# Compilação
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -O2 -Iinclude -Iinclude/internal -MMD -MP
LDFLAGS  :=

PREFIX   ?= /usr/local
INCDIR   := $(PREFIX)/include/matplotc
LIBDIR   := $(PREFIX)/lib

# Dependência externa: raylib
# Localização (opcional), para raylib instalado fora dos diretórios do sistema:
#   make RAYLIB_PREFIX=$HOME/.local
#   ou: export RAYLIB_PREFIX=$HOME/.local
ifneq ($(RAYLIB_PREFIX),)
  CFLAGS          += -I$(RAYLIB_PREFIX)/include
  LDFLAGS         += -L$(RAYLIB_PREFIX)/lib
  RUNTIME_RPATH    := -Wl,-rpath,$(RAYLIB_PREFIX)/lib
  PKG_CONFIG_PATH := $(RAYLIB_PREFIX)/lib/pkgconfig$(if $(PKG_CONFIG_PATH),:$(PKG_CONFIG_PATH))
  export PKG_CONFIG_PATH
endif

# Detecção via pkg-config, com fallback para os nomes padrão das libs de sistema.
PKG_CONFIG   ?= pkg-config
RAYLIB_FOUND := $(shell $(PKG_CONFIG) --exists raylib 2>/dev/null && echo 1)

ifeq ($(RAYLIB_FOUND),1)
  RAYLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags raylib)
  RAYLIB_LIBS   := $(shell $(PKG_CONFIG) --libs raylib)
else
  RAYLIB_CFLAGS :=
  RAYLIB_LIBS   := -lraylib -lGL -lpthread -ldl -lrt -lX11
endif

CFLAGS += $(RAYLIB_CFLAGS)
LDLIBS := $(RAYLIB_LIBS) -lm

# Diretórios
SRC_DIR    := src
INC_DIR    := include
APP_DIR    := app
TEST_DIR   := tests
BUILD_DIR  := build
OBJ_DIR    := $(BUILD_DIR)/obj
LIB_DIR    := lib
BIN_DIR    := bin
TEST_BIN   := $(BUILD_DIR)/tests

LIB_NAME   := matplotc
STATIC_LIB := $(LIB_DIR)/lib$(LIB_NAME).a
SHARED_LIB := $(LIB_DIR)/lib$(LIB_NAME).so

APP_SRC    := $(APP_DIR)/main.c
APP_STATIC := $(BIN_DIR)/$(LIB_NAME)_static
APP_SHARED := $(BIN_DIR)/$(LIB_NAME)_dynamic

# Objetos
SRCS      := $(wildcard $(SRC_DIR)/*.c)
OBJS      := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

# Cabeçalhos públicos (o que o usuário inclui). Os internos em
# include/internal/ não são instalados: não são API. O -Iinclude/internal no
# CFLAGS só serve para compilar a própria biblioteca.
HEADERS   := $(wildcard $(INC_DIR)/*.h)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN)/%,$(TEST_SRCS))

# Targets padrão
.PHONY: all libs app run test install clean deps check-deps

all: libs app

# Bibliotecas estática e dinâmica
libs: $(STATIC_LIB) $(SHARED_LIB)

$(STATIC_LIB): $(OBJS) | $(LIB_DIR)
	ar rcs $@ $^

$(SHARED_LIB): $(OBJS) | $(LIB_DIR)
	$(CC) -shared -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Aplicação cliente
# Sem -MMD/-MP aqui: senão o .d do executável seria gerado dentro de bin/.
APP_CFLAGS := $(filter-out -MMD -MP,$(CFLAGS))

app: $(APP_STATIC) $(APP_SHARED)

# Ligação estática
$(APP_STATIC): $(APP_SRC) $(STATIC_LIB) $(HEADERS) | $(BIN_DIR)
	$(CC) $(APP_CFLAGS) $(LDFLAGS) $(APP_SRC) $(STATIC_LIB) -o $@ $(LDLIBS)

# Ligação dinâmica
# ($$ORIGIN/../lib permite rodar sem LD_LIBRARY_PATH e sem instalar)
$(APP_SHARED): $(APP_SRC) $(SHARED_LIB) $(HEADERS) | $(BIN_DIR)
	$(CC) $(APP_CFLAGS) $(LDFLAGS) $(APP_SRC) -L$(LIB_DIR) -l$(LIB_NAME) \
	    -Wl,-rpath,'$$ORIGIN/../lib' $(RUNTIME_RPATH) -o $@ $(LDLIBS)

run: $(APP_STATIC)
	./$(APP_STATIC)

# --- Dependências externas ---------------------------------------------------
# make deps        -> instala/compila a raylib (scripts/setup-deps.sh)
# make check-deps  -> apenas verifica se a raylib está disponível
deps:
	./scripts/setup-deps.sh

check-deps:
	@echo '#include <raylib.h>' | \
	    $(CC) -x c - -o /dev/null -c $(RAYLIB_CFLAGS) 2>/dev/null \
	    && echo "raylib: OK$(if $(RAYLIB_FOUND), (pkg-config))" \
	    || { \
	        echo "ERRO: raylib não encontrada."; \
	        echo "Instale com 'make deps' ou siga a seção Dependências do README."; \
	        exit 1; \
	    }

# Testes automatizados
# Cada tests/*.c vira um executável em build/tests/ que é executado em seguida.
# A saída e o código de saída indicam aprovação ou falha.
test: libs $(TEST_BINS)
	@fail=0; \
	for t in $(TEST_BINS); do \
	    echo "==> $$t"; \
	    ./$$t || fail=1; \
	done; \
	if [ -z "$(TEST_BINS)" ]; then \
	    echo "Nenhum teste encontrado em $(TEST_DIR)/"; \
	elif [ $$fail -ne 0 ]; then \
	    echo "RESULTADO: FALHA"; exit 1; \
	else \
	    echo "RESULTADO: APROVADO"; \
	fi

$(TEST_BIN)/%: $(TEST_DIR)/%.c $(STATIC_LIB) $(HEADERS) | $(TEST_BIN)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(STATIC_LIB) -o $@ $(LDLIBS)

# Instalação
# Bibliotecas em $(PREFIX)/lib e headers em $(PREFIX)/include/matplotc.
# Depois de instalar fora de /usr/local, pode ser necessário:
#   export LD_LIBRARY_PATH=$$HOME/.local/lib:$$LD_LIBRARY_PATH
install: libs
	install -Dm644 $(STATIC_LIB) $(DESTDIR)$(LIBDIR)/$(notdir $(STATIC_LIB))
	install -Dm755 $(SHARED_LIB) $(DESTDIR)$(LIBDIR)/$(notdir $(SHARED_LIB))
	install -d $(DESTDIR)$(INCDIR)
	install -m644 $(HEADERS) $(DESTDIR)$(INCDIR)/
	@echo "Instalado em $(DESTDIR)$(LIBDIR) e $(DESTDIR)$(INCDIR)"

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR)

# Diretórios
$(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(TEST_BIN):
	mkdir -p $@

# Dependências geradas pelo compilador
-include $(DEPS)
