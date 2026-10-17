#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"

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

void create_bar(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea
)
{
    draw_plane(context, plane, plotarea);
    draw_bar_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}

void create_graph(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count
)
{
    InitWindow(context->width, context->height, context->title);
    SetTargetFPS(60);

    PlotArea plot_area = create_plotarea(context);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);


        switch (plane->type) {
            case SCATTER:
                create_scatter(context, plane, data, data_count, &plot_area);
                break;

            case BAR:
                create_bar(context, plane, data, data_count, &plot_area);
                break;

            default:
                break;
        }

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }

    CloseWindow();
}
