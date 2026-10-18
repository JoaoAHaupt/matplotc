#include "matplotc.h"

int main(void)
{
    Context window = {
        1200.0, 800.0,
        "Vendas Mensais - Comparacao entre Lojas"
    };

    Plane plano = {
        {1, 6}, 1,
        {0, 100}, 10,
        false
    };

    // Vendas da Loja Centro (em milhares de reais)
    int x1[] = {1, 2, 3, 4, 5, 6};   // era {1990..1995}
    int y1[] = {45, 52, 48, 65, 72, 80};
    int n1 = sizeof(x1) / sizeof(x1[0]);

    Data data1 = {
        plano,
        "Loja Centro",
        x1,
        "Meses",
        y1,
        "Vendas (R$ mil)",
        n1
    };



    Data dados[] = {data1};
    int data_count = sizeof(dados) / sizeof(dados[0]);

    plot_bar(&window, &plano, dados, data_count);

    return 0;
}
