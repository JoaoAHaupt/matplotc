#include "raylib.h"
#include "context.h"
#include "plotarea.h"
#include "data.h"
#include "plane.h"

typedef struct {
    Plane plane;
    char *label;
    int *x;
    int *y;
    int size;
} Data;

typedef struct {
    char *label;
    int first_value[2];
    int final_value[2]; 
    int width;
    int height;
    int densidade_freq;
} Range;

typedef struct {
    Plane plane;
    char *label;
    Range *data;
    int size;
} Structured_Data;

Structured_Data set_intervals(Data *data, int quantity) {
    Structured_Data s_data;
    s_data.size = quantity;
    for (int i = 0; i < data->size; i++) {
        s_data.data[].height +=  

    }
    return s_data;
}
Data densidade_frequencia(Data *data){
    int *valores = data->y;
    int *densidade;
    int total = 0;
    for (int i = 0; valores[i] != NULL; i++) total += valores[i];
    for (int i = 0; valores[i] != NULL; i++) densidade[i] = valores[i] / total / tamanho_intervalo[i];
}
void plot_bar_graph(Data *data, int filled, int numerical, Color color) {
    if (numerical) {
        Structured_Data *struct_data = set_intervals(data);
        if (filled) {
            for (int i = 0; i < struct_data->size; i++) {
                Range intervalo = struct_data->data[i];
                DrawRectangle(intervalo->first_value[0],
                              intervalo->first_value[1],
                              intervalo->width,
                              intervalo->height,
                              color);
                // ADICIONAR RÓTULOS TBM!
            }
        }
        else {
            for (int i = 0; i < struct_data->size; i++) {
                Range intervalo = struct_data->data[i];
                DrawRectangleLines(intervalo->first_value[0],
                                   intervalo->first_value[1],
                                   intervalo->width,
                                   intervalo->height,
                                   color);
            }
        }
    }
    else {
        if (filled) {
            for (int i = 0; i < struct_data->size; i++) {
                Range intervalo = struct_data->data[i];
                DrawRectangle(data->x[i],
                              EIXOX,
                              PLANEWIDTH / size,
                              data->y[i],
                              color);
            }
        }
        else {
            for (int i = 0; i < struct_data->size; i++) {
                Range intervalo = struct_data->data[i];
                DrawRectangleLines(intervalo->first_value[0],
                                   intervalo->first_value[1],
                                   intervalo->width,
                                   intervalo->height,
                                   color);
            }
        }
    }
    return;
}

