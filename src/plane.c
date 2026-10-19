#include "plane.h"
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

<<<<<<< HEAD
void draw_plane(Context *context, Plane *plane, PlotArea *plot)
{
    draw_plane_with_x_inset(context, plane, plot, 0.0f);
}

void draw_plane_with_x_inset(
    Context *context,
    Plane *plane,
    PlotArea *plot,
    float x_inset
)
{
    (void)context;

    float graph_width = plot->width;
    float graph_height = plot->height;

    float graph_left = plot->left;
    float graph_right = plot->right;
    float graph_top = plot->top;
    float graph_bottom = plot->bottom;

    // Eixo X
    int number_of_scale_x =
        (plane->x_min_max[1] - plane->x_min_max[0]) / plane->scale_x;

    if (number_of_scale_x <= 0) {
        return;
    }

    float x_axis_width = graph_width - 2.0f * x_inset;
    float scale_pixel_x = x_axis_width / number_of_scale_x;
    float value_x = plane->x_min_max[0];

    for (int i = 0; i <= number_of_scale_x; i++) {
        float x = graph_left + x_inset + i * scale_pixel_x;

        // marcadorzin
        DrawRectangle(
            (int)(x - 1),
            (int)(graph_bottom - tick_size / 2),
            2,
            tick_size,
            BLACK
        );

        // linhas verticais da grad, somente se quiser
        if (plane->lines && i > 0 && i < number_of_scale_x) {
            DrawLine(
                (int)x,
                (int)graph_top,
                (int)x,
                (int)graph_bottom,
                LIGHTGRAY
            );
        }

        // numero centralizado no marcador. Talvez seja bom o usuario decidir se quer ou nao casa decimal
        const char *label = TextFormat("%.0f", value_x);
        int text_width = MeasureText(label, font_size);

        DrawText(
            label,
            (int)(x - text_width / 2),
            (int)(graph_bottom + 12),
            font_size,
            BLACK
        );

        value_x += plane->scale_x;
    }

    // Eixo Y
    int number_of_scale_y =
        (plane->y_min_max[1] - plane->y_min_max[0]) / plane->scale_y;

    if (number_of_scale_y <= 0) {
        return;
    }

    float scale_pixel_y = graph_height / number_of_scale_y;
    float value_y = plane->y_min_max[0];

    for (int i = 0; i <= number_of_scale_y; i++) {
        float y = graph_bottom - i * scale_pixel_y;

        // marcaxodrizn
        DrawRectangle(
            (int)(graph_left - tick_size / 2),
            (int)(y - 1),
            tick_size,
            2,
            BLACK
        );

        // linhas horizontais da grad, somente se quiser
        if (plane->lines && i > 0 && i < number_of_scale_y) {
            DrawLine(
                (int)graph_left,
                (int)y,
                (int)graph_right,
                (int)y,
                LIGHTGRAY
            );
        }

        // Numero alinhado a direita
        const char *label = TextFormat("%.0f", value_y);
        int text_width = MeasureText(label, font_size);

        DrawText(
            label,
            (int)(graph_left - tick_size / 2 - 8 - text_width),
            (int)(y - font_size / 2),
            font_size,
            BLACK
        );

        value_y += plane->scale_y;
    }

    // borda do grafico, tem que vir dps so pra nao ser sobrescrita
    DrawRectangleLines(
        (int)graph_left,
        (int)graph_top,
        (int)graph_width,
        (int)graph_height,
        BLACK
    );
=======
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
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8
}
