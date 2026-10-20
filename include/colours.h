/**
 * @file colours.h
 * @brief Paleta de cores usada para diferenciar séries e fatias.
 */

#ifndef COLOURS_H
#define COLOURS_H

#include "raylib.h"

/** @brief Quantidade de cores disponíveis na paleta ::COLOURS. */
#define COLOURS_COUNT 8

/**
 * @brief Paleta de cores das séries.
 *
 * Use o índice da série módulo ::COLOURS_COUNT para escolher a cor,
 * de modo que as cores se repitam quando houver mais séries que cores.
 */
extern const Color COLOURS[COLOURS_COUNT];

#endif