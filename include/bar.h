#ifndef BAR_H
#define BAR_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot);

void create_bar(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif
