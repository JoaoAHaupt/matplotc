#include "bar.h"
#include "context.h"
#include "data.h"
#include "line.h"
#include "pie.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"
#include "scatter.h"
<<<<<<< HEAD
#include "line.h"
#include "pie.h"
#include "bar.h"
#include "hist.h"


=======
>>>>>>> feat/use-continuos-xy-axes

void plot_line(Context *context, Plane *plane, Data *data, int data_count) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_line(plane, data, data_count, &plot_area);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

<<<<<<< HEAD
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
=======
void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);
>>>>>>> feat/use-continuos-xy-axes

  PlotArea plot_area = create_plotarea(context);

<<<<<<< HEAD
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        create_scatter(context, plane, data, data_count, &plot_area, corr);
=======
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_scatter(plane, data, data_count, &plot_area, corr);
>>>>>>> feat/use-continuos-xy-axes

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

void plot_pie(Context *context, Plane *plane, Data *data, int data_count) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_pie(plane, data, data_count, &plot_area);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

void plot_bar(Context *context, Plane *plane, Data *data, int data_count) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_bar(plane, data, data_count, &plot_area);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

void plot_histogram(
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
        create_histogram(context, plane, data, data_count, &plot_area);

        EndDrawing();

        if (IsKeyPressed(KEY_S)) {
            TakeScreenshot("grafico.png");
        }
    }
    CloseWindow();
}
