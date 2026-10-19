#include "matplotc.h"

int main(void)
{
    Context window = {
        800.0, 800.0,
        "PlotFJMS - Teste Grafico de Pizza"
    };

    Plane plano = {
        {0, 4}, 1,
        {0, 100}, 10,
        false
    };

    float x1[] = {1, 2, 3, 4};
    float y1[] = {40, 30, 20, 10};

    int size1 = sizeof(y1) / sizeof(y1[0]);

    Data data1 = {
        plano,
        "Linguagens",
        x1,
        "Linguagem",
        y1,
        "Participacao (%)",
        size1
    };

    Data dados[] = {data1};
    int data_count = sizeof(dados) / sizeof(dados[0]);

    plot_pie(&window, &plano, dados, data_count);

    return 0;
}
