#ifndef BAR_H
#define BAR_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/* Monta um frame do gráfico de barras na área indicada. Interno: o usuário
 * chama plot_bar (matplotc.h). */
void create_bar(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif
