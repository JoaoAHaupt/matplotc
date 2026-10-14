#ifndef CONTEXT_H
#define CONTEXT_H

typedef struct{
    float left_padding_proportion;
    float right_padding_proportion;
    float top_padding_proportion;   
    float bottom_padding_proportion; 
} Proportions;

typedef struct{
    float width;
    float height;
    char *title;
    Proportions proportions;
} Context;

#endif
