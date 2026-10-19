#include "colours.h"
#include "framework.h"
#include "hist.h"
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

int main(void)
{
  MT_BEGIN("histogram");

  int samples[] = {1, 1, 4, 10};
  Data data = {.x = samples, .size = 4};
  Plane plane = {
      .x_min_max = {0, 10},
      .scale_x = 2.0f,
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

  draw_hist_data(&data, 1, &plane, &plot);

  MT_CHECK_INT(3, rectangle_count);
  MT_CHECK_INT(3, outline_count);
  MT_CHECK_FLOAT(10.0f, rectangles[0].x, 0.001f);
  MT_CHECK_FLOAT(20.0f, rectangles[0].width, 0.001f);
  MT_CHECK_FLOAT(100.0f, rectangles[0].y, 0.001f);
  MT_CHECK_FLOAT(20.0f, rectangles[0].height, 0.001f);
  MT_CHECK_FLOAT(50.0f, rectangles[1].x, 0.001f);
  MT_CHECK_FLOAT(10.0f, rectangles[1].height, 0.001f);
  MT_CHECK_FLOAT(90.0f, rectangles[2].x, 0.001f);
  MT_CHECK_FLOAT(10.0f, rectangles[2].height, 0.001f);
  MT_CHECK_INT(COLOURS[0].r, rectangle_colours[0].r);

  rectangle_count = 0;
  outline_count = 0;
  plane.scale_x = 0.0f;
  draw_hist_data(&data, 1, &plane, &plot);
  MT_CHECK_INT(0, rectangle_count);
  MT_CHECK_INT(0, outline_count);

  return MT_END();
}
