#ifndef MATPLOTC_H
#define MATPLOTC_H

#include "context.h"
#include "data.h"
#include "plane.h"

void plot_line(Context *context, Plane *plane, Data *data, int data_count);
void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr);
void plot_pie(Context *context, Plane *plane, Data *data, int data_count);
void plot_bar(Context *context, Plane *plane, Data *data, int data_count);

#endif
