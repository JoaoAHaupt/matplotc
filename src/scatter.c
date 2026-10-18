#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"

void draw_scatter_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];

    for (int j = 0; j < data_count; j++) {
        for (int i = 0; i < data[j].size; i++) {
            float point_x = plot->left +
                (data[j].x[i] - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y = plot->bottom -
                (data[j].y[i] - plane->y_min_max[0]) /
                y_range * plot->height;

            DrawCircle(
                (int)point_x,
                (int)point_y,
                5,
                COLOURS[j]
            );
        }
    }
}

void create_scatter(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
)
{
    draw_plane(context, plane, plotarea);
    draw_scatter_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}
