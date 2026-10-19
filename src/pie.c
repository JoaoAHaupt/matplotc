#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"
#include <stddef.h>

void draw_pie_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0]) {
        return;
    }

    float total = 0;
    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            int x = data[j].x[i];
            int y = data[j].y[i];
            if (x >= plane->x_min_max[0] && x <= plane->x_min_max[1] &&
                y >= plane->y_min_max[0] && y <= plane->y_min_max[1]) {
                total += y;
            }
        }
    }

    if (total <= 0) return;

    float start_angle = 0;

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            int x = data[j].x[i];
            int y = data[j].y[i];
            if (x < plane->x_min_max[0] || x > plane->x_min_max[1] ||
                y < plane->y_min_max[0] || y > plane->y_min_max[1]) {
                continue;
            }

            float angle = ((float)y / total) * 360.0f;

            DrawCircleSector(
                (Vector2){400, 400},
                150,
                start_angle,
                start_angle + angle,
                32,
                COLOURS[i % (sizeof(COLOURS) / sizeof(COLOURS[0]))]
            );

            start_angle += angle;
        }
    }
}

void create_pie(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
)
{
    draw_plane(context, plane, plotarea);
    draw_pie_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}
