#include "bar.h"
#include "colours.h"
#include "data.h"
#include "math.h"
#include "plane.h"
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

<<<<<<< HEAD
static float get_slot_width(
    Data *data,
    int data_count,
    float x_min,
    float x_max,
    float y_min,
    float y_max,
    PlotArea *plot
)
{
    if (data == NULL || data_count <= 0 || plot == NULL ||
        x_max <= x_min || y_max <= y_min ||
        plot->width <= 0.0f) {
        return 0.0f;
    }

    float x_range = x_max - x_min;
    float min_step = x_range;

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL ||
            data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            if (data[j].x[i] < x_min || data[j].x[i] > x_max ||
                data[j].y[i] < y_min || data[j].y[i] > y_max) {
                continue;
            }

            float current_x = (float)data[j].x[i];

            for (int k = 0; k < data_count; k++) {
                if (data[k].x == NULL || data[k].y == NULL ||
                    data[k].size <= 0) {
                    continue;
                }

                for (int l = 0; l < data[k].size; l++) {
                    if (data[k].x[l] < x_min || data[k].x[l] > x_max ||
                        data[k].y[l] < y_min || data[k].y[l] > y_max) {
                        continue;
                    }

                    float distance =
                        fabsf(current_x - (float)data[k].x[l]);

                    if (distance > 0.0f && distance < min_step) {
                        min_step = distance;
                    }
                }
            }
        }
    }

    if (min_step <= 0.0f || min_step > x_range) {
        min_step = x_range / 10.0f;
    }

    return (min_step / x_range) * plot->width;
}

void draw_bar_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
)
{
    if (data == NULL || plane == NULL || plot == NULL ||
        data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        plot->width <= 0 || plot->height <= 0) {
        return;
    }

    float x_min = plane->x_min_max[0];
    float x_max = plane->x_min_max[1];
    float y_min = plane->y_min_max[0];
    float y_max = plane->y_min_max[1];

    float x_range = x_max - x_min;
    float y_range = y_max - y_min;

    float slot_width = get_slot_width(
        data, data_count, x_min, x_max, y_min, y_max, plot
    );
    float group_width = slot_width * BAR_WIDTH_RATIO;
    float bar_width = group_width / data_count;
=======
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
  float bar_w = group_w / data_count;

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
    Color bar_color = COLOURS[j % 8];
    for (int i = 0; i < data[j].size; i++) {
      float x = data[j].x[i];
      float y = data[j].y[i];

      if (x < x_min || x > x_max) {
        continue;
      }
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8

      float center_x = plot->left + (x - x_min) / x_range * plot->width;
      float bar_x = center_x - group_w / 2.0f + j * bar_w;

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

<<<<<<< HEAD
    float base_y = plot->bottom -
        ((base_value - y_min) / y_range) * plot->height;

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL ||
            data[j].size <= 0) {
            continue;
        }

        Color bar_color = COLOURS[j % BAR_COLOUR_COUNT];

        for (int i = 0; i < data[j].size; i++) {
            float x = (float)data[j].x[i];
            float y = (float)data[j].y[i];

            /*
             * Ignore values outside the horizontal plot range.
             */
            if (x < x_min || x > x_max || y < y_min || y > y_max) {
                continue;
            }

            float center_x = plot->left + slot_width / 2.0f +
                ((x - x_min) / x_range) *
                (plot->width - slot_width);

            /*
             * Center the entire group around its x coordinate.
             */
            float bar_x = center_x - group_width / 2.0f
                        + j * bar_width;

            /*
             * Convert the value to screen coordinates.
             */
            float value_y = plot->bottom -
                ((y - y_min) / y_range) * plot->height;

            /*
             * Construct the rectangle between the value and baseline.
             */
            float top = fminf(value_y, base_y);
            float bottom = fmaxf(value_y, base_y);

            /*
             * Clip the rectangle to the plot area.
             */
            float left = fmaxf(bar_x, plot->left);
            float right = fminf(bar_x + bar_width, plot->right);

            top = fmaxf(top, plot->top);
            bottom = fminf(bottom, plot->bottom);

            if (right <= left || bottom <= top) {
                continue;
            }

            Rectangle bar = {
                .x = left,
                .y = top,
                .width = right - left,
                .height = bottom - top
            };

            DrawRectangleRec(bar, bar_color);
            DrawRectangleLinesEx(bar, 1.0f, BLACK);
        }
    }
}

void create_bar(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
)
{
    if (context == NULL || plane == NULL ||
        data == NULL || plotarea == NULL || data_count <= 0) {
        return;
    }

    float slot_width = get_slot_width(
        data,
        data_count,
        (float)plane->x_min_max[0],
        (float)plane->x_min_max[1],
        (float)plane->y_min_max[0],
        (float)plane->y_min_max[1],
        plotarea
    );

    draw_plane_with_x_inset(context, plane, plotarea, slot_width / 2.0f);
    draw_bar_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
=======
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
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8
}
