#include "context.h"
#include <stdio.h>

Context create_context(float width, float height, const char *title)
{
    if (width <= 0 || height <= 0 || title == NULL || title[0] == '\0') {
        fprintf(stderr, "Error: Invalid parameters when creating Context.\n");

        return (Context){0};
    }

    Context context = {
        .width = width,
        .height = height,
        .title = (char *)title
    };

    return context;
}
