# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Icodigo

# Fontes e objetos
SRC = codigo\\main.c codigo\\compradores.c codigo\\produtos.c codigo\\vendas.c codigo\\vendedores.c
OBJ = $(SRC:.c=.o)

# Saída
OUT_DIR = codigo\\output
BIN = $(OUT_DIR)\\programa.exe

# Regra principal
all: $(OUT_DIR) $(BIN)

# Compilação do binário
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@

# Criação do diretório de saída (compatível com cmd)
$(OUT_DIR):
	if not exist $(OUT_DIR) mkdir $(OUT_DIR)

# Limpeza dos .o
clean:
	del /Q codigo\\*.o

# Limpeza total
distclean: clean
	del /Q $(BIN)
