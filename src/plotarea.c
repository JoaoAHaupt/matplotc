#include "plotarea.h"

PlotArea create_plotarea(Context *context)
{
    PlotArea area;

    // Numerops altearoiso que eu escolhi, mas depois precisam mudar de acordo com o tamanho das dimensoes
    // do context
    area.padding_left = 80;
    area.padding_right = 40;
    area.padding_top = 40;
    area.padding_bottom = 60;

    area.left = area.padding_left;
    area.top = area.padding_top;

    area.width = context->width
               - area.padding_left
               - area.padding_right;

    area.height = context->height
                - area.padding_top
                - area.padding_bottom;

    area.right = area.left + area.width;
    area.bottom = area.top + area.height;

    return area;
}
