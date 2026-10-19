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

#endif
