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

<<<<<<< HEAD
void draw_plane(Context *context, Plane *plane, PlotArea *plot);
void draw_plane_with_x_inset(
    Context *context,
    Plane *plane,
    PlotArea *plot,
    float x_inset
);
=======
void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

Plane create_plane(float x_min, float x_max, float scale_x, float y_min,
                   float y_max, float scale_y, bool lines);
>>>>>>> 76782c276986f9369752c276a9f8d1f344ff99e8

#endif
