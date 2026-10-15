#ifndef PLOT_GRAPHS
#define PLOT_GRAPHS

void plot_scatter_graph(Data *data, Plane *plane, PlotArea *plot, Color color);
void plot_bar_graph_num(Structured_Data *struct_data, Plane *plane, PlotArea *plot, int filled, Color color);
void plot_bar_graph(Data *data, Plane *plane, PlotArea *plot, int filled, Color color);
void draw_labels(Data *data, Plane *plane);

#endif