#include "bar.h"
#include "colours.h"
#include "data.h"
#include "data_draw.h"
#include "math.h"
#include "plane.h"
#include "plane_draw.h"
#include "plotarea.h"
#include "raylib.h"
#include <stddef.h>

void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot) {
  if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
      plane->x_min_max[1] <= plane->x_min_max[0] ||
      plane->y_min_max[1] <= plane->y_min_max[0] || plot->width <= 0 ||
      plot->height <= 0) {
    return;
  }

  float x_min = plane->x_min_max[0];
  float x_max = plane->x_min_max[1];
  float y_min = plane->y_min_max[0];
  float y_max = plane->y_min_max[1];

  float x_range = x_max - x_min;
  float y_range = y_max - y_min;

  float min_step = x_range;
  for (int j = 0; j < data_count; j++) {
    if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
      continue;
    }
    for (int i = 1; i < data[j].size; i++) {
      float d = fabsf(data[j].x[i] - data[j].x[i - 1]);
      if (d > 0 && d < min_step)
        min_step = d;
    }
  }

  if (min_step <= 0.0f || min_step > x_range) {
    min_step = x_range / 10.0f;
  }

  float slot_w = (min_step / x_range) * plot->width;
  float group_w = slot_w * 0.8f;
  float bar_w = group_w / (float)data_count;

  float base_val = fminf(fmaxf(0.0f, y_min), y_max);
  float base_y = plot->bottom - (base_val - y_min) / y_range * plot->height;
  base_y = fminf(fmaxf(base_y, plot->top), plot->bottom);

  // Recorta o desenho na area do grafico
  BeginScissorMode((int)plot->left, (int)plot->top, (int)plot->width,
                   (int)plot->height);

  for (int j = 0; j < data_count; j++) {
    if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
      continue;
    }
    Color bar_color = COLOURS[j % COLOURS_COUNT];
    for (int i = 0; i < data[j].size; i++) {
      float x = data[j].x[i];
      float y = data[j].y[i];

      if (x < x_min || x > x_max) {
        continue;
      }

      float center_x = plot->left + (x - x_min) / x_range * plot->width;
      float bar_x = center_x - group_w / 2.0f + (float)j * bar_w;

      float value_y = plot->bottom - (y - y_min) / y_range * plot->height;
      value_y = fminf(fmaxf(value_y, plot->top), plot->bottom);

      float top = fminf(value_y, base_y);
      float bottom = fmaxf(value_y, base_y);
      top = fmaxf(top, plot->top);
      bottom = fminf(bottom, plot->bottom);
      if (bottom <= top)
        continue;

      Rectangle bar = {
          .x = bar_x, .y = top, .width = bar_w, .height = bottom - top};
      DrawRectangleRec(bar, bar_color);
      DrawRectangleLinesEx(bar, 1.0f, BLACK);
    }
  }

  EndScissorMode();
}

void create_bar(Plane *plane, Data *data, int data_count, PlotArea *plotarea) {
  if (plane == NULL || data == NULL || plotarea == NULL || data_count <= 0) {
    return;
  }
  draw_plane(plane, plotarea);
  draw_bar_data(data, data_count, plane, plotarea);
  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
}
