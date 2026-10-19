#include "colours.h"
#include "framework.h"
#include "line.h"
#include "raylib.h"

static Vector2 line_starts[8];
static Vector2 line_ends[8];
static Color line_colours[8];
static float line_widths[8];
static int line_count;

void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color)
{
  if (line_count < 8) {
    line_starts[line_count] = startPos;
    line_ends[line_count] = endPos;
    line_widths[line_count] = thick;
    line_colours[line_count] = color;
  }
  line_count++;
}

int main(void)
{
  MT_BEGIN("line graph");

  int x[] = {0, 5, 10, 11, 5, 5};
  int y[] = {0, 5, 10, 5, 11, -1};
  Data data = {.x = x, .y = y, .size = 6};
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

  draw_line_data(&data, 1, &plane, &plot);

  MT_CHECK_INT(2, line_count);
  MT_CHECK_FLOAT(10.0f, line_starts[0].x, 0.001f);
  MT_CHECK_FLOAT(120.0f, line_starts[0].y, 0.001f);
  MT_CHECK_FLOAT(60.0f, line_ends[0].x, 0.001f);
  MT_CHECK_FLOAT(70.0f, line_ends[0].y, 0.001f);
  MT_CHECK_FLOAT(110.0f, line_ends[1].x, 0.001f);
  MT_CHECK_FLOAT(20.0f, line_ends[1].y, 0.001f);
  MT_CHECK_FLOAT(3.0f, line_widths[0], 0.001f);
  MT_CHECK_INT(COLOURS[0].g, line_colours[0].g);

  return MT_END();
}
