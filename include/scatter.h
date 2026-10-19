#ifndef SCATTER_H
#define SCATTER_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void draw_scatter_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

void draw_linear_correlation(Data *data, int data_count, Plane *plane, PlotArea *plot);


void create_scatter(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea,
    bool show_regression

);

#endif
