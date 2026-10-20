# MatPlotC

## Dependências

A única dependência externa do matplotc é a **[raylib](https://www.raylib.com/)**
(cabeçalho + biblioteca). No Linux, a raylib ainda precisa dos cabeçalhos de
desenvolvimento de X11/OpenGL.

Forma recomendada — um comando detecta a distro e, se a raylib não estiver nos
repositórios, compila a versão fixada (5.5.0) em `$HOME/.local`;
No Windows, execute o comando em um shell MinGW64, UCRT64 ou CLANG64 do
MSYS2:

```
make deps                # equivale a ./scripts/setup-deps.sh
```



make deps; o script instala o GCC e a raylib para a arquitetura do shell.

Para conferir se já está tudo disponível:

```
make check-deps
```

Se a raylib foi instalada pelo script (fora do sistema), informe o prefixo na
compilação:

```
make RAYLIB_PREFIX=$HOME/.local
```

Para instalar em outro prefixo ou fixar outra versão:

```
PREFIX=$HOME/.local RAYLIB_VERSION=5.5.0 ./scripts/setup-deps.sh
```

baixa o raylib na maquina, depois a gente faz ele ser junto com o projeto

## Uso

A interface pública está em `matplotc.h`, organizada em 4 módulos:

- **Contexto** — `create_context`, `show`
- **Dados** — `create_data`, `load_data`, `free_data`
- **Gráficos** — `plot_line`, `plot_scatter`, `plot_bar`, `plot_pie`, `plot_histogram`
- **Exportação** — `export_png`

```c
#include "matplotc.h"

int main(void) {
  Context ctx = create_context(1000, 800, "Meu grafico");
  Plane plane = create_plane(0, 10, 1.0f, 0, 100, 10.0f, true);
  float x[] = {1, 2, 3, 4, 5};
  float y[] = {10, 40, 35, 70, 90};
  Data d = create_data(plane, "Serie", x, "Tempo", y, "Valor", 5);

  plot_line(&ctx, &plane, &d, 1);
  show(&ctx);                         /* janela interativa */
  /* ou, sem janela: export_png(&ctx, "grafico.png"); */
  return 0;
}
```

Os headers internos ficam em `include/internal/` e não fazem parte da API:
`PlotArea`, `create_plotarea`, `create_line`/`create_bar`/... e `draw_*` são
detalhes de implementação.

Modo de entrada por arquivo (`load_data`): um `.txt`/`.csv` com duas colunas
(x e y), separadas por espaço ou vírgula; linhas vazias e iniciadas com `#`
são ignoradas. Exemplo em `examples/vendas.txt`.
