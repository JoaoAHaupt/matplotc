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

typedef struct {
    char *label;
    int first_value[2];
    int width;
    int height;
} Range;

typedef struct {
    Plane plane;
    char *label;
    Range *intervals;
    int size;
} Structured_Data;

Structured_Data set_intervals_q(Data *data, int quantity);
Structured_Data set_intervals_s(Data *data, int size);

#endif