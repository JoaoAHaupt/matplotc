#ifndef PLANE_H
#define PLANE_H

#include "raylib.h"
#include "context.h"
#include "plotarea.h"

typedef struct {
    int x_min_max[2];
    float scale_x;
    int y_min_max[2];
    float scale_y;
    bool lines;
} Plane;

Plane create_plane(
    int x_min,
    int x_max,
    float scale_x,
    int y_min,
    int y_max,
    float scale_y,
    bool lines
);

void draw_plane(Context *context, Plane *plane, PlotArea *plot);
void draw_plane_with_x_inset(
    Context *context,
    Plane *plane,
    PlotArea *plot,
    float x_inset
);

#endif
