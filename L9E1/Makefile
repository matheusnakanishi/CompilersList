# Variáveis
CC = gcc                # Compilador
CFLAGS = -Wall -g       # Flags de compilação: -Wall ativa todos os avisos, -g adiciona símbolos de depuração
TARGET = l9e1       # Nome do executável
SRC = LISTA_09_EXERCICIO_01.c        # Arquivo-fonte

# Regra para compilar o programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regra para limpar arquivos compilados
clean:
	rm -f $(TARGET)