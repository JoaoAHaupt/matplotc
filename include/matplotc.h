#ifndef MATPLOTC_H
#define MATPLOTC_H

/* Interface pública do matplotc, organizada em 4 módulos:
 *
 *   Contexto    - criação da janela e exibição do gráfico
 *   Dados       - criação/carregamento e liberação dos dados
 *   Gráficos    - registro do gráfico a ser desenhado (um por tipo)
 *   Exportação  - gravação do gráfico em arquivo PNG
 *
 * Fluxo típico:
 *
 *   Context ctx = create_context(1000, 800, "Meu grafico");
 *   Data d = create_data(plane, "Serie", x, "X", y, "Y", n);
 *   plot_line(&ctx, &plane, &d, 1);
 *   show(&ctx);                       // ou: export_png(&ctx, "grafico.png");
 */

#include <stdbool.h>

#include "context.h"
#include "data.h"
#include "plane.h"

/* Contexto */
void show(Context *context);

/* Dados */
/* create_data, load_data e free_data estão em data.h. */

/* Gráficos */
void plot_line(Context *context, Plane *plane, Data *data, int data_count);
void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr);
void plot_pie(Context *context, Data *data, int data_count);
void plot_bar(Context *context, Plane *plane, Data *data, int data_count);
void plot_histogram(Context *context, Plane *plane, Data *data, int data_count);

/* Exportação */
bool export_png(Context *context, const char *filename);

#endif
