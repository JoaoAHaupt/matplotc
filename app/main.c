#include "matplotc.h"

int main(void) {
  Context window = {1200, 800, "Vendas Mensais - Comparacao entre Lojas"};

  Plane plano = {{0, 7}, 1, {0, 200}, 200, false};

  float x1[] = {1, 2, 3, 4, 5, 6};
  float y1[] = {45, 52, 48, 65, 72, 80};
  int n1 = sizeof(x1) / sizeof(x1[0]);

  Data data1 = {plano, "Loja Centro", x1, "Meses", y1, "Vendas (R$ mil)", n1};

  float x2[] = {1, 2, 3, 4, 5, 6};
  float y2[] = {60, 55, 70, 68, 85, 95};
  int n2 = sizeof(x2) / sizeof(x2[0]);

  Data data2 = {plano, "Loja Shopping", x2, "Meses", y2, "Vendas (R$ mil)", n2};

  Data dados[] = {data1, data2};
  int data_count = sizeof(dados) / sizeof(dados[0]);

  plot_bar(&window, &plano, dados, data_count);

  return 0;
}
