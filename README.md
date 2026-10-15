# quetalformigas

baixa o raylib na maquina, depois a gente faz ele ser junto com o projeto

compilar
❯ gcc main.c ../src/plane.c ../src/data.c \
          -I../include -o grafico \
          -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
❯ gcc app/main.c src/plane.c src/data.c src/plotarea.c src/plotgraphs.c -Iinclude -o grafico -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

context - Informacoes sobre a janela
plotarea - informacoes sobre a area em que o grafico sera inserida (queria deixar essa classe sem ser vista pelo usuario final, mas seila)
plane - plano cartesiano
data - estruturacao dos dados (nao sei se gostei muito com eles estao estruturados, talvez seja bom mudar)
plotgraphs - desenho dos graficos em si (eu criei mas pode ser reorganizado igual tava antes tbm, o que o sr windows dono do repositorio preferir)

Coisas futuras:
  acabar todos os graficos  
  poder fazer graficos com um .txt como entrada
  poder gerar uma imagem do grafico (nao sei se isso eh possivel)