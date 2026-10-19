#include "line.h"
#include "colours.h"
#include "data.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot) {
  float x_range = plane->x_min_max[1] - plane->x_min_max[0];
  float y_range = plane->y_min_max[1] - plane->y_min_max[0];

  for (int j = 0; j < data_count; j++) {
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
                 3.0f, COLOURS[j]);
    }
  }
}

void create_line(Plane *plane, Data *data, int data_count, PlotArea *plotarea) {
  draw_plane(plane, plotarea);
  draw_line_data(data, data_count, plane, plotarea);
  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
}
