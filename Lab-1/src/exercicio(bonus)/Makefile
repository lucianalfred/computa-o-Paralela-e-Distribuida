# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g

# Nome do executável
TARGET = task_manager

# Arquivos fonte
SRCS = t_task.c main.c

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJS = $(SRCS:.c=.o)

# Regra padrão (compila tudo)
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada arquivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para recompilar tudo
rebuild: clean all

# Indica que "all" e "clean" não são arquivos
.PHONY: all clean rebuild