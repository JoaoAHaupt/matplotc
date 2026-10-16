
#include "raylib.h"
#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "context.h"
#include "plot.h"

int main(void)
{
    Context window = {800.0, 800.0, "Teste"};

    Plane plano = {
        SCATTER,
        {0, 100}, 10,
        {0, 100}, 10,
        true
    };

    int x[] = {
        5, 12, 18, 25, 31, 38, 44, 51,
        57, 64, 70, 77, 83, 91, 98
    };

    int y[] = {
        12, 18, 20, 29, 31, 35, 43, 45,
        53, 55, 62, 65, 71, 77, 79
    };

    int size = sizeof(x) / sizeof(x[0]);

    Data data = {
        plano,
        "veremlho",
        x,
        "Pontos",
        y,
        "rosas",
        size
    };

    int x2[] = {
        3, 10, 16, 23, 29, 36, 42, 49,
        55, 62, 68, 75, 82, 90, 97
    };

    int y2[] = {
        8, 25, 38, 48, 56, 62, 67, 71,
        74, 76, 78, 79, 80, 80, 81
    };

    int size2 = sizeof(x2) / sizeof(x2[0]);

    Data data2 = {
        plano,
        "azul",
        x2,
        "Pontos",
        y2,
        "rosas",
        size2
    };

    Data dados[] = {data, data2};

    int data_count = sizeof(dados) / sizeof(dados[0]);

    InitWindow(window.width, window.height, window.title);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        create_graph(&window, &plano, dados, data_count);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
