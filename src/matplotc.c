/**
 * @file matplotc.c
 * @brief Implementação das funções de plotagem da API pública (ver matplotc.h).
 *
 * Todas as funções seguem o mesmo fluxo: abrem a janela, criam a área de
 * plotagem e, a cada quadro (60 FPS), limpam o fundo e desenham o gráfico.
 * A tecla S salva uma captura em `grafico.png`.
 */

#include "matplotc.h"
#include "bar.h"
#include "context.h"
#include "data.h"
#include "hist.h"
#include "line.h"
#include "pie.h"
#include "plane.h"
#include "plotarea.h"
#include "raylib.h"
#include "scatter.h"

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

void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_scatter(plane, data, data_count, &plot_area, corr);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

void plot_pie(Context *context, Data *data, int data_count) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_pie(data, data_count, &plot_area);

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

void plot_histogram(Context *context, Plane *plane, Data *data, int data_count) {
  InitWindow(context->width, context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    create_histogram(plane, data, data_count, &plot_area);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}
