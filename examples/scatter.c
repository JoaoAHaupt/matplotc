#include "matplotc.h"
#include <stdbool.h>

int main(void)
{
    Context window = {1000.0, 800.0, "PlotFJMS - Teste 2"};

    Plane plano = {
        {0, 100}, 10,
        {0, 100}, 10,
        true
    };

    int x1[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    int y1[] = {8, 18, 24, 33, 39, 51, 58, 66, 78, 88};

    int size1 = sizeof(x1) / sizeof(x1[0]);

    Data data1 = {
        plano,
        "Linear",
        x1,
        "Tempo",
        y1,
        "Valor",
        size1
    };

    int x2[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    int y2[] = {12, 17, 20, 24, 29, 33, 38, 42, 47, 52};

    int size2 = sizeof(x2) / sizeof(x2[0]);

    Data data2 = {
        plano,
        "Lento",
        x2,
        "Tempo",
        y2,
        "Valor",
        size2
    };

    int x3[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    int y3[] = {50, 75, 90, 70, 45, 20, 10, 30, 60, 85};

    int size3 = sizeof(x3) / sizeof(x3[0]);

    Data data3 = {
        plano,
        "Oscilatorio",
        x3,
        "Tempo",
        y3,
        "Valor",
        size3
    };

    Data dados[] = {data1, data2, data3};

    int data_count = sizeof(dados) / sizeof(dados[0]);
    plot_scatter(&window, &plano, dados, data_count, false);

    return 0;
}
