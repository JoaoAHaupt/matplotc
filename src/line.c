#include "line.h"
#include "colours.h"
#include "data.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"
<<<<<<< HEAD
#include "colours.h"
#include <stddef.h>

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        plot->width <= 0.0f || plot->height <= 0.0f) {
        return;
    }

    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size < 2) {
            continue;
        }

        for (int i = 1; i < data[j].size; i++) {
            int x1 = data[j].x[i - 1];
            int y1 = data[j].y[i - 1];
            int x2 = data[j].x[i];
            int y2 = data[j].y[i];

            if (x1 < plane->x_min_max[0] || x1 > plane->x_min_max[1] ||
                y1 < plane->y_min_max[0] || y1 > plane->y_min_max[1] ||
                x2 < plane->x_min_max[0] || x2 > plane->x_min_max[1] ||
                y2 < plane->y_min_max[0] || y2 > plane->y_min_max[1]) {
                continue;
            }

            float point_x1 = plot->left +
                (x1 - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y1 = plot->bottom -
                (y1 - plane->y_min_max[0]) /
                y_range * plot->height;

            float point_x2 = plot->left +
                (x2 - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y2 = plot->bottom -
                (y2 - plane->y_min_max[0]) /
                y_range * plot->height;
=======

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
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8

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
