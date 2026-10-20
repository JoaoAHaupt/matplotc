#ifndef HIST_H
#define HIST_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/* Monta um frame do histograma na área indicada. Interno: o usuário chama
 * plot_histogram (matplotc.h). */
void create_histogram(Plane *plane, Data *data, int data_count,
                      PlotArea *plotarea);

#endif
