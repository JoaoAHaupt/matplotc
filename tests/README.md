# Testes

Execução:

```
make test
```

O alvo `make test` compila a biblioteca, gera **um executável por arquivo `.c`**
desta pasta e roda todos em sequência, retornando erro se algum falhar.

## Arquivos

| Arquivo | Cobre |
| --- | --- |
| `test_main.c` | Construtores (`create_context`, `create_plane`), `load_data` básico e os caminhos de erro de `show`/`export_png` |
| `test_data.c` | `create_data`, `load_data` (formato, linhas inválidas, crescimento do buffer) e `free_data` |
| `test_export.c` | `export_png`: falhas cedo sem janela; gera um PNG real quando há `DISPLAY` |

As fixtures de dados ficam em `tests/fixtures/`. Os testes que não abrem
janela (tudo menos o export real) rodam em CI headless; o `test_export.c`
pula a parte que precisa de display quando `DISPLAY` está ausente ou vazio.

## framework.h

Mini framework de asserções (sem dependências externas). O objetivo é ter
testes pequenos, sem dependência de bibliotecas externas de teste, que possam
ser executados com `make test`.

Cada arquivo em tests/ é compilado em um executável independente (ver a regra
`test` no Makefile). O teste deve:

1. chamar `MT_BEGIN("nome da suíte")`;
2. usar uma das asserções (`MT_CHECK`, `MT_CHECK_INT`, `MT_CHECK_FLOAT`,
   `MT_CHECK_STR`);
3. retornar `MT_END()` do main.

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

### Várias suítes num só arquivo

`MT_BEGIN`/`MT_END` zeram e reportam os contadores de *uma* suíte. Se um
arquivo tiver mais de um teste, acumule o resultado e devolva o código de
saída no fim — como em `test_data.c`:

```c
static int falhas = 0;

static void reportar(void) {
    printf("    %s: %d/%d asserções\n", failed ? "FALHOU" : "PASSOU",
           total - failed, total);
    if (failed) falhas++;
}

int main(void) {
    test_a();  /* cada um chama MT_BEGIN, asserções e reportar() */
    test_b();
    return falhas == 0 ? 0 : 1;
}
```
