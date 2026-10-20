#include "data.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN 256

/* Anexa um ponto às arrays dinâmicas, dobrando a capacidade quando cheia.
 * Em caso de falha de alocação, devolve false preservando o que já foi
 * alocado (a limpeza é responsabilidade do chamador). */
static bool append_point(float **x, float **y, int *count, int *capacity,
                         float px, float py) {
  if (*count == *capacity) {
    int new_capacity = *capacity == 0 ? 16 : *capacity * 2;

    float *new_x = realloc(*x, (size_t)new_capacity * sizeof(float));
    if (new_x == NULL) {
      return false;
    }
    *x = new_x;

    float *new_y = realloc(*y, (size_t)new_capacity * sizeof(float));
    if (new_y == NULL) {
      return false;
    }
    *y = new_y;

    *capacity = new_capacity;
  }

  (*x)[*count] = px;
  (*y)[*count] = py;
  (*count)++;
  return true;
}

Data load_data(const char *path, Plane plane, const char *label,
               const char *x_axis_label, const char *y_axis_label) {
  if (path == NULL || label == NULL || x_axis_label == NULL ||
      y_axis_label == NULL) {
    fprintf(stderr, "Error: Invalid parameters when loading Data.\n");
    return (Data){0};
  }

  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error: Could not open data file '%s'.\n", path);
    return (Data){0};
  }

  float *x = NULL;
  float *y = NULL;
  int count = 0;
  int capacity = 0;
  char line[LINE_MAX_LEN];

  while (fgets(line, sizeof(line), file) != NULL) {
    /* Comentários começam com '#' e estendem até o fim da linha. */
    char *comment = strchr(line, '#');
    if (comment != NULL) {
      *comment = '\0';
    }

    /* Aceita tanto separador por vírgula quanto por espaço. */
    for (char *p = line; *p != '\0'; p++) {
      if (*p == ',') {
        *p = ' ';
      }
    }

    float px, py;
    if (sscanf(line, " %f %f", &px, &py) != 2) {
      /* Linha vazia ou malformada: ignora. */
      continue;
    }

    if (!isfinite(px) || !isfinite(py)) {
      continue;
    }

    if (!append_point(&x, &y, &count, &capacity, px, py)) {
      fprintf(stderr, "Error: Out of memory while loading '%s'.\n", path);
      free(x);
      free(y);
      fclose(file);
      return (Data){0};
    }
  }

  fclose(file);

  if (count == 0) {
    fprintf(stderr, "Error: No valid points in data file '%s'.\n", path);
    free(x);
    free(y);
    return (Data){0};
  }

  Data data = create_data(plane, label, x, x_axis_label, y, y_axis_label,
                          count);
  if (data.size == 0) {
    /* create_data rejeitou os parâmetros: não fica com as arrays alocadas. */
    free(x);
    free(y);
    return (Data){0};
  }

  data.owns_memory = true;
  return data;
}
