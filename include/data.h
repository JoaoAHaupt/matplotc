#ifndef DATA_H
#define DATA_H

#include "plane.h"

typedef struct {
  Plane plane;
  char *label;

  float *x;
  char *x_axis_label;

  float *y;
  char *y_axis_label;

  int size;

  /* true quando x/y foram alocados por load_data; nesse caso, libere os
   * arrays com free_data. Em create_data, os arrays pertencem ao chamador. */
  bool owns_memory;
} Data;

Data create_data(Plane plane, const char *label, float *x,
                 const char *x_axis_label, float *y, const char *y_axis_label,
                 int size);

/* Carrega duas colunas (x e y) de um arquivo .txt/.csv. Espaços e vírgulas
 * separam as colunas; linhas vazias e linhas iniciadas com '#' são
 * ignoradas, assim como linhas malformadas. Os arrays x/y são alocados por
 * esta função (owns_memory = true): libere com free_data. Retorna
 * (Data){0} em caso de erro (arquivo inexistente ou sem pontos válidos). */
Data load_data(const char *path, Plane plane, const char *label,
               const char *x_axis_label, const char *y_axis_label);

/* Libera os arrays alocados por load_data e zera a struct. Inofensiva para
 * Data vinda de create_data (arrays do chamador) e para NULL. */
void free_data(Data *data);

#endif
