#ifndef PLOTFJMS_H
#define PLOTFJMS_H

#include "context.h"
#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"

void plot_line(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
);

void plot_scatter(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
);

void plot_pie(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
);

void plot_bar(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
);

#endif
