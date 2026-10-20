#ifndef DATA_DRAW_H
#define DATA_DRAW_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/* Desenho dos dados e rótulos de um gráfico. Interno: cada gráfico monta o
 * seu frame usando estas funções; o usuário da biblioteca não as chama. */
void draw_line_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot);
void draw_label(Data *data, Plane *plane, PlotArea *plot);
void draw_legend(Data *data, int data_count, PlotArea *plot);
void draw_linear_correlation(Data *data, int data_count, Plane *plane,
                             PlotArea *plot);

#endif
