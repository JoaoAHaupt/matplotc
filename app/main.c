#include "raylib.h"
#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "stdio.h"

int main(void)
{
    Canvas default_proportions = {0.10f, 0.05f, 0.05f, 0.10f};
    Context window = {800.0, 800.0, "Teste", default_proportions};

    Plane plano = {
        SCATTER,
        {0, 100}, 10,
        {0, 100}, 10,
        true
    };

    // Acho que nao eh uma boa
    int x[] = {5, 12, 18, 25, 31, 38, 44, 51, 57, 64, 70, 77, 83, 91, 98};
    int y[] = {12, 18, 20, 29, 31, 35, 43, 45, 53, 55, 62, 65, 71, 77, 79};

    int size = sizeof(x) / sizeof(x[0]);

    Data data = {plano, "pontos", x, y, size};
    PlotArea plot = create_plotarea(&window);
    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_plane(&window, &plano, &plot);
        draw_data(&data, &plano, &plot);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
