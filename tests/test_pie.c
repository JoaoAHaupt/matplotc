#include "colours.h"
#include "framework.h"
#include "pie.h"
#include "raylib.h"

static float start_angles[8];
static float end_angles[8];
static Color sector_colours[8];
static int sector_count;

void DrawCircleSector(
    Vector2 center,
    float radius,
    float startAngle,
    float endAngle,
    int segments,
    Color color
)
{
  (void)center;
  (void)radius;
  (void)segments;
  if (sector_count < 8) {
    start_angles[sector_count] = startAngle;
    end_angles[sector_count] = endAngle;
    sector_colours[sector_count] = color;
  }
  sector_count++;
}

int main(void)
{
  MT_BEGIN("pie chart");

  int x[] = {1, 3, 11, 5};
  int values[] = {1, 3, 5, 11};
  Data data = {.x = x, .y = values, .size = 4};
  Plane plane = {
      .x_min_max = {0, 10},
      .y_min_max = {0, 10},
  };
  PlotArea plot = {0};

  draw_pie_data(&data, 1, &plane, &plot);

  MT_CHECK_INT(2, sector_count);
  MT_CHECK_FLOAT(0.0f, start_angles[0], 0.001f);
  MT_CHECK_FLOAT(90.0f, end_angles[0], 0.001f);
  MT_CHECK_FLOAT(90.0f, start_angles[1], 0.001f);
  MT_CHECK_FLOAT(360.0f, end_angles[1], 0.001f);
  MT_CHECK_INT(COLOURS[0].r, sector_colours[0].r);
  MT_CHECK_INT(COLOURS[1].b, sector_colours[1].b);

  sector_count = 0;
  int non_positive_values[] = {0, -1};
  int valid_x[] = {1, 2};
  data.x = valid_x;
  data.y = non_positive_values;
  data.size = 2;
  draw_pie_data(&data, 1, &plane, &plot);
  MT_CHECK_INT(0, sector_count);

  return MT_END();
}
