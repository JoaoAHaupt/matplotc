#include "scatter.h"
#include "colours.h"
#include "data.h"
#include "math.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"

void draw_scatter_data(Data *data, int data_count, Plane *plane,
                       PlotArea *plot) {
  float x_range = plane->x_min_max[1] - plane->x_min_max[0];
  float y_range = plane->y_min_max[1] - plane->y_min_max[0];

  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      float point_x = plot->left + (data[j].x[i] - plane->x_min_max[0]) /
                                       x_range * plot->width;

      float point_y = plot->bottom - (data[j].y[i] - plane->y_min_max[0]) /
                                         y_range * plot->height;

      DrawCircle((int)point_x, (int)point_y, 5, COLOURS[j]);
    }
  }
}

void create_scatter(Plane *plane, Data *data, int data_count,
                    PlotArea *plotarea, bool show_regression) {
  draw_plane(plane, plotarea);
  draw_scatter_data(data, data_count, plane, plotarea);
  if (show_regression) {
    draw_linear_correlation(data, data_count, plane, plotarea);
  }
  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
}

void draw_linear_correlation(Data *data, int data_count, Plane *plane,
                             PlotArea *plot) {
  float x_range = plane->x_min_max[1] - plane->x_min_max[0];
  float y_range = plane->y_min_max[1] - plane->y_min_max[0];

  if (x_range <= 0 || y_range <= 0)
    return;

  for (int j = 0; j < data_count; j++) {
    int n = data[j].size;

    if (n < 2)
      continue;

    double sum_x = 0;
    double sum_y = 0;
    double sum_xy = 0;
    double sum_x2 = 0;

    for (int i = 0; i < n; i++) {
      double x = data[j].x[i];
      double y = data[j].y[i];

      sum_x += x;
      sum_y += y;
      sum_xy += x * y;
      sum_x2 += x * x;
    }

    double denominator = n * sum_x2 - sum_x * sum_x;

    if (fabs(denominator) < 1e-9)
      continue;

    double a = (n * sum_xy - sum_x * sum_y) / denominator;
    double b = (sum_y - a * sum_x) / n;

    double x1 = plane->x_min_max[0];
    double x2 = plane->x_min_max[1];

    double y1 = a * x1 + b;
    double y2 = a * x2 + b;

    float screen_x1 =
        plot->left + (x1 - plane->x_min_max[0]) / x_range * plot->width;

    float screen_y1 =
        plot->bottom - (y1 - plane->y_min_max[0]) / y_range * plot->height;

    float screen_x2 =
        plot->left + (x2 - plane->x_min_max[0]) / x_range * plot->width;

    float screen_y2 =
        plot->bottom - (y2 - plane->y_min_max[0]) / y_range * plot->height;

    DrawLineEx((Vector2){screen_x1, screen_y1}, (Vector2){screen_x2, screen_y2},
               1.0f, COLOURS[j]);
  }
}
