#include "data.h"
#include "colours.h"
#include "data_draw.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Data create_data(Plane plane, const char *label, float *x,
                 const char *x_axis_label, float *y, const char *y_axis_label,
                 int size) {
  if (size <= 0 || x == NULL || y == NULL) {
    fprintf(stderr, "Error: Invalid data arrays or size.\n");
    return (Data){0};
  }

  if (label == NULL || x_axis_label == NULL || y_axis_label == NULL) {
    fprintf(stderr, "Error: Data labels cannot be NULL.\n");
    return (Data){0};
  }

  Data data = {.plane = plane,
               .label = (char *)label,
               .x = x,
               .x_axis_label = (char *)x_axis_label,
               .y = y,
               .y_axis_label = (char *)y_axis_label,
               .size = size,
               .owns_memory = false};

  return data;
}

void free_data(Data *data) {
  if (data == NULL) {
    return;
  }

  /* Só mexe nos arrays se eles foram alocados por load_data. Em Data vinda
   * de create_data os arrays pertencem ao chamador e não devem ser tocados. */
  if (!data->owns_memory) {
    return;
  }

  free(data->x);
  free(data->y);

  data->x = NULL;
  data->y = NULL;
  data->size = 0;
  data->owns_memory = false;
}

void draw_label(Data *data, Plane *plane, PlotArea *plot) {
  if (data == NULL || plot == NULL) {
    return;
  }

  (void)plane; /* eixo já é desenhado por draw_plane */
  Font font = GetFontDefault();
  float font_size = 20.0f;
  float spacing = 1.0f;

  Vector2 position_x = {plot->left + plot->width / 2, plot->bottom + 35};

  Vector2 origin_x = {
      MeasureTextEx(font, data->x_axis_label, font_size, spacing).x / 2, 0};

  DrawTextPro(font, data->x_axis_label, position_x, origin_x, 0.0f, font_size,
              spacing, BLACK);

  Vector2 position_y = {plot->left - 60, plot->top + plot->height / 2};

  Vector2 origin_y = {
      MeasureTextEx(font, data->y_axis_label, font_size, spacing).x / 2, 0};

  DrawTextPro(font, data->y_axis_label, position_y, origin_y, -90.0f, font_size,
              spacing, BLACK);
}

void draw_legend(Data *data, int data_count, PlotArea *plot) {
  if (data == NULL || plot == NULL || data_count <= 0) {
    return;
  }

  Font font = GetFontDefault();
  float font_size = 16.0f;
  float spacing = 1.0f;

  float box_size = 12.0f;
  float padding = 8.0f;
  float line_height = 24.0f;

  float legend_x = plot->right - 150;
  float legend_y = plot->top + 10;

  for (int i = 0; i < data_count; i++) {
    float y = legend_y + i * line_height;

    // Caixinha colorida
    DrawRectangle((int)legend_x, (int)y, (int)box_size, (int)box_size,
                  COLOURS[i % COLOURS_COUNT]);

    // Nome da série (label pode ser NULL em Data montada à mão)
    if (data[i].label != NULL) {
      DrawTextEx(font, data[i].label,
                 (Vector2){legend_x + box_size + padding, y - 2}, font_size,
                 spacing, BLACK);
    }
  }
}
