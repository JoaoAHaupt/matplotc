#ifndef DATA_H
#define DATA_H

#include "plane.h"

typedef struct {
    Plane plane;
    char *label;

    int *x;
    char *x_axis_label;

    int *y;
    char *y_axis_label;

    int size;
} Data;

void draw_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_label(Data *data, Plane *plane, PlotArea *plot);
void draw_legend(Data *data, int data_count, PlotArea *plot);
int data_size(Data *data);

#endif
