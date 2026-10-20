/**
 * @file scatter.h
 * @brief Interface do gráfico de dispersão.
 */

#ifndef SCATTER_H
#define SCATTER_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/**
 * @brief Desenha os pontos de todas as séries como círculos de raio 5 px.
 *
 * Cada série usa a cor correspondente da paleta ::COLOURS.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plane      Plano cartesiano com os limites de x e y.
 * @param plot       Área de plotagem em pixels.
 */
void draw_scatter_data(Data *data, int data_count, Plane *plane,
                       PlotArea *plot);

/**
 * @brief Cria o gráfico de dispersão completo.
 *
 * Desenha, em ordem: o plano (eixos e grade), os pontos, a reta de regressão
 * (opcional), os rótulos dos eixos e a legenda.
 *
 * @param plane           Plano cartesiano.
 * @param data            Vetor de séries de dados.
 * @param data_count      Quantidade de séries em @p data.
 * @param plotarea        Área de plotagem em pixels.
 * @param show_regression Se verdadeiro, desenha a reta de regressão linear
 *                        de cada série.
 */
void create_scatter(Plane *plane, Data *data, int data_count,
                    PlotArea *plotarea, bool show_regression);

/**
 * @brief Desenha a reta de regressão linear (mínimos quadrados) de cada série.
 *
 * Para cada série calcula y = a·x + b e traça a reta de x mínimo a x máximo
 * do plano, na cor da série, com 1 px de espessura.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plane      Plano cartesiano com os limites de x e y.
 * @param plot       Área de plotagem em pixels.
 *
 * @note Séries com menos de 2 pontos, ou com todos os x iguais (regressão
 *       indefinida), são ignoradas.
 */
void draw_linear_correlation(Data *data, int data_count, Plane *plane,
                             PlotArea *plot);

#endif