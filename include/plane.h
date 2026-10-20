/**
 * @file plane.h
 * @brief Plano cartesiano: limites dos eixos, escalas e desenho dos eixos.
 */

#ifndef PLANE_H
#define PLANE_H

#include "plotarea.h"
#include <stdbool.h>

/**
 * @brief Plano cartesiano que define o intervalo visível dos dados.
 */
typedef struct {
  float x_min_max[2];  ///< Limites do eixo x: [0] = mínimo, [1] = máximo.
  float scale_x;       ///< Espaçamento entre marcações do eixo x (também a largura da classe no histograma).
  float y_min_max[2];  ///< Limites do eixo y: [0] = mínimo, [1] = máximo.
  float scale_y;       ///< Espaçamento entre marcações do eixo y.
  bool lines;          ///< Se verdadeiro, desenha linhas de grade.
} Plane;

/**
 * @brief Desenha o plano: eixos x e y, marcações, grade opcional e borda.
 *
 * @param plane     Plano cartesiano a desenhar.
 * @param plot_area Área de plotagem em pixels.
 */
void draw_plane(Plane *plane, PlotArea *plot_area);

/**
 * @brief Desenha o eixo x (marcações e valores abaixo da área do gráfico).
 *
 * Os valores crescem da esquerda para a direita. Se @p lines for verdadeiro,
 * desenha também linhas verticais de grade nas marcações internas.
 *
 * @param scale     Espaçamento entre marcações (deve ser maior que 0).
 * @param min_max   Limites do eixo: [0] = mínimo, [1] = máximo.
 * @param lines     Se verdadeiro, desenha a grade.
 * @param plot_area Área de plotagem em pixels.
 *
 * @note Não desenha nada se @p scale for inválido ou se não couber ao menos
 *       uma divisão no intervalo.
 */
void draw_axis_x(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

/**
 * @brief Desenha o eixo y (marcações e valores à esquerda da área do gráfico).
 *
 * Os valores crescem de baixo para cima. Se @p lines for verdadeiro,
 * desenha também linhas horizontais de grade nas marcações internas.
 *
 * @param scale     Espaçamento entre marcações (deve ser maior que 0).
 * @param min_max   Limites do eixo: [0] = mínimo, [1] = máximo.
 * @param lines     Se verdadeiro, desenha a grade.
 * @param plot_area Área de plotagem em pixels.
 *
 * @note Não desenha nada se @p scale for inválido ou se não couber ao menos
 *       uma divisão no intervalo.
 */
void draw_axis_y(float scale, float min_max[2], bool lines,
                 PlotArea *plot_area);

/**
 * @brief Cria um plano cartesiano validando os parâmetros.
 *
 * @param x_min   Limite inferior de x.
 * @param x_max   Limite superior de x (deve ser maior que @p x_min).
 * @param scale_x Espaçamento das marcações de x (deve ser maior que 0).
 * @param y_min   Limite inferior de y.
 * @param y_max   Limite superior de y (deve ser maior que @p y_min).
 * @param scale_y Espaçamento das marcações de y (deve ser maior que 0).
 * @param lines   Se verdadeiro, desenha linhas de grade.
 *
 * @return Plano preenchido; ou um Plane zerado se algum parâmetro for
 *         inválido (mensagem de erro em stderr).
 */
Plane create_plane(float x_min, float x_max, float scale_x, float y_min,
                   float y_max, float scale_y, bool lines);

#endif