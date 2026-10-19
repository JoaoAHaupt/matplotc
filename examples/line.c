#include "matplotc.h"

int main(void)
{
    Context window = create_context(
        1000.0, 800.0,
        "MatplotC - Populacao do Brasil"
    );

    if (window.width == 0)
        return 1;

    Plane plano = create_plane(
        1990, 2025, 5,
        0, 220, 20,
        true
    );

    if (plano.x_min_max[0] == plano.x_min_max[1])
        return 1;

    int x1[] = {1990, 2000, 2010, 2020, 2025};
    int y1[] = {150, 170, 191, 211, 213};

    int size1 = sizeof(x1) / sizeof(x1[0]);

    Data data1 = create_data(
        plano,
        "Populacao",
        x1, "Ano",
        y1, "Populacao (milhoes)",
        size1
    );

    if (data1.size == 0)
        return 1;

    int x2[] = {1990, 2000, 2010, 2020, 2025};
    int y2[] = {50, 65, 80, 100, 115};

    int size2 = sizeof(x2) / sizeof(x2[0]);

    Data data2 = create_data(
        plano,
        "Serie hipotetica",
        x2, "Ano",
        y2, "Valor",
        size2
    );

    if (data2.size == 0)
        return 1;

    int x3[] = {1990, 2000, 2010, 2020, 2025};
    int y3[] = {80, 110, 90, 130, 100};

    int size3 = sizeof(x3) / sizeof(x3[0]);

    Data data3 = create_data(
        plano,
        "Serie oscilatoria",
        x3, "Ano",
        y3, "Valor",
        size3
    );

    if (data3.size == 0)
        return 1;

    Data dados[] = {data1, data2, data3};

    int data_count = sizeof(dados) / sizeof(dados[0]);

    plot_line(&window, &plano, dados, data_count);

    return 0;
}
