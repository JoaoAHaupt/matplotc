#include "framework.h"
#include "context.h"
#include "data.h"
#include "matplotc.h"
#include "plane.h"
#include <stdbool.h>

int main(void) {
  MT_BEGIN("context and plane constructors");

  Context context = create_context(800.0f, 600.0f, "test");
  MT_CHECK_FLOAT(800.0f, context.width, 0.001f);
  MT_CHECK_FLOAT(600.0f, context.height, 0.001f);
  MT_CHECK_STR("test", context.title);

  context = create_context(0.0f, 600.0f, "test");
  MT_CHECK_FLOAT(0.0f, context.width, 0.001f);
  MT_CHECK_FLOAT(0.0f, context.height, 0.001f);
  MT_CHECK(context.title == NULL);

  context = create_context(800.0f, -1.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(-1.0f, 600.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 0.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 600.0f, NULL);
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 600.0f, "");
  MT_CHECK(context.title == NULL);

  Plane plane = create_plane(-10, 10, 2.0f, -20, 20, 5.0f, true);
  MT_CHECK_INT(-10, plane.x_min_max[0]);
  MT_CHECK_INT(10, plane.x_min_max[1]);
  MT_CHECK_FLOAT(2.0f, plane.scale_x, 0.001f);
  MT_CHECK_INT(-20, plane.y_min_max[0]);
  MT_CHECK_INT(20, plane.y_min_max[1]);
  MT_CHECK_FLOAT(5.0f, plane.scale_y, 0.001f);
  MT_CHECK(plane.lines);

  plane = create_plane(5, 5, 1.0f, 0, 10, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[0]);
  MT_CHECK_INT(0, plane.y_min_max[1]);
  plane = create_plane(0, 10, 1.0f, 5, 5, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[1]);

  plane = create_plane(10, 0, 1.0f, 0, 10, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[1]);
  plane = create_plane(0, 10, 1.0f, 10, 0, 1.0f, false);
  MT_CHECK_INT(0, plane.y_min_max[1]);

  plane = create_plane(0, 10, 0.0f, 0, 10, 1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_x, 0.001f);
  plane = create_plane(0, 10, -1.0f, 0, 10, 1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_x, 0.001f);
  plane = create_plane(0, 10, 1.0f, 0, 10, 0.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_y, 0.001f);
  plane = create_plane(0, 10, 1.0f, 0, 10, -1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_y, 0.001f);

  /* --- Módulo de dados: load_data / free_data --- */
  plane = create_plane(1, 6, 1.0f, 0, 100, 10.0f, false);

  Data loaded =
      load_data("tests/fixtures/vendas.txt", plane, "Vendas", "Mes", "Total");
  MT_CHECK_INT(6, loaded.size);
  MT_CHECK(loaded.owns_memory);
  MT_CHECK_STR("Vendas", loaded.label);
  MT_CHECK_STR("Mes", loaded.x_axis_label);
  MT_CHECK_STR("Total", loaded.y_axis_label);
  MT_CHECK_FLOAT(1.0f, loaded.x[0], 0.001f);
  MT_CHECK_FLOAT(45.0f, loaded.y[0], 0.001f);
  MT_CHECK_FLOAT(6.0f, loaded.x[5], 0.001f);
  MT_CHECK_FLOAT(80.0f, loaded.y[5], 0.001f);
  MT_CHECK_FLOAT(1, loaded.plane.x_min_max[0], 0.001f);

  free_data(&loaded);
  MT_CHECK(loaded.x == NULL);
  MT_CHECK(loaded.y == NULL);
  MT_CHECK_INT(0, loaded.size);
  MT_CHECK(!loaded.owns_memory);

  /* Arquivo inexistente e parâmetros inválidos: retorna Data zerada. */
  Data missing =
      load_data("tests/fixtures/nao_existe.txt", plane, "L", "X", "Y");
  MT_CHECK_INT(0, missing.size);
  MT_CHECK(missing.x == NULL);
  MT_CHECK(missing.y == NULL);

  Data no_params = load_data(NULL, plane, "L", "X", "Y");
  MT_CHECK_INT(0, no_params.size);

  free_data(&missing); /* inofensiva: nada alocado */
  free_data(NULL);     /* inofensiva */

  /* --- show() e export_png() devem falhar cedo, sem abrir janela, quando
   * não há janela/gráfico registrado. ATENÇÃO: nunca chame um plot_* com
   * argumentos válidos aqui, senão show()/export_png() abririam uma janela
   * de verdade e gravaria um PNG. */
  show(NULL);
  show(&context);

  plane = create_plane(0, 10, 1.0f, 0, 10, 1.0f, false);
  plot_bar(&context, &plane, NULL, 1); /* dado inválido: não registra */
  plot_histogram(NULL, &plane, NULL, 1);
  show(&context); /* ainda sem gráfico registrado */

  MT_CHECK(!export_png(NULL, "saida.png"));
  MT_CHECK(!export_png(&context, NULL));
  MT_CHECK(!export_png(&context, ""));
  MT_CHECK(!export_png(&context, "saida.png")); /* sem gráfico registrado */

  return MT_END();
}
