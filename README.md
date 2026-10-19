# quetalformigas

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

compilar
gcc pie.c ../src/plane.c ../src/data.c ../src/plotarea.c ../src/matplotc.c \
                -I../include -o grafico \
                -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

context - Informacoes sobre a janela
plotarea - informacoes sobre a area em que o grafico sera inserida (queria deixar essa classe sem ser vista pelo usuario final, mas seila)
plane - plano cartesiano
data - os dados (nao sei se gostei muito com eles estao estruturados, talvez seja bom mudar)


Coisas futuras:
  acabar todos os graficos  
  poder fazer graficos com um .txt como entrada
  poder gerar uma imagem do grafico (nao sei se isso eh possivel)
