#ifndef SCATTER_H
#define SCATTER_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

void draw_scatter_data(Data *data, int data_count, Plane *plane,
                       PlotArea *plot);

void create_scatter(Plane *plane, Data *data, int data_count,
                    PlotArea *plotarea, bool show_regression);

void draw_linear_correlation(Data *data, int data_count, Plane *plane,
                             PlotArea *plot);

#endif
