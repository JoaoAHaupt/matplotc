# MatPlotC

Biblioteca de plotagem de gráficos, inspirado no MatPlotLib, usando **[raylib](https://www.raylib.com/)** para renderização.

Membros:
- Felipe Cassio Rocha de Oliveira Lima
- João Augusto Haupt Fonseca Oliveira
- Mateus Cruzatto Ramos
- Sarah Antunes

## Dependências

A única dependência externa do matplotc é a **[raylib](https://www.raylib.com/)**
(cabeçalho + biblioteca). No Linux, a raylib ainda precisa dos cabeçalhos de
desenvolvimento de X11/OpenGL.

Forma recomendada — um comando detecta a distro e, se a raylib não estiver nos
repositórios, compila a versão fixada (5.5.0) em `$HOME/.local`:

```
make deps                # equivale a ./scripts/setup-deps.sh
```

No Windows, execute o comando em um shell MinGW64, UCRT64 ou CLANG64 do
MSYS2. O script instala o GCC e a raylib para a arquitetura do shell.

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

## Compilação

```
make            # biblioteca (lib/) + aplicação de exemplo (bin/)
make RAYLIB_PREFIX=$HOME/.local   # se a raylib foi instalada pelo script
make run        # compila e roda a aplicação de exemplo
make install    # instala a biblioteca e os headers públicos (PREFIX=/usr/local)
make clean
```

A aplicação de exemplo (`app/main.c`) apresenta um menu com um gráfico por
opção — útil para ver cada tipo de desenho rapidamente:

| Opção | O que faz |
| --- | --- |
| 1 | Barras (uma série: vendas por mês) |
| 2 | Linhas (uma série) |
| 3 | Dispersão (duas séries, com reta de regressão) |
| 4 | Pizza (participação por categoria) |
| 5 | Histograma (distribuição de amostras) |
| 6 | Barras com dados lidos de `examples/vendas.txt` |
| 7 | Barras com `examples/vendas.txt` e exportação para `grafico.png` |

Nas opções 1-6 abre-se a janela interativa (`show`); a opção 7 demonstra o
`export_png` (gera `grafico.png` sem abrir janela).

## Como funciona

O matplotc é uma biblioteca de plotagem sobre a
**[raylib](https://www.raylib.com/)**, escrita em C11. Ela cuida do desenho
(planos, eixos, escalas, legenda, rótulos) para que quem usa informe apenas os
dados e o tipo de gráfico.

O modelo é o mesmo do `matplotlib`: você **monta** um gráfico e depois
**exibe** (na tela) ou **exporta** (em arquivo). As funções `plot_*` não abrem
janela nem bloqueiam — elas apenas registram o gráfico desejado. Quem abre a
janela é `show()`; quem grava o PNG é `export_png()`.

```
create_context  ─┐
create_plane     │  monta os objetos
create_data     ─┤
plot_bar         │  registra o gráfico escolhido
                 ├─► show()        → janela interativa (loop até fechar)
                 └─► export_png()  → grafico.png (sem janela)
free_data        (libera os dados, se vieram de load_data)
```

### Os 4 módulos da API

A interface pública fica em `include/matplotc.h` e é dividida em 4 módulos.
Cada um cuida de uma etapa do uso:

**1. Contexto** — a janela. `create_context(width, height, title)` valida e
guarda o tamanho e o título. `show(&ctx)` abre a janela, entra no loop de
desenho (60 FPS) e só retorna quando o usuário fecha. Durante o loop, a tecla
`S` salva um screenshot em `grafico.png`.

**2. Dados** — o que será desenhado.

- `create_data(plane, label, x, x_label, y, y_label, size)` associa dois
  vetores de `float` a rótulos. Os vetores pertencem ao chamador: a biblioteca
  só os referencia.
- `load_data(path, plane, label, x_label, y_label)` lê um arquivo `.txt`/`.csv`
  de duas colunas e aloca as arrays internamente.
- `free_data(&data)` libera apenas o que `load_data` alocou. É segura para
  `create_data` (não toca nos vetores do chamador) e para `NULL`.

**3. Gráficos** — o tipo de desenho. Um `plot_*` por tipo:

| Função           | Gráfico                                       | Eixos            |
| ---------------- | --------------------------------------------- | ---------------- |
| `plot_line`      | linhas                                        | plano cartesiano |
| `plot_scatter`   | dispersão (com regressão opcional via `corr`) | plano cartesiano |
| `plot_bar`       | barras (suporta várias séries)                | plano cartesiano |
| `plot_histogram` | histograma (bins por `scale_x`)               | plano cartesiano |
| `plot_pie`       | pizza (fatias por categoria)                  | não usa plano    |

Todas recebem `context`, `plane` (exceto a pizza), o(s) `data` e
`data_count` — o número de séries. O gráfico fica registrado até que outra
`plot_*` o substitua, e é isso que `show`/`export_png` desenham.

**4. Exportação** — `export_png(&ctx, "arquivo.png")` renderiza o gráfico
registrado em um arquivo, **sem abrir janela** (usa uma janela oculta da
raylib). Retorna `false` se não houver gráfico registrado ou se o arquivo não
puder ser gravado. Útil para gerar imagens em lote ou em servidores sem tela.

### Roteiro mínimo

```c
#include "matplotc.h"

int main(void) {
  Context ctx = create_context(1000, 800, "Meu grafico");
  Plane plane = create_plane(0, 10, 1.0f, 0, 100, 10.0f, true);
  float x[] = {1, 2, 3, 4, 5};
  float y[] = {10, 40, 35, 70, 90};
  Data d = create_data(plane, "Serie", x, "Tempo", y, "Valor", 5);

  plot_line(&ctx, &plane, &d, 1);   /* registra o gráfico */
  show(&ctx);                       /* janela interativa */
  /* ou, sem janela: export_png(&ctx, "grafico.png"); */
  return 0;
}
```

### Entrada por arquivo

`load_data` lê duas colunas (`x y`) separadas por espaço **ou** vírgula. Linhas
vazias, linhas iniciadas por `#` (comentário) e linhas malformadas são
ignoradas. Exemplo em `examples/vendas.txt`:

```
# Vendas mensais
1, 45
2, 52
5 72      # separador por espaço também vale
```

Os dados carregados pertencem à biblioteca: chame `free_data(&d)` ao terminar.

## Como o desenho funciona (por dentro)

Esta parte é útil para quem for mexer no código da biblioteca.

- **`Plane`** define os limites do plano (`x_min_max`, `y_min_max`) e o passo
  das marcas de escala (`scale_x`, `scale_y`). `lines` liga/desliga as linhas
  de grade.
- **`PlotArea`** é a região retangular onde o gráfico é desenhado, calculada a
  partir do `Context` com margens para os eixos e rótulos (`create_plotarea`).
  É **interna**: quem usa a biblioteca não precisa conhecê-la.
- **`Data`** guarda os vetores, os rótulos de eixo, o rótulo da série (usado na
  legenda) e o `Plane` associado.
- **Cores**: uma paleta fixa de 8 cores (`COLOURS`, em `colours.h`) é usada em
  ciclo — a série _i_ usa `COLOURS[i % 8]`.
- **Fluxo de um frame**: cada tipo de gráfico tem uma função `create_*`
  (interna) que desenha, em ordem, o plano/eixos, os dados, os rótulos dos
  eixos e a legenda. `show` e `export_png` chamam essa mesma função, então a
  imagem exportada é idêntica ao que aparece na tela.
- **Um gráfico por vez**: o registro do gráfico pendente fica em estado interno
  de `matplotc.c` (tipo, ponteiros e contagem). Por isso uma `plot_*` substitui
  a anterior.

### Estrutura dos diretórios

```
include/            # API pública: matplotc.h, context.h, data.h, plane.h
include/internal/   # headers internos (PlotArea, desenho, cores) — não são API
src/                # implementação da biblioteca
  matplotc.c        #   show, export_png, registro do gráfico e os plot_*
  context.c         #   create_context
  plane.c           #   create_plane e desenho do plano/eixos
  plotarea.c        #   create_plotarea (margens)
  data.c            #   create_data, free_data e desenho de rótulos/legenda
  load.c            #   load_data (leitura de arquivo)
  line.c / scatter.c / bar.c / pie.c / hist.c   # um por tipo de gráfico
  colours.c         #   paleta de cores
app/                # aplicação de exemplo (menu interativo)
docs/               # documentação (este README e o relatório)
examples/           # dados de exemplo (vendas.txt)
tests/              # testes automatizados (make test)
```

## Testes

```
make test
```

Cada arquivo em `tests/` vira um executável independente e roda em sequência.
Os testes de `load_data` não abrem janela e rodam em CI headless; o teste de
`export_png` gera um PNG de verdade quando há display (e se ignora sem
`DISPLAY`). Detalhes em `tests/README.md`.
