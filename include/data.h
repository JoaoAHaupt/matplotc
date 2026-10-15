#ifndef DATA_H
#define DATA_H

typedef struct {
    char *label;
    int *x;
    int *y;
    int size;
} Data;

typedef struct {
    char *label;
    int first_value[2];
    int height;
} Range;

typedef struct {
    char *label;
    Range *intervals;
    int size; // tamanho de cada intervalo
    int num; // quantidade de intervalos
} Structured_Data;

Structured_Data create_num_intervals(Data *data, int num);
Structured_Data create_intervals_of_size(Data *data, int size);

#endif