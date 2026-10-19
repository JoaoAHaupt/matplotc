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

Data create_data(
    Plane plane,
    const char *label,
    int *x,
    const char *x_axis_label,
    int *y,
    const char *y_axis_label,
    int size
);

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_pie_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_label(Data *data, Plane *plane, PlotArea *plot);
void draw_legend(Data *data, int data_count, PlotArea *plot);
int data_size(Data *data);

#endif
