#include "line.h"
#include "colours.h"
#include "data.h"
#include "data_draw.h"
#include "plane.h"
#include "plane_draw.h"
#include "plotarea.h"
#include "raylib.h"
#include <stddef.h>

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot) {
  float x_range = plane->x_min_max[1] - plane->x_min_max[0];
  float y_range = plane->y_min_max[1] - plane->y_min_max[0];

  for (int j = 0; j < data_count; j++) {
    if (data[j].x == NULL || data[j].y == NULL) {
      continue;
    }
    for (int i = 1; i < data[j].size; i++) {
      float point_x1 = plot->left + (data[j].x[i - 1] - plane->x_min_max[0]) /
                                        x_range * plot->width;

      float point_y1 = plot->bottom - (data[j].y[i - 1] - plane->y_min_max[0]) /
                                          y_range * plot->height;

      float point_x2 = plot->left + (data[j].x[i] - plane->x_min_max[0]) /
                                        x_range * plot->width;

      float point_y2 = plot->bottom - (data[j].y[i] - plane->y_min_max[0]) /
                                          y_range * plot->height;

      DrawLineEx((Vector2){point_x1, point_y1}, (Vector2){point_x2, point_y2},
                 3.0f, COLOURS[j % COLOURS_COUNT]);
    }
  }
}

void create_line(Plane *plane, Data *data, int data_count, PlotArea *plotarea) {
  if (plane == NULL || data == NULL || plotarea == NULL || data_count <= 0) {
    return;
  }
  draw_plane(plane, plotarea);

  // Recorta o desenho na area do grafico: pontos fora do plano nao invadem
  // as margens, os eixos nem a legenda.
  BeginScissorMode((int)plotarea->left, (int)plotarea->top,
                   (int)plotarea->width, (int)plotarea->height);
  draw_line_data(data, data_count, plane, plotarea);
  EndScissorMode();

  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
}
