#ifndef SCATTER_H
#define SCATTER_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/* Monta um frame do gráfico de dispersão na área indicada. Interno: o
 * usuário chama plot_scatter (matplotc.h). */
void create_scatter(Plane *plane, Data *data, int data_count,
                    PlotArea *plotarea, bool show_regression);

#endif
