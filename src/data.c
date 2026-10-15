#include "plane.h"
#include "data.h"
#include "plotarea.h"
#include "stdio.h"

int YDOX = 0; // YDOX: preciso saber como os dados vao estar
// organizados pra saber como acessar o valor de y de um certo x

Structured_Data set_intervals_n(Data *data, int num){
    Structured_Data s_data;
    s_data.num = num;
    s_data.size = data->size / num;

    for (int i = 0; i < num; i++) {
        // s_data.intervals[i]->label = i*s_data.size + "-" + (i+1)*s_data.size-1;
        s_data.intervals[i].first_value[0] = i*s_data.size; 
        s_data.intervals[i].first_value[1] = YDOX; 
        s_data.intervals[i].height = 0;
    }
    for (int i = 0; i < num; i++) {
        int first = s_data.intervals[i].first_value[0];
        for (int d = first; d < first+s_data.size; d++) {
            s_data.intervals[i].height += YDOX;
        }
    }
    return s_data;
}

// pra documentacao: limitado pq todos os intervalos precisam ter o mesmo tamanho
// pressupoe que seja possivel, ou seja, que size seja menor ou igual a data->size
// e que size divida data->size
Structured_Data set_intervals_s(Data *data, int size){
    Structured_Data s_data;
    s_data.size = size;
    s_data.num = data->size / size;

    for (int i = 0; i < s_data.num; i++) {
        // s_data.intervals[i]->label = i*size + "-" + (i+1)*size-1;
        s_data.intervals[i].first_value[0] = i*size; 
        s_data.intervals[i].first_value[1] = YDOX; 
        s_data.intervals[i].height = 0;
    }
    for (int i = 0; i < s_data.num; i++) {
        int first = s_data.intervals[i].first_value[0];
        for (int d = first; d < first+size; d++) {
            s_data.intervals[i].height += YDOX;
        }
    }
    return s_data;
}