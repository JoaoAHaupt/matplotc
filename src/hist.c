#include "hist.h"
#include "colours.h"
#include "raylib.h"
#include <limits.h>
<<<<<<< HEAD
#include <math.h>
#include <stddef.h>

void draw_hist_data(Data *data, int data_count, Plane *plane, PlotArea *plot) {
  if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
      plane->x_min_max[1] <= plane->x_min_max[0] || plane->y_min_max[1] <= 0 ||
      plane->y_min_max[1] <= plane->y_min_max[0] || !isfinite(plane->scale_x) ||
      plane->scale_x <= 0.0 || plot->width <= 0.0 || plot->height <= 0.0) {
    return;
  }

  float x_min = (float)plane->x_min_max[0];
  float x_max = (float)plane->x_min_max[1];
  float y_min = (float)plane->y_min_max[0];
  float y_max = (float)plane->y_min_max[1];
  float x_range = x_max - x_min;
  float y_range = y_max - y_min;
  float requested_bins = ceilf(x_range / plane->scale_x);

  if (!isfinite(requested_bins) || requested_bins >= (float)INT_MAX) {
    return;
  }

  int bin_count = (int)requested_bins;

  if (bin_count < 1) {
    bin_count = 1;
  }

  int pixel_bin_limit = (int)plot->width;

  if (pixel_bin_limit < 1) {
    pixel_bin_limit = 1;
  }
  int requested_bin_count = bin_count;

  if (bin_count > pixel_bin_limit) {
    bin_count = pixel_bin_limit;
  }

  float bin_width = bin_count == requested_bin_count
                        ? plane->scale_x
                        : x_range / (float)bin_count;

  float baseline = 0.0;

  if (baseline < y_min) {
    baseline = y_min;
  } else if (baseline > y_max) {
    baseline = y_max;
  }

  float baseline_y =
      plot->bottom - ((baseline - y_min) / y_range) * plot->height;

  for (int series = 0; series < data_count; series++) {
    if (data[series].x == NULL || data[series].size <= 0) {
      continue;
=======
#include <stddef.h>

void draw_hist_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
)
{
    if (data == NULL || plane == NULL || plot == NULL ||
        data_count <= 0 ||
        plane->y_min_max[1] <= 0 ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        !isfinite(plane->scale_x) || plane->scale_x <= 0.0 ||
        plot->width <= 0.0 || plot->height <= 0.0) {
        return;
>>>>>>> 6d4ffbf (fix: use all labels)
    }

    Color color = COLOURS[series % COLOURS_COUNT];

    for (int bin = 0; bin < bin_count; bin++) {
      float bin_min = x_min + (float)bin * bin_width;
      float bin_max = fminf(bin_min + bin_width, x_max);
      int frequency = 0;

<<<<<<< HEAD
      for (int sample = 0; sample < data[series].size; sample++) {
        float value = (float)data[series].x[sample];
        if (value >= bin_min &&
            (value < bin_max || (bin == bin_count - 1 && value <= x_max))) {
          frequency++;
=======
    int bin_count = (int)requested_bins;

    if (bin_count < 1) {
        bin_count = 1;
    }

    float bin_width = x_range / (float)bin_count;

    float baseline = 0.0;

    if (baseline < y_min) {
        baseline = y_min;
    } else if (baseline > y_max) {
        baseline = y_max;
    }

    float baseline_y = plot->bottom -
        ((baseline - y_min) / y_range) * plot->height;

    for (int series = 0; series < data_count; series++) {
        if (data[series].x == NULL || data[series].size <= 0) {
            continue;
>>>>>>> 6d4ffbf (fix: use all labels)
        }
      }

      if (frequency == 0) {
        continue;
      }

<<<<<<< HEAD
      if ((float)frequency <= baseline) {
        continue;
      }
=======
        for (int bin = 0; bin < bin_count; bin++) {
            float bin_min = x_min + (float)bin * bin_width;
            float bin_max = bin_min + bin_width;
            int frequency = 0;
>>>>>>> 6d4ffbf (fix: use all labels)

      float value_y =
          plot->bottom - (((float)frequency - y_min) / y_range) * plot->height;
      float top = fminf(value_y, baseline_y);
      float bottom = fmaxf(value_y, baseline_y);
      float bin_left = plot->left + ((bin_min - x_min) / x_range) * plot->width;
      float bin_pixel_width = ((bin_max - bin_min) / x_range) * plot->width;
      float bar_width = bin_pixel_width / (float)data_count;
      float left = bin_left + (float)series * bar_width;
      float right = left + bar_width;

      left = fmaxf(left, plot->left);
      right = fminf(right, plot->right);
      top = fmaxf(top, plot->top);
      bottom = fminf(bottom, plot->bottom);

<<<<<<< HEAD
      if (right <= left || bottom <= top) {
        continue;
      }

      Rectangle bar = {
          .x = left, .y = top, .width = right - left, .height = bottom - top};
=======
            float value_y = plot->bottom -
                (((float)frequency - y_min) / y_range) * plot->height;
            float top = fminf(value_y, baseline_y);
            float bottom = fmaxf(value_y, baseline_y);
            float bin_left = plot->left +
                ((bin_min - x_min) / x_range) * plot->width;
            float bar_width = (bin_width / x_range * plot->width) / (float)data_count;
            float left = bin_left + (float)series * bar_width;
            float right = left + bar_width;
>>>>>>> 6d4ffbf (fix: use all labels)

      DrawRectangleRec(bar, color);
      DrawRectangleLinesEx(bar, 1.0f, BLACK);
    }
  }
}

<<<<<<< HEAD
void create_histogram(Plane *plane, Data *data, int data_count,
                      PlotArea *plotarea) {
  if (plane == NULL || data == NULL || plotarea == NULL || data_count <= 0) {
    return;
  }

  draw_plane(plane, plotarea);
  draw_hist_data(data, data_count, plane, plotarea);
  draw_label(data, plane, plotarea);
  draw_legend(data, data_count, plotarea);
=======
void create_histogram(Plane *plane, Data *data, int data_count, PlotArea *plotarea)
{
    if (plane == NULL || data == NULL ||
        plotarea == NULL || data_count <= 0) {
        return;
    }

    draw_plane(plane, plotarea);
    draw_hist_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
>>>>>>> 6d4ffbf (fix: use all labels)
}
