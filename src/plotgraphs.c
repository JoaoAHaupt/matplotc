#include "raylib.h"
#include "context.h"
#include "plotarea.h"
#include "plane.h"
#include "data.h"
#include "plotgraphs.h"

void plot_scatter_graph(Data *data, Plane *plane, PlotArea *plot)
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

// ainda no processo!!!
void plot_bar_graph(Data *data, Plane *plane, int filled, int numerical, Color color) {
}

void draw_labels(Data *data, Plane *plane){
    if (plane->type == SCATTER) {} // dividir pelo tipo?
    // da pra colocar os rotulos dentro de cada uma das funcoes plot tbm
}