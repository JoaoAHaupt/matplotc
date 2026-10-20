#include "pie.h"
#include "colours.h"
#include "data.h"
#include "data_draw.h"
#include "plotarea.h"
#include "raylib.h"
#include <stddef.h>

/* Soma de todos os valores de y das séries. Retorna 0 se não houver dados. */
static float total_value(Data *data, int data_count) {
  if (data == NULL || data_count <= 0) {
    return 0.0f;
  }

  float total = 0;
  for (int j = 0; j < data_count; j++) {
    if (data[j].y == NULL) {
      continue;
    }
    for (int i = 0; i < data[j].size; i++) {
      total += data[j].y[i];
    }
  }
  return total;
}

/* Legenda do gráfico de pizza: uma entrada por fatia (e não por série),
 * usando o valor de x como nome da categoria. */
static void draw_pie_legend(Data *data, int data_count, PlotArea *plotarea) {
  float total = total_value(data, data_count);
  if (total <= 0) {
    return;
  }

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
    if (data[j].y == NULL) {
      continue;
    }

    for (int i = 0; i < data[j].size; i++) {
      float y = legend_y + (float)slice * line_height;

      // Caixinha colorida com a cor da fatia
      DrawRectangle((int)legend_x, (int)y, (int)box_size, (int)box_size,
                    COLOURS[slice % COLOURS_COUNT]);

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

/* Espaço reservado à direita para a legenda, em pixels. */
#define PIE_LEGEND_WIDTH 170.0f

/* Centro e raio da pizza a partir da área do gráfico: ela ocupa o espaço à
 * esquerda da legenda, centralizada, com uma folga nas bordas. */
static void pie_geometry(PlotArea *plotarea, Vector2 *center, float *radius) {
  float width = plotarea->width - PIE_LEGEND_WIDTH;
  if (width < plotarea->width * 0.5f) {
    width = plotarea->width * 0.5f;
  }
  float height = plotarea->height;

  center->x = plotarea->left + width / 2.0f;
  center->y = plotarea->top + height / 2.0f;
  *radius = (width < height ? width : height) / 2.0f * 0.9f;
}

static void draw_pie_slices(Data *data, int data_count, Vector2 center,
                            float radius) {
  float total = total_value(data, data_count);
  if (total <= 0) {
    return;
  }

  float start_angle = 0;
  int slice = 0;

  for (int j = 0; j < data_count; j++) {
    if (data[j].y == NULL) {
      continue;
    }

    for (int i = 0; i < data[j].size; i++) {
      // calcula o angulo
      float angle = (data[j].y[i] / total) * 360.0f;

      DrawCircleSector(center, radius, start_angle, start_angle + angle, 64,
                       COLOURS[slice % COLOURS_COUNT]);

      start_angle += angle;
      slice++;
    }
  }
}

void create_pie(Data *data, int data_count, PlotArea *plotarea) {
  if (data == NULL || plotarea == NULL || data_count <= 0) {
    return;
  }
  Vector2 center;
  float radius;
  pie_geometry(plotarea, &center, &radius);
  draw_pie_slices(data, data_count, center, radius);
  draw_pie_legend(data, data_count, plotarea);
}
