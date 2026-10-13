#include "plane.h"
#include "plotarea.h"

static const int font_size = 15;
static const int tick_size = 10;

void draw_plane(Context *context, Plane *plane, PlotArea *plot)
{
    (void)context;

    float graph_width = plot->width;
    float graph_height = plot->height;

    float graph_left = plot->left;
    float graph_right = plot->right;
    float graph_top = plot->top;
    float graph_bottom = plot->bottom;

    // Eixo X
    int number_of_scale_x =
        (plane->x_min_max[1] - plane->x_min_max[0]) / plane->scale_x;

    if (number_of_scale_x <= 0) {
        return;
    }

    float scale_pixel_x = graph_width / number_of_scale_x;
    float value_x = plane->x_min_max[0];

    for (int i = 0; i <= number_of_scale_x; i++) {
        float x = graph_left + i * scale_pixel_x;

        // marcadorzin
        DrawRectangle(
            (int)(x - 1),
            (int)(graph_bottom - tick_size / 2),
            2,
            tick_size,
            BLACK
        );

        // linhas verticais da grad, somente se quiser
        if (plane->lines && i > 0 && i < number_of_scale_x) {
            DrawLine(
                (int)x,
                (int)graph_top,
                (int)x,
                (int)graph_bottom,
                LIGHTGRAY
            );
        }

        // numero centralizado no marcador. Talvez seja bom o usuario decidir se quer ou nao casa decimal
        const char *label = TextFormat("%.0f", value_x);
        int text_width = MeasureText(label, font_size);

        DrawText(
            label,
            (int)(x - text_width / 2),
            (int)(graph_bottom + 12),
            font_size,
            BLACK
        );

        value_x += plane->scale_x;
    }

    // Eixo Y
    int number_of_scale_y =
        (plane->y_min_max[1] - plane->y_min_max[0]) / plane->scale_y;

    if (number_of_scale_y <= 0) {
        return;
    }

    float scale_pixel_y = graph_height / number_of_scale_y;
    float value_y = plane->y_min_max[0];

    for (int i = 0; i <= number_of_scale_y; i++) {
        float y = graph_bottom - i * scale_pixel_y;

        // marcaxodrizn
        DrawRectangle(
            (int)(graph_left - tick_size / 2),
            (int)(y - 1),
            tick_size,
            2,
            BLACK
        );

        // linhas horizontais da grad, somente se quiser
        if (plane->lines && i > 0 && i < number_of_scale_y) {
            DrawLine(
                (int)graph_left,
                (int)y,
                (int)graph_right,
                (int)y,
                LIGHTGRAY
            );
        }

        // Numero alinhado a direita
        const char *label = TextFormat("%.0f", value_y);
        int text_width = MeasureText(label, font_size);

        DrawText(
            label,
            (int)(graph_left - tick_size / 2 - 8 - text_width),
            (int)(y - font_size / 2),
            font_size,
            BLACK
        );

        value_y += plane->scale_y;
    }

    // borda do grafico, tem que vir dps so pra nao ser sobrescrita
    DrawRectangleLines(
        (int)graph_left,
        (int)graph_top,
        (int)graph_width,
        (int)graph_height,
        BLACK
    );
}
