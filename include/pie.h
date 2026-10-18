#ifndef PIE_H
#define PIE_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void draw_pie_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

void create_pie(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
);

#endif
