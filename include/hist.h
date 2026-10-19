#ifndef HIST_H
#define HIST_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void draw_hist_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

void create_histogram(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
);

#endif
