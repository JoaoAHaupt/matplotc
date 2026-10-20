/**
 * @file bar.h
 * @brief Interface do gráfico de barras.
 *
 * Declara as funções responsáveis por desenhar um gráfico de barras
 * agrupadas (uma barra por série em cada posição x).
 */

#ifndef BAR_H
#define BAR_H

#include "data.h"
#include "plane.h"
#include "plotarea.h"

/**
 * @brief Desenha as barras de todas as séries dentro da área do gráfico.
 *
 * A largura de cada grupo de barras é calculada a partir da menor distância
 * entre dois valores consecutivos de x em qualquer série (ocupando 80% desse
 * espaço). Dentro do grupo, cada série recebe uma barra de largura igual.
 * As barras partem da linha de base y = 0 (limitada ao intervalo visível de y)
 * e o desenho é recortado na área do gráfico.
 *
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plane      Plano cartesiano com os limites de x e y.
 * @param plot       Área de plotagem em pixels.
 *
 * @note Não faz nada se algum ponteiro for NULL, se @p data_count for
 *       menor ou igual a zero ou se os limites do plano/área forem inválidos.
 */
void draw_bar_data(Data *data, int data_count, Plane *plane, PlotArea *plot);

/**
 * @brief Cria o gráfico de barras completo.
 *
 * Desenha o plano, as barras, os rótulos dos eixos e a legenda.
 *
 * @param plane    Plano cartesiano com os limites de x e y.
 * @param data     Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param plotarea Área de plotagem em pixels.
 *
 * @note Deve ser chamada dentro do laço de desenho (entre BeginDrawing e
 *       EndDrawing do raylib).
 */
void create_bar(Plane *plane, Data *data, int data_count, PlotArea *plotarea);

#endif