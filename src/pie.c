#include "pie.h"
#include "colours.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"
<<<<<<< HEAD
#include "colours.h"
#include <stddef.h>

void draw_pie_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0]) {
        return;
    }

    float total = 0;
    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            int x = data[j].x[i];
            int y = data[j].y[i];
            if (x >= plane->x_min_max[0] && x <= plane->x_min_max[1] &&
                y >= plane->y_min_max[0] && y <= plane->y_min_max[1]) {
                total += y;
            }
        }
=======

// Legenda do gráfico de pizza: uma entrada por fatia (e não por série),
// usando o valor de x como nome da categoria.
static void draw_pie_legend(Data *data, int data_count, PlotArea *plotarea) {
  float total = 0;
  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      total += data[j].y[i];
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8
    }
  }

  if (total <= 0)
    return;

  Font font = GetFontDefault();
  float font_size = 16.0f;
  float spacing = 1.0f;

<<<<<<< HEAD
    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            int x = data[j].x[i];
            int y = data[j].y[i];
            if (x < plane->x_min_max[0] || x > plane->x_min_max[1] ||
                y < plane->y_min_max[0] || y > plane->y_min_max[1]) {
                continue;
            }

            float angle = ((float)y / total) * 360.0f;
=======
  float box_size = 12.0f;
  float padding = 8.0f;
  float line_height = 24.0f;
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8

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
