#include "plane.h"
#include "plane_draw.h"
#include "plotarea.h"
#include "raylib.h"
#include <stdio.h>

static const int font_size = 15;
static const int tick_size = 10;

Plane create_plane(float x_min, float x_max, float scale_x, float y_min,
                   float y_max, float scale_y, bool lines) {
  if (x_min >= x_max || y_min >= y_max || scale_x <= 0 || scale_y <= 0) {
    fprintf(stderr, "Error: Invalid parameters when creating Plane.\n");
    return (Plane){0};
  }

  Plane plane = {.x_min_max = {x_min, x_max},
                 .scale_x = scale_x,
                 .y_min_max = {y_min, y_max},
                 .scale_y = scale_y,
                 .lines = lines};

  return plane;
}

void draw_plane(Plane *plane, PlotArea *plot_area) {
  draw_axis_x(plane->scale_x, plane->x_min_max, plane->lines, plot_area);
  draw_axis_y(plane->scale_y, plane->y_min_max, plane->lines, plot_area);

  // Borda do grafico
  DrawRectangleLines((int)plot_area->left, (int)plot_area->top,
                     (int)plot_area->width, (int)plot_area->height, BLACK);
}

/* Eixo X: marcadores embaixo, valores crescendo da esquerda para a direita. */
void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area) {
  if (scale <= 0.0f) {
    return;
  }

  int number_of_scale = (int)((min_max[1] - min_max[0]) / scale);

  if (number_of_scale <= 0) {
    return;
  }

  float scale_pixel_x = plot_area->width / number_of_scale;
  float value = min_max[0];

  for (int i = 0; i <= number_of_scale; i++) {
    float x = plot_area->left + i * scale_pixel_x;

    DrawRectangle((int)(x - 1), (int)(plot_area->bottom - (float)tick_size / 2),
                  2, tick_size, BLACK);

    if (lines && i > 0 && i < number_of_scale) {
      DrawLine((int)x, (int)plot_area->top, (int)x, (int)plot_area->bottom,
               LIGHTGRAY);
    }

    const char *label = TextFormat("%g", value);
    int text_width = MeasureText(label, font_size);

    DrawText(label, (int)(x - (float)text_width / 2),
             (int)(plot_area->bottom + 12), font_size, BLACK);

    value += scale;
  }
}

/* Eixo Y: marcadores na esquerda, valores crescendo de baixo para cima. */
void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area) {
  if (scale <= 0.0f) {
    return;
  }

  int number_of_scale = (int)((min_max[1] - min_max[0]) / scale);

  if (number_of_scale <= 0) {
    return;
  }

  float scale_pixel_y = plot_area->height / number_of_scale;
  float value = min_max[0];

  for (int i = 0; i <= number_of_scale; i++) {
    float y = plot_area->bottom - i * scale_pixel_y;

    DrawRectangle((int)(plot_area->left - (float)tick_size / 2), (int)(y - 1),
                  tick_size, 2, BLACK);

    if (lines && i > 0 && i < number_of_scale) {
      DrawLine((int)plot_area->left, (int)y, (int)plot_area->right, (int)y,
               LIGHTGRAY);
    }

    const char *label = TextFormat("%g", value);
    int text_width = MeasureText(label, font_size);

    DrawText(label,
             (int)(plot_area->left - (float)tick_size / 2 - 8 - text_width),
             (int)(y - (float)font_size / 2), font_size, BLACK);

    value += scale;
  }
}
