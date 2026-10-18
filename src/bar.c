#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"
#include "raylib.h"
#include "colours.h"
#include <stddef.h>
#include <math.h>

#define BAR_COLOUR_COUNT 8
#define BAR_GROUP_GAP 0.20f
#define BAR_WIDTH_RATIO 0.80f

void draw_bar_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
)
{
    if (data == NULL || plane == NULL || plot == NULL ||
        data_count <= 0 ||
        plane->x_min_max[1] <= plane->x_min_max[0] ||
        plane->y_min_max[1] <= plane->y_min_max[0] ||
        plot->width <= 0 || plot->height <= 0) {
        return;
    }

    float x_min = plane->x_min_max[0];
    float x_max = plane->x_min_max[1];
    float y_min = plane->y_min_max[0];
    float y_max = plane->y_min_max[1];

    float x_range = x_max - x_min;
    float y_range = y_max - y_min;

    /*
     * Find the minimum positive distance between distinct x values.
     * This works even when the data is not sorted.
     */
    float min_step = x_range;

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL ||
            data[j].size <= 0) {
            continue;
        }

        for (int i = 0; i < data[j].size; i++) {
            float current_x = (float)data[j].x[i];

            for (int k = 0; k < data_count; k++) {
                if (data[k].x == NULL || data[k].size <= 0) {
                    continue;
                }

                for (int l = 0; l < data[k].size; l++) {
                    float distance =
                        fabsf(current_x - (float)data[k].x[l]);

                    if (distance > 0.0f && distance < min_step) {
                        min_step = distance;
                    }
                }
            }
        }
    }

    /*
     * If every point has the same x value, use a fallback width.
     */
    if (min_step <= 0.0f || min_step > x_range) {
        min_step = x_range / 10.0f;
    }

    float slot_width = (min_step / x_range) * plot->width;
    float group_width = slot_width * BAR_WIDTH_RATIO;
    float bar_width = group_width / data_count;

    /*
     * The baseline is zero whenever zero is visible.
     * Otherwise, it is placed at the nearest visible boundary.
     */
    float base_value = 0.0f;

    if (base_value < y_min) {
        base_value = y_min;
    } else if (base_value > y_max) {
        base_value = y_max;
    }

    float base_y = plot->bottom -
        ((base_value - y_min) / y_range) * plot->height;

    for (int j = 0; j < data_count; j++) {
        if (data[j].x == NULL || data[j].y == NULL ||
            data[j].size <= 0) {
            continue;
        }

        Color bar_color = COLOURS[j % BAR_COLOUR_COUNT];

        for (int i = 0; i < data[j].size; i++) {
            float x = (float)data[j].x[i];
            float y = (float)data[j].y[i];

            /*
             * Ignore values outside the horizontal plot range.
             */
            if (x < x_min || x > x_max) {
                continue;
            }

            float center_x = plot->left +
                ((x - x_min) / x_range) * plot->width;

            /*
             * Center the entire group around its x coordinate.
             */
            float bar_x = center_x - group_width / 2.0f
                        + j * bar_width;

            /*
             * Convert the value to screen coordinates.
             */
            float value_y = plot->bottom -
                ((y - y_min) / y_range) * plot->height;

            /*
             * Construct the rectangle between the value and baseline.
             */
            float top = fminf(value_y, base_y);
            float bottom = fmaxf(value_y, base_y);

            /*
             * Clip the rectangle to the plot area.
             */
            float left = fmaxf(bar_x, plot->left);
            float right = fminf(bar_x + bar_width, plot->right);

            top = fmaxf(top, plot->top);
            bottom = fminf(bottom, plot->bottom);

            if (right <= left || bottom <= top) {
                continue;
            }

            Rectangle bar = {
                .x = left,
                .y = top,
                .width = right - left,
                .height = bottom - top
            };

            DrawRectangleRec(bar, bar_color);
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
    if (context == NULL || plane == NULL ||
        data == NULL || plotarea == NULL || data_count <= 0) {
        return;
    }

    draw_plane(context, plane, plotarea);
    draw_bar_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}
