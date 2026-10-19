#ifndef HIST_H
#define HIST_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

void draw_hist_data(Data *data, int data_count, Plane *plane, PlotArea *plot);

void create_histogram(Plane *plane, Data *data, int data_count,
                      PlotArea *plotarea);

#endif
