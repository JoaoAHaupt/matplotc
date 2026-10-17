#include "plotfjms.h"

int main(void)
{
    Context window = {800.0, 800.0, "Teste - Grafico de Barras"};

    Plane plano = {
        BAR,
        {0, 10}, 1,
        {0, 100}, 10,
        false
    };

    int x1[] = {1, 2, 3, 4, 5, 10};
    int y1[] = {20, 45, 30, 70, 55, 100};

    Data data1 = {
        plano,
        "Serie A",
        x1,
        "Categorias",
        y1,
        "Valores",
        5
    };

    Data dados[] = {data1};
    int data_count = sizeof(dados) / sizeof(dados[0]);

    create_graph(&window, &plano, dados, data_count);


    return 0;
}
