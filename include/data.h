#ifndef DATA_H
#define DATA_H

#include "plane.h"

typedef struct {
    Plane plane; // isso ta sendo usado em algum momento? 
    // pq todas as funcoes que usam Data e StructuredData ja pegam o plane como argumento
    char *label;
    int *x;
    int *y;
    int size;
} Data;

typedef struct {
    char *label;
    int first_value[2];
    int height;
} Range;

typedef struct {
    Plane plane;
    char *label;
    Range *intervals;
    int width;
    int size;
} Structured_Data;

Structured_Data set_intervals_q(Data *data, int quantity);
Structured_Data set_intervals_s(Data *data, int size);

#endif