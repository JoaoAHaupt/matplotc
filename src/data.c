#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"
#include "stdio.h"

void draw_data(Data *data, Plane *plane, PlotArea *plot)
{
    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];


        for (int i = 0; i < data->size; i++) {
            printf("AAAAAAAAAAAAAAAAAAAAA");
            float point_x = plot->left +
                (data->x[i] - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y = plot->bottom -
                (data->y[i] - plane->y_min_max[0]) /
                y_range * plot->height;

            DrawCircle((int)point_x, (int)point_y, 5, RED);

    }
}


void draw_label(Data *data, Plane *plane){}
