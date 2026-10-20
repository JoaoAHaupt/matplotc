#ifndef PLANE_DRAW_H
#define PLANE_DRAW_H

#include "plane.h"
#include "plotarea.h"
#include <stdbool.h>

/* Desenho do plano cartesiano. Interno: o usuário da biblioteca só precisa
 * criar o Plane (create_plane); quem desenha é o plot_* escolhido. */
void draw_plane(Plane *plane, PlotArea *plot_area);

void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

#endif
