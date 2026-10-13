#ifndef PLANE_H
#define PLANE_H

#include "raylib.h"
#include "context.h"
#include "plotarea.h"

enum Graph {
    PIE,
    BAR,
    LINE,
    SCATTER
};

typedef struct {
    enum Graph type;
    int x_min_max[2];
    float scale_x;
    int y_min_max[2];
    float scale_y;
    bool lines;
} Plane;

void draw_plane(Context *context, Plane *plane, PlotArea *plot);

#endif
