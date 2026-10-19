#ifndef CONTEXT_H
#define CONTEXT_H

typedef struct {
    float width;
    float height;
    const char *title;
} Context;

Context create_context(float width, float height, const char *title);

#endif
