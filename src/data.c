#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "raylib.h"
#include <stdio.h>

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

void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{

}
