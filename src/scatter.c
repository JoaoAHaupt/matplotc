#include "colours.h"
#include "data.h"
#include "math.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"
#include "scatter.h"

static const int font_size = 15;

void draw_scatter_data(Data *data, int data_count, Plane *plane, PlotArea *plot) {
  float x_min = plane->x_min_max[0];
  float y_min = plane->y_min_max[0];
  float x_range = plane->x_min_max[1] - x_min;
  float y_range = plane->y_min_max[1] - y_min;

  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      float x = data[j].x[i];
      float y = data[j].y[i];

      float point_x = plot->left + (x - x_min) / x_range * plot->width;
      float point_y = plot->bottom - (y - y_min) / y_range * plot->height;

      DrawCircle((int)point_x, (int)point_y, 4.0f, COLOURS[j]);
    }
  }
}

void draw_linear_correlation(Data *data, int data_count, Plane *plane,
                             PlotArea *plot) {
  // Soma
  float sum_x = 0.0f, sum_y = 0.0f;
  float sum_xy = 0.0f, sum_x2 = 0.0f, sum_y2 = 0.0f;

  int total = 0;
  for (int j = 0; j < data_count; j++) {
    for (int i = 0; i < data[j].size; i++) {
      sum_x += data[j].x[i];
      sum_y += data[j].y[i];
      sum_xy += data[j].x[i] * data[j].y[i];
      sum_x2 += data[j].x[i] * data[j].x[i];
      sum_y2 += data[j].y[i] * data[j].y[i];
      total++;
    }
  }

  if (total == 0)
    return;

  float mean_x = sum_x / (float)total;
  float mean_y = sum_y / (float)total;

  float numerator_b = sum_xy - (float)total * mean_x * mean_y;
  float denominator_b = sum_x2 - (float)total * mean_x * mean_x;

  if (fabsf(denominator_b) < 1e-12f)
    return;

  float b = numerator_b / denominator_b;
  float a = mean_y - b * mean_x;

  float x_min = plane->x_min_max[0];
  float x_max = plane->x_min_max[1];
  float x_range = x_max - x_min;
  float y_range = plane->y_min_max[1] - plane->y_min_max[0];

  float x1 = x_min;
  float y1 = a + b * x1;
  float x2 = x_max;
  float y2 = a + b * x2;

  float px1 = plot->left + (x1 - x_min) / x_range * plot->width;
  float py1 = plot->bottom - (y1 - plane->y_min_max[0]) / y_range * plot->height;
  float px2 = plot->left + (x2 - x_min) / x_range * plot->width;
  float py2 = plot->bottom - (y2 - plane->y_min_max[0]) / y_range * plot->height;

  DrawLineEx((Vector2){px1, py1}, (Vector2){px2, py2}, 2.0f, DARKGRAY);

  float r_num = (float)total * sum_xy - sum_x * sum_y;
  float r_den = sqrtf(((float)total * sum_x2 - sum_x * sum_x) *
                      ((float)total * sum_y2 - sum_y * sum_y));
  if (r_den < 1e-12f)
    return;
  float r = r_num / r_den;

  const char *eq = TextFormat("y = %g x + %g  r = %.3f", b, a, r);
  DrawText(eq, (int)(plot->left + 10), (int)(plot->top + 10), font_size, BLACK);
}

void create_scatter(Plane *plane, Data *data, int data_count, PlotArea *plotarea,
                    bool show_regression) {
  draw_plane(plane, plotarea);
  draw_scatter_data(data, data_count, plane, plotarea);
  if (show_regression) {
    draw_linear_correlation(data, data_count, plane, plotarea);
  }
  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
}
