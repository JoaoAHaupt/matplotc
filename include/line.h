#ifndef LINE_H
#define LINE_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void draw_line_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

void create_line(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
);

#endif
