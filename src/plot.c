#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

void create_scatter(Context *context, Plane *plane, Data *data, int data_count, PlotArea *plotarea)
{
    draw_plane(context, plane, plotarea);
    draw_data(data, data_count, plane, plotarea);
    draw_label(data, plane, plotarea);
    draw_legend(data, data_count, plotarea);
}

void create_graph(Context *context, Plane *plane, Data *data, int data_count)
{
    PlotArea plot_area = create_plotarea(context);

    create_scatter(context, plane, data, data_count, &plot_area);
}
