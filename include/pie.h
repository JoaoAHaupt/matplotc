#ifndef PIE_H
#define PIE_H

#include "data.h"
#include "plotarea.h"

void draw_pie_data(Data *data, int data_count);
void create_pie(Data *data, int data_count, PlotArea *plotarea);

#endif
