/**
 * @file data.h
 * @brief Estrutura de dados das séries e funções comuns de desenho
 *        (rótulos dos eixos e legenda).
 */

#ifndef DATA_H
#define DATA_H

#include "plane.h"

/**
 * @brief Uma série de dados a ser plotada.
 *
 * Os vetores @c x e @c y e as strings de rótulo não são copiados; devem
 * continuar válidos enquanto a série for usada.
 */
typedef struct {
  Plane plane;          ///< Plano cartesiano associado à série.
  char *label;          ///< Nome da série (mostrado na legenda).

  float *x;             ///< Valores do eixo x (@c size elementos).
  char *x_axis_label;   ///< Rótulo do eixo x.

  float *y;             ///< Valores do eixo y (@c size elementos).
  char *y_axis_label;   ///< Rótulo do eixo y.

  int size;             ///< Quantidade de pontos em @c x e @c y.
} Data;

/**
 * @brief Cria uma série de dados validando os parâmetros.
 *
 * @param plane        Plano cartesiano da série.
 * @param label        Nome da série (legenda).
 * @param x            Vetor com os valores de x.
 * @param x_axis_label Rótulo do eixo x.
 * @param y            Vetor com os valores de y.
 * @param y_axis_label Rótulo do eixo y.
 * @param size         Número de pontos (deve ser maior que 0).
 *
 * @return Série preenchida; ou um Data zerado se @p size for inválido, se
 *         @p x ou @p y forem NULL ou se algum rótulo for NULL
 *         (mensagem de erro em stderr).
 */
Data create_data(Plane plane, const char *label, float *x,
                 const char *x_axis_label, float *y, const char *y_axis_label,
                 int size);

/**
 * @brief Desenha os rótulos dos eixos x e y.
 *
 * O rótulo de x é centralizado abaixo da área do gráfico e o de y é
 * desenhado girado em -90° à esquerda dela. Os textos vêm da primeira série
 * (@p data[0]).
 *
 * @param data  Vetor de séries (usa a primeira).
 * @param plane Plano cartesiano (não utilizado atualmente).
 * @param plot  Área de plotagem em pixels.
 */
void draw_label(Data *data, Plane *plane, PlotArea *plot);

/**
 * @brief Desenha a legenda com uma entrada (cor + nome) por série.
 *
 * A legenda fica no canto superior direito da área do gráfico.
 *
 * @param data       Vetor de séries.
 * @param data_count Quantidade de séries em @p data.
 * @param plot       Área de plotagem em pixels.
 */
void draw_legend(Data *data, int data_count, PlotArea *plot);

/**
 * @brief Retorna a quantidade de pontos de uma série.
 *
 * @param data Série de dados.
 * @return Valor de @c data->size, ou 0 se @p data for NULL.
 */
int data_size(Data *data);

#endif