#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"
#include "math.h"
void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    float x_min = plane->x_min_max[0];
    float y_min = plane->y_min_max[0];
    float y_max = plane->y_min_max[1];
    float x_range = plane->x_min_max[1] - x_min;
    float y_range = y_max - y_min;

    // Menor distância entre dois x consecutivos: define a "fatia" de cada grupo de barras
    float min_step = x_range;
    for (int j = 0; j < data_count; j++) {
        for (int i = 1; i < data[j].size; i++) {
            float d = fabsf((float)(data[j].x[i] - data[j].x[i - 1]));
            if (d > 0 && d < min_step) min_step = d;
        }
    }

    float slot_w  = min_step / x_range * plot->width;  // largura reservada por grupo
    float group_w = slot_w * 0.8f;                     // 20% de respiro entre grupos
    float bar_w   = group_w / data_count;              // séries lado a lado

    // Linha de base das barras: y = 0, limitado ao intervalo visível
    float base_val = fminf(fmaxf(0.0f, y_min), y_max);
    float base_y = plot->bottom - (base_val - y_min) / y_range * plot->height;

    for (int j = 0; j < data_count; j++) {
        for (int i = 0; i < data[j].size; i++) {
            float center_x = plot->left +
                (data[j].x[i] - x_min) / x_range * plot->width;

            float bar_x = center_x - group_w / 2.0f + j * bar_w;

            float value_y = plot->bottom -
                (data[j].y[i] - y_min) / y_range * plot->height;

            // Não deixa a barra sair da área do gráfico
            value_y = fminf(fmaxf(value_y, plot->top), plot->bottom);

            Rectangle bar = {
                bar_x,
                fminf(value_y, base_y),      // funciona para valores negativos também
                bar_w,
                fabsf(base_y - value_y)
            };

            DrawRectangleRec(bar, COLOURS[j]);
            DrawRectangleLinesEx(bar, 1.0f, BLACK);
        }
    }
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
