#ifndef PLOTFJMS_H
#define PLOTFJMS_H

#include "context.h"
#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"

void create_graph(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
);

#endif
