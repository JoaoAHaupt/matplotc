/**
 * @file plotarea.h
 * @brief Área de plotagem: região da janela onde o gráfico é desenhado.
 */

#ifndef PLOTAREA_H
#define PLOTAREA_H

#include "context.h"

/**
 * @brief Retângulo (em pixels) reservado ao gráfico, com suas margens.
 *
 * As margens deixam espaço para valores dos eixos, rótulos e legenda.
 */
typedef struct {
    float padding_left;    ///< Margem esquerda em pixels.
    float padding_right;   ///< Margem direita em pixels.
    float padding_top;     ///< Margem superior em pixels.
    float padding_bottom;  ///< Margem inferior em pixels.

    float width;           ///< Largura útil da área em pixels.
    float height;          ///< Altura útil da área em pixels.

    float left;            ///< Coordenada x da borda esquerda.
    float right;           ///< Coordenada x da borda direita.
    float top;             ///< Coordenada y da borda superior.
    float bottom;          ///< Coordenada y da borda inferior.
} PlotArea;

/**
 * @brief Calcula a área de plotagem a partir do tamanho da janela.
 *
 * As margens são proporcionais ao tamanho da janela (esquerda 10%, direita 5%,
 * topo 5%, base 7,5%) e limitadas a valores mínimos e máximos em pixels:
 * esquerda 50–100, direita 25–60, topo 25–60, base 40–80.
 *
 * @param context Contexto da janela (largura e altura).
 * @return Área de plotagem calculada.
 */
PlotArea create_plotarea(Context *context);

#endif