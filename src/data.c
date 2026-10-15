#include "data.h"
#include "plane.h"
#include "plotarea.h"
#include "stdio.h"

// pra documentacao: limitado pq todos os intervalos precisam ter o mesmo tamanho
// pressupoe que num seja maior que 0 e que num divida o tamanho data-> size
Structured_Data create_num_intervals(Data *data, int num){
    Structured_Data s_data = {0};
    // s_data.label = data->label;
    s_data.num = num;
    s_data.size = data->size / num;

    for (int i = 0; i < num; i++) {
        int first = i*s_data.size;
        int last = (i+1)*s_data.size - 1;

        snprintf(s_data.intervals[i].label, sizeof(s_data.intervals[i].label),"%d-%d", data->x[first], data->x[last]);
        s_data.intervals[i].first_value[0] = data->x[first]; 
        s_data.intervals[i].first_value[1] = data->y[first]; 
        s_data.intervals[i].height = 0;

        for (int d = first; d < last+1; d++) {
            s_data.intervals[i].height += data->y[d];
        }
    }
    return s_data;
}

// pra documentacao: limitado pq todos os intervalos precisam ter o mesmo tamanho
// pressupoe que size seja menor ou igual a data->size e que size divida data->size
Structured_Data create_intervals_of_size(Data *data, int size){
    Structured_Data s_data = {0};
    s_data.size = size;
    s_data.num = data->size / size;

    for (int i = 0; i < s_data.num; i++) {
        int first = i*size;
        int last = (i+1)*size - 1;

        snprintf(s_data.intervals[i].label, sizeof(s_data.intervals[i].label),"%d-%d", data->x[first], data->x[last]);
        s_data.intervals[i].first_value[0] = data->x[first]; 
        s_data.intervals[i].first_value[1] = data->y[first]; 
        s_data.intervals[i].height = 0;

        for (int d = first; d < last+1; d++) {
            s_data.intervals[i].height += data->y[d];
        }
    }
    return s_data;
}