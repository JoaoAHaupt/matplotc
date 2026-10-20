#include "plotarea.h"
#include <stddef.h>

PlotArea create_plotarea(Context *context) {
  if (context == NULL || context->width <= 0.0f || context->height <= 0.0f) {
    return (PlotArea){0};
  }

  PlotArea area;

  area.padding_left = context->width * 0.10f;
  area.padding_right = context->width * 0.05f;
  area.padding_top = context->height * 0.05f;
  area.padding_bottom = context->height * 0.075f;

  if (area.padding_left < 50)
    area.padding_left = 50;
  if (area.padding_left > 100)
    area.padding_left = 100;

  if (area.padding_right < 25)
    area.padding_right = 25;
  if (area.padding_right > 60)
    area.padding_right = 60;

  if (area.padding_top < 25)
    area.padding_top = 25;
  if (area.padding_top > 60)
    area.padding_top = 60;

  if (area.padding_bottom < 40)
    area.padding_bottom = 40;
  if (area.padding_bottom > 80)
    area.padding_bottom = 80;

  area.left = area.padding_left;
  area.top = area.padding_top;

  area.width = context->width - area.padding_left - area.padding_right;

  area.height = context->height - area.padding_top - area.padding_bottom;

  area.right = area.left + area.width;
  area.bottom = area.top + area.height;

  return area;
}
