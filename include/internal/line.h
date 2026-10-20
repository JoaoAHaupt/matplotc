#ifndef LINE_H
#define LINE_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/* Monta um frame do gráfico de linhas na área indicada. Interno: o usuário
 * chama plot_line (matplotc.h). */
void create_line(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif
