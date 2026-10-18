#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"

void draw_pie_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    float total = 0;
    // soma ytudo
    for (int j = 0; j < data_count; j++) {
        for (int i = 0; i < data[j].size; i++) {
            total += data[j].y[i];
        }
    }

    if (total <= 0) return;

    float start_angle = 0;

    for (int j = 0; j < data_count; j++) {
        for (int i = 0; i < data[j].size; i++) {
            // calcula o angulo
            float angle = (data[j].y[i] / total) * 360.0f;

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
