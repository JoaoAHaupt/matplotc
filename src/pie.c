/**
 * @file pie.c
 * @brief Implementação do gráfico de pizza (ver pie.h).
 */

#include "pie.h"
#include "colours.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"

/**
 * @brief Desenha a legenda do gráfico de pizza.
 *
 * Uma entrada por fatia (e não por série), usando o valor de x como nome
 * da categoria e mostrando o percentual da fatia.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plotarea   Área de plotagem em pixels (posiciona a legenda).
 */
static void draw_pie_legend(Data *data, int data_count, PlotArea *plotarea) {
  float total = 0;
  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      total += data[j].y[i];
    }
  }

  if (total <= 0)
    return;

  Font font = GetFontDefault();
  float font_size = 16.0f;
  float spacing = 1.0f;

  float box_size = 12.0f;
  float padding = 8.0f;
  float line_height = 24.0f;

  float legend_x = plotarea->right - 150;
  float legend_y = plotarea->top + 10;

  int slice = 0;
  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      float y = legend_y + slice * line_height;

      // Caixinha colorida com a cor da fatia
      DrawRectangle((int)legend_x, (int)y, (int)box_size, (int)box_size,
                    COLOURS[i % COLOURS_COUNT]);

      // Nome da categoria (x) e o seu percentual
      const char *label = TextFormat("%g (%.0f%%)", data[j].x[i],
                                     data[j].y[i] / total * 100.0f);
      DrawTextEx(font, label,
                 (Vector2){legend_x + box_size + padding, y - 2}, font_size,
                 spacing, BLACK);

      slice++;
    }
  }
}

void draw_pie_data(Data *data, int data_count) {
  float total = 0;
  // soma ytudo
  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      total += data[j].y[i];
    }
  }

  if (total <= 0)
    return;

  float start_angle = 0;

  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      // calcula o angulo
      float angle = (data[j].y[i] / total) * 360.0f;

      DrawCircleSector((Vector2){400, 400}, 150, start_angle,
                       start_angle + angle, 32, COLOURS[i % COLOURS_COUNT]);

      start_angle += angle;
    }
  }
}

void create_pie(Data *data, int data_count, PlotArea *plotarea) {
  draw_pie_data(data, data_count);
  draw_pie_legend(data, data_count, plotarea);
}
