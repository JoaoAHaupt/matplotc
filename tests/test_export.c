/* Teste de integração do módulo de exportação (export_png).
 *
 * export_png precisa de um contexto gráfico da raylib, então este teste só
 * realmente exporta se houver um display disponível (ou Xvfb). Sem display,
 * as asserções de arquivo são ignoradas e o teste passa — assim ele roda
 * também em CI headless.
 *
 * Nenhum teste aqui chama show(): a janela é criada oculta. */
#include "framework.h"
#include "data.h"
#include "matplotc.h"
#include "plane.h"
#include <stdio.h>
#include <stdlib.h>

#define SAIDA "build/tests/saida_export.png"

static long tamanho_arquivo(const char *path) {
  FILE *f = fopen(path, "rb");
  if (f == NULL) {
    return -1;
  }
  fseek(f, 0, SEEK_END);
  long n = ftell(f);
  fclose(f);
  return n;
}

int main(void) {
  MT_BEGIN("export_png: falhas cedo (sem janela)");

  /* Caminhos inválidos retornam false sem sequer abrir a raylib. */
  MT_CHECK(!export_png(NULL, SAIDA));
  MT_CHECK(!export_png(NULL, NULL));

  Context ctx = create_context(320.0f, 240.0f, "export test");
  MT_CHECK(!export_png(&ctx, NULL));
  MT_CHECK(!export_png(&ctx, ""));
  MT_CHECK(!export_png(&ctx, SAIDA)); /* nada registrado ainda */

  remove(SAIDA);

  const char *display = getenv("DISPLAY");
  if (display == NULL || display[0] == '\0') {
    printf("    (sem DISPLAY: export real ignorado)\n");
    return MT_END();
  }

  /* Reporta a suíte anterior antes que MT_BEGIN zere os contadores. */
  int falhas = MT_END();

  MT_BEGIN("export_png: gera arquivo PNG");

  Plane plane = create_plane(1, 3, 1.0f, 0, 100, 10.0f, false);
  float x[] = {1, 2, 3};
  float y[] = {10, 50, 90};
  Data d = create_data(plane, "serie", x, "X", y, "Y", 3);

  plot_line(&ctx, &plane, &d, 1);
  MT_CHECK(export_png(&ctx, SAIDA));
  MT_CHECK(tamanho_arquivo(SAIDA) > 0);

  remove(SAIDA);
  falhas = MT_END() || falhas;

  /* Mais séries do que cores na paleta (8): as cores devem se repetir em
   * ciclo, sem ler fora do vetor COLOURS. */
  MT_BEGIN("export_png: mais de 8 series");

  Plane muitas = create_plane(0, 10, 1.0f, 0, 12, 1.0f, true);
  float mx[] = {0, 10};
  float my[10][2];
  Data series[10];
  for (int i = 0; i < 10; i++) {
    my[i][0] = my[i][1] = (float)(i + 1);
    series[i] = create_data(muitas, "serie", mx, "X", my[i], "Y", 2);
  }

  plot_line(&ctx, &muitas, series, 10);
  MT_CHECK(export_png(&ctx, SAIDA));
  plot_scatter(&ctx, &muitas, series, 10, true);
  MT_CHECK(export_png(&ctx, SAIDA));
  MT_CHECK(tamanho_arquivo(SAIDA) > 0);

  remove(SAIDA);
  return MT_END() || falhas;
}
