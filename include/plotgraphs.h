#ifndef PLOT_GRAPHS
#define PLOT_GRAPHS

void plot_scatter_graph(Data *data, Plane *plane, PlotArea *plot);
void plot_bar_graph(Data *data, Plane *plane, int filled, int numerical, Color color);
void draw_labels(Data *data, Plane *plane);

#endif