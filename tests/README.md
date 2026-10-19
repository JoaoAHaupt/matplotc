# Testes

Execução:

```
make test
```

O alvo `make test` compila a biblioteca, gera **um executável por arquivo `.c`**
desta pasta e roda todos em sequência, retornando erro se algum falhar.
Os testes de barras, histograma, linha, pizza e dispersão substituem as chamadas
de desenho do raylib por capturadores, permitindo verificar os elementos
desenhados sem abrir uma janela.

## framework.h

Mini framework de asserções (sem dependências externas). O objetivo é ter testes pequenos, sem dependência de bibliotecas externas de teste, que possam ser executados com `make test`.

Cada arquivo em tests/ é compilado em um executável independente (ver a regra `test` no Makefile). O teste deve:

1. chamar `MT_BEGIN("nome da suíte")`;
2. usar uma das asserções (`MT_CHECK`, `MT_CHECK_INT`, ...);
3. retornar `MT_END()` do main.

```c
#include "framework.h"
#include "plotarea.h"

int main(void)
{
    MT_BEGIN("plotarea");
    Context c = { 800.0f, 600.0f, "teste" };
    PlotArea a = create_plotarea(&c);

    MT_CHECK(a.width > 0.0f);
    MT_CHECK_FLOAT(680.0f, a.width, 0.001f);

    return MT_END();
}
```

`MT_END()` devolve `0` se tudo passou e `1` caso contrário.
