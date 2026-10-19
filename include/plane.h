#ifndef PLANE_H
#define PLANE_H

#include "plotarea.h"
#include <stdbool.h>

typedef struct {
  float x_min_max[2];
  float scale_x;
  float y_min_max[2];
  float scale_y;
  bool lines;
} Plane;

void draw_plane(Plane *plane, PlotArea *plot_area);

void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

Plane create_plane(float x_min, float x_max, float scale_x, float y_min,
                   float y_max, float scale_y, bool lines);

#endif
