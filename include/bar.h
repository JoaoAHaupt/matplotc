#ifndef BAR_H
#define BAR_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void draw_bar_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

void create_bar(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif
