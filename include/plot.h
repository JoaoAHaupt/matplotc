#ifndef PLOT_H
#define PLOT_H

#include "context.h"
#include "plane.h"
#include "data.h"
#include "plotarea.h"

void create_graph(Context *context, Plane *plane, Data *data, int data_count);

void create_scatter(Context *context, Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif
