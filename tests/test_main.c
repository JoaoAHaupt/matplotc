#include "framework.h"
#include "context.h"
#include "plane.h"

int main(void) {
  MT_BEGIN("context and plane constructors");

  Context context = create_context(800.0f, 600.0f, "test");
  MT_CHECK_FLOAT(800.0f, context.width, 0.001f);
  MT_CHECK_FLOAT(600.0f, context.height, 0.001f);
  MT_CHECK_STR("test", context.title);

  context = create_context(0.0f, 600.0f, "test");
  MT_CHECK_FLOAT(0.0f, context.width, 0.001f);
  MT_CHECK_FLOAT(0.0f, context.height, 0.001f);
  MT_CHECK(context.title == NULL);

  context = create_context(800.0f, -1.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(-1.0f, 600.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 0.0f, "test");
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 600.0f, NULL);
  MT_CHECK(context.title == NULL);
  context = create_context(800.0f, 600.0f, "");
  MT_CHECK(context.title == NULL);

  Plane plane = create_plane(-10, 10, 2.0f, -20, 20, 5.0f, true);
  MT_CHECK_INT(-10, plane.x_min_max[0]);
  MT_CHECK_INT(10, plane.x_min_max[1]);
  MT_CHECK_FLOAT(2.0f, plane.scale_x, 0.001f);
  MT_CHECK_INT(-20, plane.y_min_max[0]);
  MT_CHECK_INT(20, plane.y_min_max[1]);
  MT_CHECK_FLOAT(5.0f, plane.scale_y, 0.001f);
  MT_CHECK(plane.lines);

  plane = create_plane(5, 5, 1.0f, 0, 10, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[0]);
  MT_CHECK_INT(0, plane.y_min_max[1]);
  plane = create_plane(0, 10, 1.0f, 5, 5, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[1]);

  plane = create_plane(10, 0, 1.0f, 0, 10, 1.0f, false);
  MT_CHECK_INT(0, plane.x_min_max[1]);
  plane = create_plane(0, 10, 1.0f, 10, 0, 1.0f, false);
  MT_CHECK_INT(0, plane.y_min_max[1]);

  plane = create_plane(0, 10, 0.0f, 0, 10, 1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_x, 0.001f);
  plane = create_plane(0, 10, -1.0f, 0, 10, 1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_x, 0.001f);
  plane = create_plane(0, 10, 1.0f, 0, 10, 0.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_y, 0.001f);
  plane = create_plane(0, 10, 1.0f, 0, 10, -1.0f, false);
  MT_CHECK_FLOAT(0.0f, plane.scale_y, 0.001f);

  return MT_END();
}
