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
#include <stddef.h>
#include <stdio.h>

typedef enum {
  PLOT_LINE,
  PLOT_SCATTER,
  PLOT_BAR,
  PLOT_PIE,
  PLOT_HIST,
} PlotType;

typedef struct {
  PlotType type;
  Plane *plane;
  Data *data;
  int data_count;
  bool corr;
} PendingPlot;

static PendingPlot pending = {0};
static bool has_pending = false;

static void draw_frame(PlotArea *plot_area) {
  switch (pending.type) {
  case PLOT_LINE:
    create_line(pending.plane, pending.data, pending.data_count, plot_area);
    break;
  case PLOT_SCATTER:
    create_scatter(pending.plane, pending.data, pending.data_count, plot_area,
                   pending.corr);
    break;
  case PLOT_BAR:
    create_bar(pending.plane, pending.data, pending.data_count, plot_area);
    break;
  case PLOT_PIE:
    create_pie(pending.data, pending.data_count, plot_area);
    break;
  case PLOT_HIST:
    create_histogram(pending.plane, pending.data, pending.data_count,
                     plot_area);
    break;
  }
}

void show(Context *context) {
  if (context == NULL) {
    return;
  }

  if (!has_pending) {
    fprintf(stderr, "Error: nothing to show, call a plot_* function first.\n");
    return;
  }

  InitWindow((int)context->width, (int)context->height, context->title);
  /* export_png liga FLAG_WINDOW_HIDDEN e a raylib mantém as flags entre
   * janelas; sem isto, um show() depois de export_png abriria uma janela
   * invisível que não pode ser fechada. */
  ClearWindowState(FLAG_WINDOW_HIDDEN);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_frame(&plot_area);

    EndDrawing();

    if (IsKeyPressed(KEY_S)) {
      TakeScreenshot("grafico.png");
    }
  }
  CloseWindow();
}

bool export_png(Context *context, const char *filename) {
  if (context == NULL || filename == NULL || filename[0] == '\0') {
    return false;
  }

  if (!has_pending) {
    fprintf(stderr,
            "Error: nothing to export, call a plot_* function first.\n");
    return false;
  }

  /* Janela oculta: a raylib precisa de um contexto gráfico para renderizar,
   * mas não precisa aparecer na tela. show() desfaz a flag, então
   * export_png e show podem ser chamados em qualquer ordem. */
  SetConfigFlags(FLAG_WINDOW_HIDDEN);
  InitWindow((int)context->width, (int)context->height, context->title);
  SetTargetFPS(60);

  PlotArea plot_area = create_plotarea(context);

  BeginDrawing();
  ClearBackground(RAYWHITE);
  draw_frame(&plot_area);
  EndDrawing();

  Image image = LoadImageFromScreen();
  bool ok = ExportImage(image, filename);
  UnloadImage(image);
  CloseWindow();

  if (!ok) {
    fprintf(stderr, "Error: Could not export image to '%s'.\n", filename);
  }

  return ok;
}

void plot_line(Context *context, Plane *plane, Data *data, int data_count) {
  if (context == NULL || plane == NULL || data == NULL || data_count <= 0) {
    return;
  }

  pending = (PendingPlot){.type = PLOT_LINE,
                          .plane = plane,
                          .data = data,
                          .data_count = data_count,
                          .corr = false};
  has_pending = true;
}

void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr) {
  if (context == NULL || plane == NULL || data == NULL || data_count <= 0) {
    return;
  }

  pending = (PendingPlot){.type = PLOT_SCATTER,
                          .plane = plane,
                          .data = data,
                          .data_count = data_count,
                          .corr = corr};
  has_pending = true;
}

void plot_pie(Context *context, Data *data, int data_count) {
  /* Gráfico de pizza não usa o plano cartesiano. */
  if (context == NULL || data == NULL || data_count <= 0) {
    return;
  }

  pending = (PendingPlot){.type = PLOT_PIE,
                          .plane = NULL,
                          .data = data,
                          .data_count = data_count,
                          .corr = false};
  has_pending = true;
}

void plot_bar(Context *context, Plane *plane, Data *data, int data_count) {
  if (context == NULL || plane == NULL || data == NULL || data_count <= 0) {
    return;
  }

  pending = (PendingPlot){.type = PLOT_BAR,
                          .plane = plane,
                          .data = data,
                          .data_count = data_count,
                          .corr = false};
  has_pending = true;
}

void plot_histogram(Context *context, Plane *plane, Data *data,
                    int data_count) {
  if (context == NULL || plane == NULL || data == NULL || data_count <= 0) {
    return;
  }

  pending = (PendingPlot){.type = PLOT_HIST,
                          .plane = plane,
                          .data = data,
                          .data_count = data_count,
                          .corr = false};
  has_pending = true;
}
