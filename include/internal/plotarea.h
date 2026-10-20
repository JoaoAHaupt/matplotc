#ifndef PLOTAREA_H
#define PLOTAREA_H

#include "context.h"

typedef struct {
    float padding_left;
    float padding_right;
    float padding_top;
    float padding_bottom;

    float width;
    float height;

    float left;
    float right;
    float top;
    float bottom;
} PlotArea;

PlotArea create_plotarea(Context *context);

#endif
