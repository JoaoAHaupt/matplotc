/**
 * @file hist.h
 * @brief Interface do histograma.
 */

#ifndef HIST_H
#define HIST_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/**
 * @brief Desenha as barras do histograma de cada série.
 *
 * Os valores de @c x de cada série são distribuídos em classes (bins) de
 * largura @c plane->scale_x entre os limites de x do plano. A altura de cada
 * barra é a frequência (contagem) de valores na classe. Se o número de
 * classes exceder a largura da área em pixels, ele é reduzido e a largura da
 * classe é recalculada. A última classe inclui o limite superior de x.
 * Com várias séries, as barras de cada classe são colocadas lado a lado.
 *
 * @param data       Vetor de séries (apenas @c x é usado).
 * @param data_count Quantidade de séries em @p data.
 * @param plane      Plano cartesiano (limites de x/y e @c scale_x).
 * @param plot       Área de plotagem em pixels.
 *
 * @note Não faz nada se os parâmetros forem inválidos (ponteiros NULL,
 *       limites invertidos, @c scale_x não positivo ou não finito, etc.).
 */
void draw_hist_data(Data *data, int data_count, Plane *plane, PlotArea *plot);

/**
 * @brief Cria o histograma completo.
 *
 * Desenha, em ordem: o plano (eixos e grade), as barras, os rótulos dos
 * eixos e a legenda.
 *
 * @param plane      Plano cartesiano.
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plotarea   Área de plotagem em pixels.
 */
void create_histogram(Plane *plane, Data *data, int data_count,
                      PlotArea *plotarea);

#endif