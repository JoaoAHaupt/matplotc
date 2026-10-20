/* Testes do módulo de dados: create_data, load_data e free_data.
 *
 * Nenhum teste aqui abre janela: load_data só lê arquivo e aloca memória,
 * então roda em qualquer ambiente (inclusive CI sem display).
 *
 * Cada função abaixo roda várias suítes num só processo; MT_BEGIN/MT_END
 * zeram os contadores a cada suíte, então o main acumula as falhas e devolve
 * um código de saída diferente de zero se qualquer asserção falhar. */
#include "framework.h"
#include "data.h"
#include "plane.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int suites_falhas = 0;

static void reportar(void) {
  printf("    %s: %d/%d asserções\n", failed ? "FALHOU" : "PASSOU",
         total - failed, total);
  if (failed) {
    suites_falhas++;
  }
}

/* --- create_data --------------------------------------------------------- */

static void test_create_data(void) {
  MT_BEGIN("data: create_data");

  Plane plane = create_plane(0, 10, 1.0f, 0, 10, 1.0f, false);
  float x[] = {1, 2, 3};
  float y[] = {4, 5, 6};

  Data d = create_data(plane, "serie", x, "X", y, "Y", 3);
  MT_CHECK_INT(3, d.size);
  MT_CHECK(d.x == x); /* empresta os arrays do chamador */
  MT_CHECK(d.y == y);
  MT_CHECK(!d.owns_memory);
  MT_CHECK_STR("serie", d.label);
  MT_CHECK_STR("X", d.x_axis_label);
  MT_CHECK_STR("Y", d.y_axis_label);
  MT_CHECK_FLOAT(10, d.plane.x_min_max[1], 0.001f);

  /* Parâmetros inválidos: struct zerada. */
  MT_CHECK_INT(0, create_data(plane, "s", NULL, "X", y, "Y", 3).size);
  MT_CHECK_INT(0, create_data(plane, "s", x, "X", NULL, "Y", 3).size);
  MT_CHECK_INT(0, create_data(plane, "s", x, "X", y, "Y", 0).size);
  MT_CHECK_INT(0, create_data(plane, "s", x, "X", y, "Y", -5).size);
  MT_CHECK_INT(0, create_data(plane, NULL, x, "X", y, "Y", 3).size);
  MT_CHECK_INT(0, create_data(plane, "s", x, NULL, y, "Y", 3).size);
  MT_CHECK_INT(0, create_data(plane, "s", x, "X", y, NULL, 3).size);

  reportar();
}

/* --- load_data: caso normal ---------------------------------------------- */

static void test_load_data_ok(void) {
  MT_BEGIN("data: load_data (arquivo valido)");

  Plane plane = create_plane(1, 6, 1.0f, 0, 100, 10.0f, false);
  Data d =
      load_data("tests/fixtures/vendas.txt", plane, "Vendas", "Mes", "Total");

  MT_CHECK_INT(6, d.size);
  MT_CHECK(d.owns_memory);
  MT_CHECK(d.x != NULL && d.y != NULL);

  /* Comentários, linhas vazias e separadores mistos não entram na contagem. */
  MT_CHECK_FLOAT(1.0f, d.x[0], 0.001f);
  MT_CHECK_FLOAT(45.0f, d.y[0], 0.001f);
  MT_CHECK_FLOAT(3.0f, d.x[2], 0.001f);
  MT_CHECK_FLOAT(48.0f, d.y[2], 0.001f);
  MT_CHECK_FLOAT(5.0f, d.x[4], 0.001f); /* "5 72" (espaço) */
  MT_CHECK_FLOAT(72.0f, d.y[4], 0.001f);
  MT_CHECK_FLOAT(6.0f, d.x[5], 0.001f);
  MT_CHECK_FLOAT(80.0f, d.y[5], 0.001f);

  /* O plano informado é preservado. */
  MT_CHECK_FLOAT(1, d.plane.x_min_max[0], 0.001f);
  MT_CHECK_FLOAT(100, d.plane.y_min_max[1], 0.001f);

  free_data(&d);

  reportar();
}

/* --- load_data: arquivo malformado --------------------------------------- */

static void test_load_data_malformado(void) {
  MT_BEGIN("data: load_data (linhas invalidas sao ignoradas)");

  Plane plane = create_plane(0, 10, 1.0f, 0, 100, 10.0f, false);
  Data d = load_data("tests/fixtures/malformado.txt", plane, "M", "X", "Y");

  /* Sobram 4 pontos: "2 30", "3,40", "4 , 50" e "6,70". */
  MT_CHECK_INT(4, d.size);
  MT_CHECK_FLOAT(2.0f, d.x[0], 0.001f);
  MT_CHECK_FLOAT(30.0f, d.y[0], 0.001f);
  MT_CHECK_FLOAT(3.0f, d.x[1], 0.001f);
  MT_CHECK_FLOAT(40.0f, d.y[1], 0.001f);
  MT_CHECK_FLOAT(4.0f, d.x[2], 0.001f);
  MT_CHECK_FLOAT(50.0f, d.y[2], 0.001f);
  MT_CHECK_FLOAT(6.0f, d.x[3], 0.001f);
  MT_CHECK_FLOAT(70.0f, d.y[3], 0.001f);

  free_data(&d);

  reportar();
}

/* --- load_data: realloc alem da capacidade inicial ----------------------- */

static void test_load_data_muitos_pontos(void) {
  MT_BEGIN("data: load_data (cresce a capacidade)");

  Plane plane = create_plane(1, 100, 10.0f, 0, 200, 20.0f, false);
  Data d = load_data("tests/fixtures/muitos_pontos.txt", plane, "M", "X", "Y");

  MT_CHECK_INT(100, d.size); /* > 16 (capacidade inicial) e > 64 */
  MT_CHECK_FLOAT(1.0f, d.x[0], 0.001f);
  MT_CHECK_FLOAT(100.0f, d.x[99], 0.001f);
  MT_CHECK_FLOAT(200.0f, d.y[99], 0.001f);

  free_data(&d);

  reportar();
}

/* --- load_data e free_data: erros ---------------------------------------- */

static void test_load_data_erros(void) {
  MT_BEGIN("data: load_data/free_data (erros)");

  Plane plane = create_plane(0, 10, 1.0f, 0, 10, 1.0f, false);

  /* Arquivo inexistente. */
  Data missing =
      load_data("tests/fixtures/inexistente.txt", plane, "L", "X", "Y");
  MT_CHECK_INT(0, missing.size);
  MT_CHECK(missing.x == NULL && missing.y == NULL);

  /* Arquivo existe, mas sem pontos válidos. */
  Data vazio = load_data("tests/fixtures/sem_pontos.txt", plane, "L", "X", "Y");
  MT_CHECK_INT(0, vazio.size);
  MT_CHECK(vazio.x == NULL && vazio.y == NULL);

  /* Parâmetros inválidos. */
  MT_CHECK_INT(0, load_data(NULL, plane, "L", "X", "Y").size);
  MT_CHECK_INT(
      0, load_data("tests/fixtures/vendas.txt", plane, NULL, "X", "Y").size);
  MT_CHECK_INT(
      0, load_data("tests/fixtures/vendas.txt", plane, "L", NULL, "Y").size);
  MT_CHECK_INT(
      0, load_data("tests/fixtures/vendas.txt", plane, "L", "X", NULL).size);

  /* free_data é idempotente e segura para NULL e para dados emprestados. */
  free_data(&missing);
  free_data(&vazio);
  free_data(NULL);

  float x[] = {1};
  float y[] = {2};
  Data borrowed = create_data(plane, "b", x, "X", y, "Y", 1);
  free_data(&borrowed);
  MT_CHECK(borrowed.x == x); /* arrays do chamador não são liberados */
  MT_CHECK(!borrowed.owns_memory);

  reportar();
}

int main(void) {
  test_create_data();
  test_load_data_ok();
  test_load_data_malformado();
  test_load_data_muitos_pontos();
  test_load_data_erros();
  return suites_falhas == 0 ? 0 : 1;
}
