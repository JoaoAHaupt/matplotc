#ifndef DATA_H
#define DATA_H

#include "plane.h"

typedef struct {
    Plane plane;
    char *label;
    int *x;
    int *y;
    int size;
} Data;

void draw_data(Data *data, Plane *plane, PlotArea *plot);

#endif
