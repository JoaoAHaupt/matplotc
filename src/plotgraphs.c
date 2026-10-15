#include "context.h"
#include "data.h"
#include "plane.h"
#include "plotarea.h"
#include "plotgraphs.h"
#include "raylib.h"
#include "stdio.h"

void plot_scatter_graph(Data *data, Plane *plane, PlotArea *plot, Color color)
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

            DrawCircle((int)point_x, (int)point_y, 5, color);

    }
}

// pra documentacao: int filled deve ser preenchido com 0 se false e 1 se true
void plot_bar_graph(Data *data, Plane *plane, PlotArea *plot, int filled, Color color)
{
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];
    int size = data->size;
    float bar_width = plot->width / size;

    for (int i = 0; i < size; i++) {
        int coordinates[2] = {data->x[i], data->y[i]};

        float bar_x = plot->left + i * bar_width;
        float bar_y = plot->bottom -
                (coordinates[1] - plane->y_min_max[0]) /
                y_range * plot->height;
        float bar_height = plot->bottom - bar_y;

        if (filled) {
            DrawRectangle((int)bar_x, 
                          (int)bar_y,
                          (int)bar_width,
                          (int)bar_height,
                          color);
            DrawRectangleLines((int)bar_x, 
                               (int)bar_y,
                               (int)bar_width,
                               (int)bar_height,
                               BLACK);
        }
        else {
            DrawRectangleLines((int)bar_x, 
                               (int)bar_y,
                               (int)bar_width,
                               (int)bar_height,
                               color);
        }
        printf(".");
    }
}

void plot_bar_graph_intervals(Structured_Data *struct_data, Plane *plane, PlotArea *plot, int filled, Color color)
{
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];
    int size = struct_data->size;
    float bar_width = plot->width / size;

    for (int i = 0; i < size; i++) {
        Range intervalo = struct_data->intervals[i]; 
        int coordinates[2] = {intervalo.first_value[0], intervalo.first_value[1]};

        float bar_x = plot->left + i * bar_width;
        float bar_y = plot->bottom -
                (coordinates[1] - plane->y_min_max[0]) /
                y_range * plot->height;
        float bar_height = plot->bottom - bar_y;

        if (filled) {
            DrawRectangle((int)bar_x, 
                          (int)bar_y,
                          (int)bar_width,
                          (int)bar_height,
                          color);
            DrawRectangleLines((int)bar_x, 
                               (int)bar_y,
                               (int)bar_width,
                               (int)bar_height,
                               BLACK);
        }
        else {
            DrawRectangleLines((int)bar_x, 
                               (int)bar_y,
                               (int)bar_width,
                               (int)bar_height,
                               color);
        }
        printf(".");
    }
}

void draw_labels(Data *data, Plane *plane){
    if (plane->type == SCATTER) {} // dividir pelo tipo aqui dentro?
    // ou fazer uma funcao draw label diferente pra cada tipo de grafico?
    // ou ja colocar os rotulos dentro de cada funcao plot_graph?
}