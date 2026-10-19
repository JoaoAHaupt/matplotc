#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "scatter.h"
#include "line.h"
#include "pie.h"
#include "bar.h"



void plot_line(
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
        create_line(context, plane, data, data_count, &plot_area);

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }
    CloseWindow();
}

void plot_scatter(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    bool corr
)
{
    InitWindow(context->width, context->height, context->title);
    SetTargetFPS(60);

    PlotArea plot_area = create_plotarea(context);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        create_scatter(context, plane, data, data_count, &plot_area, corr);

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }
    CloseWindow();
}

void plot_pie(
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
        create_pie(context, plane, data, data_count, &plot_area);

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }
    CloseWindow();
}

void plot_bar(
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
        create_bar(context, plane, data, data_count, &plot_area);

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }
    CloseWindow();
}
