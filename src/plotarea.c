#include "plotarea.h"

PlotArea create_plotarea(Context *context)
{
    PlotArea area;

    area.padding_left = context->width * context->proportions.left_padding_proportion;
    area.padding_right = context->width * context->proportions.right_padding_proportion;
    area.padding_top = context->height * context->proportions.top_padding_proportion;
    area.padding_bottom = context->height * context->proportions.bottom_padding_proportion;

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