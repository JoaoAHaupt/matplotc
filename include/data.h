#ifndef DATA_H
#define DATA_H

#include "plane.h"

typedef struct {
  Plane plane;
  char *label;

  float *x;
  char *x_axis_label;

  float *y;
  char *y_axis_label;

  int size;
} Data;

Data create_data(Plane plane, const char *label, float *x,
                 const char *x_axis_label, float *y, const char *y_axis_label,
                 int size);

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_pie_data(Data *data, int data_count);
void draw_label(Data *data, Plane *plane, PlotArea *plot);
void draw_legend(Data *data, int data_count, PlotArea *plot);
int data_size(Data *data);

#endif
