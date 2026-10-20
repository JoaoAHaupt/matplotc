#ifndef PLANE_H
#define PLANE_H

#include <stdbool.h>

typedef struct {
  float x_min_max[2];
  float scale_x;
  float y_min_max[2];
  float scale_y;
  bool lines;
} Plane;

Plane create_plane(float x_min, float x_max, float scale_x, float y_min,
                   float y_max, float scale_y, bool lines);

#endif
