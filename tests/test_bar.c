#include "bar.h"
#include "colours.h"
#include "framework.h"
#include "raylib.h"
#include <stdarg.h>
#include <stdio.h>

static Rectangle rectangles[8];
static Color rectangle_colours[8];
static int rectangle_count;
static int outline_count;
static int axis_tick_x[16];
static int axis_tick_count;
static int x_label_x[16];
static int x_label_count;

void DrawRectangleRec(Rectangle rec, Color color)
{
  if (rectangle_count < 8) {
    rectangles[rectangle_count] = rec;
    rectangle_colours[rectangle_count] = color;
  }
  rectangle_count++;
}

void DrawRectangleLinesEx(Rectangle rec, float line_thick, Color color)
{
  (void)rec;
  (void)line_thick;
  (void)color;
  outline_count++;
}

void DrawRectangle(int posX, int posY, int width, int height, Color color)
{
  (void)posY;
  (void)color;
  if (width == 2 && height == 10 && axis_tick_count < 16) {
    axis_tick_x[axis_tick_count++] = posX;
  }
}

void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color)
{
  (void)startPosX;
  (void)startPosY;
  (void)endPosX;
  (void)endPosY;
  (void)color;
}

void DrawRectangleLines(int posX, int posY, int width, int height, Color color)
{
  (void)posX;
  (void)posY;
  (void)width;
  (void)height;
  (void)color;
}

const char *TextFormat(const char *text, ...)
{
  static char buffer[128];
  va_list args;
  va_start(args, text);
  vsnprintf(buffer, sizeof(buffer), text, args);
  va_end(args);
  return buffer;
}

int MeasureText(const char *text, int fontSize)
{
  (void)text;
  (void)fontSize;
  return 10;
}

void DrawText(const char *text, int posX, int posY, int fontSize, Color color)
{
  (void)text;
  (void)fontSize;
  (void)color;
  if (posY == 132 && x_label_count < 16) {
    x_label_x[x_label_count++] = posX;
  }
}

static void reset_draw_calls(void)
{
  rectangle_count = 0;
  outline_count = 0;
}

int main(void)
{
  MT_BEGIN("bar graph");

  int x[] = {5};
  int y_first[] = {8};
  int y_second[] = {4};
  Data data[] = {
      {.x = x, .y = y_first, .size = 1},
      {.x = x, .y = y_second, .size = 1},
  };
  Plane plane = {
      .x_min_max = {0, 10},
      .y_min_max = {0, 10},
  };
  PlotArea plot = {
      .left = 10.0f,
      .right = 110.0f,
      .top = 20.0f,
      .bottom = 120.0f,
      .width = 100.0f,
      .height = 100.0f,
  };

  draw_bar_data(data, 2, &plane, &plot);

  MT_CHECK_INT(2, rectangle_count);
  MT_CHECK_INT(2, outline_count);
  MT_CHECK_FLOAT(20.0f, rectangles[0].x, 0.001f);
  MT_CHECK_FLOAT(40.0f, rectangles[0].width, 0.001f);
  MT_CHECK_FLOAT(40.0f, rectangles[0].y, 0.001f);
  MT_CHECK_FLOAT(80.0f, rectangles[0].height, 0.001f);
  MT_CHECK_FLOAT(60.0f, rectangles[1].x, 0.001f);
  MT_CHECK_FLOAT(40.0f, rectangles[1].width, 0.001f);
  MT_CHECK_FLOAT(40.0f, rectangles[1].height, 0.001f);
  MT_CHECK_INT(COLOURS[0].r, rectangle_colours[0].r);
  MT_CHECK_INT(COLOURS[1].b, rectangle_colours[1].b);

  int edge_x[] = {0, 2, 8, 10};
  int edge_y[] = {5, 5, 5, 5};
  Data edge_data = {.x = edge_x, .y = edge_y, .size = 4};
  reset_draw_calls();
  draw_bar_data(&edge_data, 1, &plane, &plot);
  MT_CHECK_INT(4, rectangle_count);
  MT_CHECK_FLOAT(12.0f, rectangles[0].x, 0.001f);
  MT_CHECK_FLOAT(16.0f, rectangles[0].width, 0.001f);
  MT_CHECK_FLOAT(92.0f, rectangles[3].x, 0.001f);
  MT_CHECK_FLOAT(16.0f, rectangles[3].width, 0.001f);

  Plane axis_plane = {
      .x_min_max = {0, 10},
      .scale_x = 2.0f,
      .y_min_max = {0, 10},
      .scale_y = 2.0f,
  };
  axis_tick_count = 0;
  x_label_count = 0;
  draw_plane_with_x_inset(NULL, &axis_plane, &plot, 10.0f);
  MT_CHECK_INT(6, axis_tick_count);
  MT_CHECK_INT(6, x_label_count);
  for (int i = 0; i < 6; i++) {
    MT_CHECK_INT(19 + i * 16, axis_tick_x[i]);
    MT_CHECK_INT(15 + i * 16, x_label_x[i]);
  }

  int mixed_x[] = {5, 5, 5, 11};
  int mixed_y[] = {8, 11, -1, 4};
  Data mixed_data = {.x = mixed_x, .y = mixed_y, .size = 4};
  reset_draw_calls();
  draw_bar_data(&mixed_data, 1, &plane, &plot);
  MT_CHECK_INT(1, rectangle_count);
  MT_CHECK_INT(1, outline_count);
  MT_CHECK_FLOAT(20.0f, rectangles[0].x, 0.001f);
  MT_CHECK_FLOAT(80.0f, rectangles[0].height, 0.001f);

  reset_draw_calls();
  draw_bar_data(NULL, 2, &plane, &plot);
  MT_CHECK_INT(0, rectangle_count);
  MT_CHECK_INT(0, outline_count);

  return MT_END();
}
