#include "colours.h"
#include "framework.h"
#include "raylib.h"
#include "scatter.h"

static int circle_x[8];
static int circle_y[8];
static Color circle_colours[8];
static int circle_count;
static Vector2 line_start;
static Vector2 line_end;
static int line_count;

void DrawCircle(int centerX, int centerY, float radius, Color color)
{
  (void)radius;
  if (circle_count < 8) {
    circle_x[circle_count] = centerX;
    circle_y[circle_count] = centerY;
    circle_colours[circle_count] = color;
  }
  circle_count++;
}

void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
{
  (void)thick;
  (void)color;
  line_start = startPos;
  line_end = endPos;
  line_count++;
}

int main(void)
{
  MT_BEGIN("scatter plot and regression");

  int x[] = {0, 10, -1, 5, 5};
  int y[] = {0, 10, 5, 11, -1};
  Data data = {.x = x, .y = y, .size = 5};
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

  draw_scatter_data(&data, 1, &plane, &plot);
  MT_CHECK_INT(2, circle_count);
  MT_CHECK_INT(10, circle_x[0]);
  MT_CHECK_INT(120, circle_y[0]);
  MT_CHECK_INT(110, circle_x[1]);
  MT_CHECK_INT(20, circle_y[1]);
  MT_CHECK_INT(COLOURS[0].r, circle_colours[0].r);

  draw_linear_correlation(&data, 1, &plane, &plot);
  MT_CHECK_INT(1, line_count);
  MT_CHECK_FLOAT(10.0f, line_start.x, 0.001f);
  MT_CHECK_FLOAT(120.0f, line_start.y, 0.001f);
  MT_CHECK_FLOAT(110.0f, line_end.x, 0.001f);
  MT_CHECK_FLOAT(20.0f, line_end.y, 0.001f);

  int clipped_x[] = {4, 6};
  int clipped_y[] = {0, 10};
  data.x = clipped_x;
  data.y = clipped_y;
  data.size = 2;
  line_count = 0;
  draw_linear_correlation(&data, 1, &plane, &plot);
  MT_CHECK_INT(1, line_count);
  MT_CHECK_FLOAT(50.0f, line_start.x, 0.001f);
  MT_CHECK_FLOAT(120.0f, line_start.y, 0.001f);
  MT_CHECK_FLOAT(70.0f, line_end.x, 0.001f);
  MT_CHECK_FLOAT(20.0f, line_end.y, 0.001f);

  line_count = 0;
  plane.x_min_max[1] = plane.x_min_max[0];
  draw_linear_correlation(&data, 1, &plane, &plot);
  MT_CHECK_INT(0, line_count);

  return MT_END();
}
