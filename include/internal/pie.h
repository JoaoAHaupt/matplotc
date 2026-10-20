#ifndef PIE_H
#define PIE_H

#include "data.h"
#include "plotarea.h"

/* Monta um frame do gráfico de pizza na área indicada. Interno: o usuário
 * chama plot_pie (matplotc.h). */
void create_pie(Data *data, int data_count, PlotArea *plotarea);

#endif
