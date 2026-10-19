#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"
#include <math.h>
#include <stddef.h>

void draw_scatter_data(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        plot->width <= 0.0f || plot->height <= 0.0f) {
        return;
    }

    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            if (data[j].x[i] < plane->x_min_max[0] ||
                data[j].x[i] > plane->x_min_max[1] ||
                data[j].y[i] < plane->y_min_max[0] ||
                data[j].y[i] > plane->y_min_max[1]) {
                continue;
            }

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

void draw_linear_correlation(Data *data, int data_count, Plane *plane, PlotArea *plot)
{
    if (data == NULL || plane == NULL || plot == NULL || data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        plot->width <= 0.0f || plot->height <= 0.0f) {
        return;
    }

    float x_range = plane->x_min_max[1] - plane->x_min_max[0];
    float y_range = plane->y_min_max[1] - plane->y_min_max[0];

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL || data[j].size < 2) {
            continue;
        }

        int n = 0;
        double sum_x = 0;
        double sum_y = 0;
        double sum_xy = 0;
        double sum_x2 = 0;

        for (int i = 0; i < data[j].size; i++) {
            double x = data[j].x[i];
            double y = data[j].y[i];

            if (x < plane->x_min_max[0] || x > plane->x_min_max[1] ||
                y < plane->y_min_max[0] || y > plane->y_min_max[1]) {
                continue;
            }

            n++;
            sum_x += x;
            sum_y += y;
            sum_xy += x * y;
            sum_x2 += x * x;
        }

        if (n < 2) {
            continue;
        }

        double denominator = n * sum_x2 - sum_x * sum_x;

        if (fabs(denominator) < 1e-9)
            continue;

        double a = (n * sum_xy - sum_x * sum_y) / denominator;
        double b = (sum_y - a * sum_x) / n;

        double x1 = plane->x_min_max[0];
        double x2 = plane->x_min_max[1];

        double y1 = a * x1 + b;
        double y2 = a * x2 + b;

        double delta_y = y2 - y1;
        double t_min = 0.0;
        double t_max = 1.0;

        if (fabs(delta_y) < 1e-12) {
            if (y1 < plane->y_min_max[0] || y1 > plane->y_min_max[1]) {
                continue;
            }
        } else {
            double t1 = (plane->y_min_max[0] - y1) / delta_y;
            double t2 = (plane->y_min_max[1] - y1) / delta_y;

            t_min = fmax(0.0, fmin(t1, t2));
            t_max = fmin(1.0, fmax(t1, t2));

            if (t_min > t_max) {
                continue;
            }
        }

        double clipped_x1 = x1 + t_min * (x2 - x1);
        double clipped_y1 = y1 + t_min * delta_y;
        double clipped_x2 = x1 + t_max * (x2 - x1);
        double clipped_y2 = y1 + t_max * delta_y;

        float screen_x1 = plot->left +
            (clipped_x1 - plane->x_min_max[0]) / x_range * plot->width;
        float screen_y1 = plot->bottom -
            (clipped_y1 - plane->y_min_max[0]) / y_range * plot->height;
        float screen_x2 = plot->left +
            (clipped_x2 - plane->x_min_max[0]) / x_range * plot->width;
        float screen_y2 = plot->bottom -
            (clipped_y2 - plane->y_min_max[0]) / y_range * plot->height;

        DrawLineEx(
            (Vector2){screen_x1, screen_y1},
            (Vector2){screen_x2, screen_y2},
            1.0f,
            COLOURS[j]
        );
    }
}

void create_scatter(
    Context *context,
    Plane *plane,
    Data *data,
    int data_count,
    PlotArea *plotarea,
    bool show_regression
)
{
    draw_plane(context, plane, plotarea);

    draw_scatter_data(data, data_count, plane, plotarea);

    if (show_regression) {
        draw_linear_correlation(data, data_count, plane, plotarea);
    }

    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}
