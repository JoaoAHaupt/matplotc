/**
 * @file pie.h
 * @brief Interface do gráfico de pizza.
 */

#ifndef PIE_H
#define PIE_H

#include "data.h"
#include "plotarea.h"

/**
 * @brief Desenha as fatias do gráfico de pizza.
 *
 * Soma todos os valores de y de todas as séries e desenha uma fatia
 * proporcional para cada valor, começando em 0°, centrada em (400, 400)
 * com raio 150.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 *
 * @note Não desenha nada se a soma dos valores for menor ou igual a zero.
 */
void draw_pie_data(Data *data, int data_count);

/**
 * @brief Cria o gráfico de pizza completo (fatias e legenda).
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plotarea   Área de plotagem em pixels (usada para posicionar a
 *                   legenda).
 */
void create_pie(Data *data, int data_count, PlotArea *plotarea);

#endif