/**
 * @file matplotc.h
 * @brief API pública da biblioteca MatplotC.
 *
 * @mainpage MatplotC
 *
 * MatplotC é uma pequena biblioteca em C, inspirada no Matplotlib, para
 * desenhar gráficos (linhas, dispersão, pizza, barras e histograma) usando
 * a biblioteca gráfica raylib.
 *
 * @section uso Uso básico
 * -# Crie a janela com create_context().
 * -# Crie as séries com create_data().
 * -# Chame uma das funções de plotagem: plot_line(), plot_scatter(),
 *    plot_pie(), plot_bar() ou plot_histogram().
 *
 * Durante a exibição, pressione a tecla **S** para salvar uma captura de
 * tela em `grafico.png`. Feche a janela para encerrar a plotagem.
 *
 * @section exemplo Exemplo
 * @code
 * float x[] = {1, 2, 3, 4};
 * float y[] = {2, 4, 3, 5};
 *
 * Context ctx = create_context(800, 600, "Meu grafico");
 * Data serie = create_data(plane, "Serie A", x, "Tempo", y, "Valor", 4);
 * plot_line(&ctx, &plane, &serie, 1);
 * @endcode
 */

#ifndef MATPLOTC_H
#define MATPLOTC_H

#include "context.h"
#include "data.h"
#include "plane.h"

/**
 * @brief Abre uma janela e exibe um gráfico de linhas.
 *
 * Bloqueia até a janela ser fechada. A tecla S salva `grafico.png`.
 *
 * @param context    Configurações da janela.
 * @param plane      Plano cartesiano (limites dos eixos).
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 */
void plot_line(Context *context, Plane *plane, Data *data, int data_count);

/**
 * @brief Abre uma janela e exibe um gráfico de dispersão.
 *
 * Bloqueia até a janela ser fechada. A tecla S salva `grafico.png`.
 *
 * @param context    Configurações da janela.
 * @param plane      Plano cartesiano (limites dos eixos).
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 * @param corr       Se verdadeiro, ativa a exibição da correlação.
 */
void plot_scatter(Context *context, Plane *plane, Data *data, int data_count,
                  bool corr);

/**
 * @brief Abre uma janela e exibe um gráfico de pizza.
 *
 * Cada valor de y vira uma fatia; o valor de x é usado como nome da
 * categoria na legenda. Bloqueia até a janela ser fechada.
 *
 * @param context    Configurações da janela.
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 */
void plot_pie(Context *context, Data *data, int data_count);

/**
 * @brief Abre uma janela e exibe um gráfico de barras.
 *
 * Bloqueia até a janela ser fechada. A tecla S salva `grafico.png`.
 *
 * @param context    Configurações da janela.
 * @param plane      Plano cartesiano (limites dos eixos).
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 */
void plot_bar(Context *context, Plane *plane, Data *data, int data_count);

/**
 * @brief Abre uma janela e exibe um histograma.
 *
 * Bloqueia até a janela ser fechada. A tecla S salva `grafico.png`.
 *
 * @param context    Configurações da janela.
 * @param plane      Plano cartesiano (limites dos eixos e largura da classe
 *                   em @c scale_x).
 * @param data       Vetor de séries de dados.
 * @param data_count Quantidade de séries em @p data.
 */
void plot_histogram(Context *context, Plane *plane, Data *data, int data_count);

#endif