# quetalformigas

baixa o raylib na maquina, depois a gente faz ele ser junto com o projeto

compilar
gcc pie.c ../src/plane.c ../src/data.c ../src/plotarea.c ../src/plotfjms.c \
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
