#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"
#include <math.h>

const Color COLOURS[] = {
    RED,
    BLUE,
    GREEN,
    ORANGE,
    PURPLE,
    MAROON,
    DARKBLUE,
    DARKGREEN
};

int data_size(Data *data){
    return sizeof(data)/sizeof(data[0]);
}

void draw_label(Data *data, Plane *plane, PlotArea *plot)
{
    Font font = GetFontDefault();
    float font_size = 20.0f;
    float spacing = 1.0f;

    Vector2 position_x = {
        plot->left + plot->width / 2,
        plot->bottom + 35
    };

    Vector2 origin_x = {
        MeasureTextEx(font, data->x_axis_label, font_size, spacing).x / 2,
        0
    };

    DrawTextPro(
        font,
        data->x_axis_label,
        position_x,
        origin_x,
        0.0f,
        font_size,
        spacing,
        BLACK
    );

    Vector2 position_y = {
        plot->left - 60,
        plot->top + plot->height / 2
    };

    Vector2 origin_y = {
        MeasureTextEx(font, data->y_axis_label, font_size, spacing).x / 2,
        0
    };

    DrawTextPro(
        font,
        data->y_axis_label,
        position_y,
        origin_y,
        -90.0f,
        font_size,
        spacing,
        BLACK
    );
}

void draw_legend(Data *data, int data_count, PlotArea *plot)
{
    Font font = GetFontDefault();
    float font_size = 16.0f;
    float spacing = 1.0f;

    float box_size = 12.0f;
    float padding = 8.0f;
    float line_height = 24.0f;

    float legend_x = plot->right - 150;
    float legend_y = plot->top + 10;

    for (int i = 0; i < data_count; i++) {
        float y = legend_y + i * line_height;

        // Caixinha colorida
        DrawRectangle(
            (int)legend_x,
            (int)y,
            (int)box_size,
            (int)box_size,
            COLOURS[i]
        );

        // Nome da série
        DrawTextEx(
            font,
            data[i].label,
            (Vector2){
                legend_x + box_size + padding,
                y - 2
            },
            font_size,
            spacing,
            BLACK
        );
    }
}

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

void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];

    for (int j = 0; j < data_count; j++) {
        for (int i = 1; i < data[j].size; i++) {
            float point_x1 = plot->left +
                (data[j].x[i-1] - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y1 = plot->bottom -
                (data[j].y[i-1] - plane->y_min_max[0]) /
                y_range * plot->height;

            float point_x2 = plot->left +
                (data[j].x[i] - plane->x_min_max[0]) /
                x_range * plot->width;

            float point_y2 = plot->bottom -
                (data[j].y[i] - plane->y_min_max[0]) /
                y_range * plot->height;

            DrawLineEx(
                (Vector2){point_x1, point_y1},
                (Vector2){point_x2, point_y2},
                3.0f,
                COLOURS[j]
            );

        }
    }
}

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
