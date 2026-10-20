#include "colours.h"

/* As macros de cor da raylib (RED, BLUE, ...) usam CLITERAL, que em C puro
 * não é "constante de expressão": com -Wpedantic o compilador avisa em cada
 * linha daqui. É esperado, não é um erro. */
const Color COLOURS[] = {
    RED,
    BLUE,
    GREEN,
    ORANGE,
    PURPLE,
    MAROON,
    DARKBLUE,
    DARKGREEN
};
