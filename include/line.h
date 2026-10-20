/**
 * @file line.h
 * @brief Interface do gráfico de linhas.
 */

#ifndef LINE_H
#define LINE_H

#include "plane.h"
#include "data.h"
#include "context.h"
#include "plotarea.h"

/**
 * @brief Desenha as linhas de todas as séries.
 *
 * Cada par de pontos consecutivos de uma série é ligado por um segmento de
 * 3 pixels de espessura, na cor da série.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plane      Plano cartesiano com os limites de x e y.
 * @param plot       Área de plotagem em pixels.
 */
void draw_line_data(
    Data *data,
    int data_count,
    Plane *plane,
    PlotArea *plot
);

/**
 * @brief Cria o gráfico de linhas completo.
 *
 * Desenha, em ordem: o plano (eixos e grade), as linhas, os rótulos dos
 * eixos e a legenda.
 *
 * @param plane      Plano cartesiano.
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plotarea   Área de plotagem em pixels.
 */
void create_line(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif