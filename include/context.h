/**
 * @file context.h
 * @brief Contexto (janela) onde o gráfico será exibido.
 */

#ifndef CONTEXT_H
#define CONTEXT_H

/**
 * @brief Parâmetros da janela do gráfico.
 */
typedef struct {
    float width;        ///< Largura da janela em pixels.
    float height;       ///< Altura da janela em pixels.
    const char *title;  ///< Título da janela.
} Context;

/**
 * @brief Cria um contexto de janela validando os parâmetros.
 *
 * @param width  Largura da janela em pixels (deve ser maior que 0).
 * @param height Altura da janela em pixels (deve ser maior que 0).
 * @param title  Título da janela (não pode ser NULL nem vazio).
 *
 * @return Contexto preenchido; ou um Context zerado se algum parâmetro for
 *         inválido (uma mensagem de erro é escrita em stderr).
 *
 * @warning A string @p title não é copiada: ela precisa continuar válida
 *          enquanto o contexto for usado.
 */
Context create_context(float width, float height, const char *title);

#endif