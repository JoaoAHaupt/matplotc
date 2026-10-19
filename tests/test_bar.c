#include "bar.h"
#include "colours.h"
#include "framework.h"
#include "raylib.h"

static Rectangle rectangles[8];
static Color rectangle_colours[8];
static int rectangle_count;
static int outline_count;

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

  reset_draw_calls();
  draw_bar_data(NULL, 2, &plane, &plot);
  MT_CHECK_INT(0, rectangle_count);
  MT_CHECK_INT(0, outline_count);

  return MT_END();
}
