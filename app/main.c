#include "matplotc.h"
#include <stdio.h>

int main(void) {
  int graph;

  while (1) {
    printf("MatplotC - selecione um tipo de grafico: \n");
    printf("1. Barras\n");
    printf("2. Linha\n");
    printf("3. Dispersao\n");
    printf("4. Pizza\n");
    printf("5. Histograma\n");
    printf("6. Barras com dados de examples/vendas.txt\n");
    printf("7. Barras e exportar para grafico.png (sem janela)\n");
    printf("Opcao: ");

    if (scanf("%d", &graph) != 1 || graph < 1 || graph > 7) {
      printf("Opcao invalida. Escolha um numero entre 1 e 7.\n");
      return 1;
    }

    Context window = create_context(1000.0, 800.0, "MatplotC");
    if (window.width == 0.0f || window.height == 0.0f) {
      return 1;
    }

    if (graph == 1) {
      /* Plano de 0 a 7: deixa meia barra de folga antes do mes 1 e depois do
       * mes 6, para que as barras das pontas nao fiquem cortadas. */
      Plane plane = create_plane(0, 7, 1.0, 0, 100, 10.0, false);
      float x[] = {1, 2, 3, 4, 5, 6};
      float y[] = {45, 52, 48, 65, 72, 80};

      int size = sizeof(x) / sizeof(x[0]);
      Data data = create_data(plane, "Vendas", x, "Mes", y, "Vendas", size);

      if (data.size == 0) {
        return 1;
      }

      plot_bar(&window, &plane, &data, 1);
      show(&window);
    } else if (graph == 2) {
      Plane plane = create_plane(0, 100, 10.0, 0, 100, 10.0, true);
      float x[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
      float y[] = {8, 18, 24, 33, 39, 51, 58, 66, 78, 88};
      Data data =
          create_data(plane, "Serie de exemplo", x, "Tempo", y, "Valor", 10);

      if (data.size == 0) {
        return 1;
      }

      plot_line(&window, &plane, &data, 1);
      show(&window);
    } else if (graph == 3) {
      Plane plane = create_plane(0, 100, 10.0, 0, 100, 10.0, true);
      float x1[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
      float y1[] = {8, 18, 24, 33, 39, 51, 58, 66, 78, 88};
      float x2[] = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
      float y2[] = {90, 80, 78, 65, 60, 52, 45, 33, 25, 12};
      Data data[] = {
          create_data(plane, "Crescente", x1, "Tempo", y1, "Valor", 10),
          create_data(plane, "Decrescente", x2, "Tempo", y2, "Valor", 10)};

      if (data[0].size == 0 || data[1].size == 0) {
        return 1;
      }

      plot_scatter(&window, &plane, data, 2, true);
      show(&window);
    } else if (graph == 4) {
      Plane plane = create_plane(0, 4, 1.0, 0, 100, 10.0, false);
      float x[] = {1, 2, 3, 4};
      float y[] = {40, 30, 20, 10};
      Data data = create_data(plane, "Participacao", x, "Categoria", y,
                              "Percentual", 4);

      if (data.size == 0) {
        return 1;
      }

      plot_pie(&window, &data, 1);
      show(&window);
    } else if (graph == 6) {
      Plane plane = create_plane(0, 7, 1.0f, 0, 100, 10.0f, false);
      Data data =
          load_data("app/vendas.txt", plane, "Vendas", "Mes", "Vendas");

      if (data.size == 0) {
        return 1;
      }

      plot_bar(&window, &plane, &data, 1);
      show(&window);
      free_data(&data);
    } else if (graph == 7) {
      Plane plane = create_plane(0, 7, 1.0f, 0, 100, 10.0f, false);
      Data data =
          load_data("examples/vendas.txt", plane, "Vendas", "Mes", "Vendas");

      if (data.size == 0) {
        return 1;
      }

      plot_bar(&window, &plane, &data, 1);
      if (export_png(&window, "grafico.png")) {
        printf("Imagem salva em grafico.png\n");
      }
      free_data(&data);
    } else {
      Plane plane = create_plane(0, 100, 10.0, 0, 10, 1.0, false);
      float values[] = {12, 18, 22, 27, 31, 34, 38, 42, 45, 47, 51, 53,
                        56, 59, 62, 65, 68, 71, 74, 78, 82, 86, 91, 95};

      float sample_indices[sizeof(values) / sizeof(values[0])];
      int size = (int)(sizeof(values) / sizeof(values[0]));

      for (int i = 0; i < size; i++) {
        sample_indices[i] = i;
      }

      Data data = create_data(plane, "Measurements", values, "Measurement",
                              sample_indices, "Frequency", size);

      if (data.size == 0) {
        return 1;
      }

      plot_histogram(&window, &plane, &data, 1);
      show(&window);
    }
  }

  return 0;
}
