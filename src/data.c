#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "stdio.h"

int YDOX = 0; // YDOX: preciso saber como os dados vao estar
// organizados pra saber como acessar o valor de y de um certo x

Structured_Data set_intervals_q(Data *data, int quantity){
    Structured_Data s_data;
    s_data.size = quantity;
    s_data.width = data->size / quantity;

    for (int i = 0; i < s_data.size; i++) {
        // s_data.intervals[i]->label = i*tamanho + "-" + (i+1)*tamanho-1;
        s_data.intervals[i].first_value = {i*tamanho, YDOX}; 
        s_data.intervals[i].height = 0;
    }
    for (int i = 0; i < s_data.size; i++) {
        first = s_data.intervals[i].first_value[0];
        for (int d = first; d < first+tamanho; d++) {
            s_data.intervals[i].height += YDOX;
        }
    }
    return s_data;
}

// pra documentacao: limitado pq todos os intervalos precisam ter o mesmo tamanho
// pressupoe que seja possivel, ou seja, que int_size seja menor ou igual a data->size
// e que int_size divida data->size
Structured_Data set_intervals_s(Data *data, int int_size){
    Structured_Data s_data;
    s_data.width = int_size;
    s_data.size = data->size / int_size;

    for (int i = 0; i < s_data.size; i++) {
        // s_data.intervals[i]->label = i*tamanho + "-" + (i+1)*tamanho-1;
        s_data.intervals[i].first_value = {i*tamanho, YDOX};
        s_data.intervals[i].height = 0;
    }
    for (int i = 0; i < s_data.size; i++) {
        first = s_data.intervals[i].first_value[0];
        for (int d = first; d < first+tamanho; d++) {
            s_data.intervals[i].height += YDOX;
        }
    }
    return s_data;
}