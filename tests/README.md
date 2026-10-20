# Testes

Execução:

```
make test
```

O alvo `make test` compila a biblioteca, gera **um executável por arquivo `.c`**
desta pasta e roda todos em sequência, retornando erro se algum falhar.

## framework.h

Mini framework de asserções (sem dependências externas). O objetivo é ter testes pequenos, sem dependência de bibliotecas externas de teste, que possam ser executados com `make test`.

Cada arquivo em tests/ é compilado em um executável independente (ver a regra `test` no Makefile). O teste deve:

1. chamar `MT_BEGIN("nome da suíte")`;
2. usar uma das asserções (`MT_CHECK`, `MT_CHECK_INT`, ...);
3. 3. retornar `MT_END()` do main.

```c
#include "framework.h"
#include "matplotc.h"

int main(void)
{
    MT_BEGIN("context and plane");
    Context c = create_context(800.0f, 600.0f, "teste");
    MT_CHECK_FLOAT(800.0f, c.width, 0.001f);

    Plane p = create_plane(0, 10, 1.0f, 0, 10, 1.0f, false);
    MT_CHECK_FLOAT(10.0f, p.x_min_max[1], 0.001f);

    return MT_END();
}
```

`MT_END()` devolve `0` se tudo passou e `1` caso contrário.
