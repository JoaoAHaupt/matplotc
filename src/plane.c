#include "plane.h"
#include "plane_draw.h"
#include "plotarea.h"
#include "raylib.h"
#include <math.h>
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

/* Quantidade de intervalos de tamanho `scale` que cabem no plano. A folga
 * relativa evita perder a última marca por erro de ponto flutuante (por
 * exemplo, 1.0 / 0.1 = 9.9999...). */
static int tick_count(float scale, float min_max[2]) {
  float range = min_max[1] - min_max[0];
  if (scale <= 0.0f || range <= 0.0f) {
    return -1;
  }
  return (int)floorf(range / scale + 1e-4f);
}

/* Valor da i-ésima marca. Calculado a partir do mínimo (e não somando o passo
 * a cada marca) para não acumular erro; valores praticamente nulos viram 0
 * para não aparecer algo como "2.98023e-08" no rótulo. */
static float tick_value(float scale, float min_max[2], int i) {
  float value = min_max[0] + (float)i * scale;
  if (fabsf(value) < scale * 1e-4f) {
    value = 0.0f;
  }
  return value;
}

/* Eixo X: marcadores embaixo, valores crescendo da esquerda para a direita.
 * Cada marca fica na posição proporcional ao seu valor, então a escala fica
 * correta mesmo quando o intervalo não é múltiplo do passo. */
void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area) {
  int number_of_scale = tick_count(scale, min_max);
  if (number_of_scale < 0) {
    return;
  }

  float range = min_max[1] - min_max[0];

  for (int i = 0; i <= number_of_scale; i++) {
    float value = tick_value(scale, min_max, i);
    float x = plot_area->left + (value - min_max[0]) / range * plot_area->width;

    DrawRectangle((int)(x - 1), (int)(plot_area->bottom - (float)tick_size / 2),
                  2, tick_size, BLACK);

    /* Grade só no interior (as bordas já são desenhadas por draw_plane). */
    if (lines && x > plot_area->left + 1.0f && x < plot_area->right - 1.0f) {
      DrawLine((int)x, (int)plot_area->top, (int)x, (int)plot_area->bottom,
               LIGHTGRAY);
    }

    const char *label = TextFormat("%g", value);
    int text_width = MeasureText(label, font_size);

    DrawText(label, (int)(x - (float)text_width / 2),
             (int)(plot_area->bottom + 12), font_size, BLACK);
  }
}

/* Eixo Y: marcadores na esquerda, valores crescendo de baixo para cima. */
void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area) {
  int number_of_scale = tick_count(scale, min_max);
  if (number_of_scale < 0) {
    return;
  }

  float range = min_max[1] - min_max[0];

  for (int i = 0; i <= number_of_scale; i++) {
    float value = tick_value(scale, min_max, i);
    float y =
        plot_area->bottom - (value - min_max[0]) / range * plot_area->height;

    DrawRectangle((int)(plot_area->left - (float)tick_size / 2), (int)(y - 1),
                  tick_size, 2, BLACK);

    if (lines && y > plot_area->top + 1.0f && y < plot_area->bottom - 1.0f) {
      DrawLine((int)plot_area->left, (int)y, (int)plot_area->right, (int)y,
               LIGHTGRAY);
    }

    const char *label = TextFormat("%g", value);
    int text_width = MeasureText(label, font_size);

    DrawText(label,
             (int)(plot_area->left - (float)tick_size / 2 - 8 - text_width),
             (int)(y - (float)font_size / 2), font_size, BLACK);
  }
}
