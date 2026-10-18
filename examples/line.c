#include "matplotc.h"

int main(void)
{
    Context window = {
        1000.0, 800.0,
        "PlotFJMS - Populacao do Brasil"
    };

    Plane plano = {
        {1990, 2025}, 5,
        {0, 220}, 20,
        true
    };

    int x1[] = {1990, 2000, 2010, 2020, 2025};
    int y1[] = {150, 170, 191, 211, 213};
    int size1 = sizeof(x1) / sizeof(x1[0]);

    Data data1 = {
        plano,
        "Populacao",
        x1,
        "Ano",
        y1,
        "Populacao (milhoes)",
        size1
    };

    int x2[] = {1990, 2000, 2010, 2020, 2025};
    int y2[] = {50, 65, 80, 100, 115};
    int size2 = sizeof(x2) / sizeof(x2[0]);

    Data data2 = {
        plano,
        "Serie hipotetica",
        x2,
        "Ano",
        y2,
        "Valor",
        size2
    };

    int x3[] = {1990, 2000, 2010, 2020, 2025};
    int y3[] = {80, 110, 90, 130, 100};
    int size3 = sizeof(x3) / sizeof(x3[0]);

    Data data3 = {
        plano,
        "Serie oscilatoria",
        x3,
        "Ano",
        y3,
        "Valor",
        size3
    };

    Data dados[] = {data1, data2, data3};

    int data_count = sizeof(dados) / sizeof(dados[0]);

    plot_line(&window, &plano, dados, data_count);

    return 0;
}
