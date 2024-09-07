# Variáveis
CC = gcc                # Compilador
CFLAGS = -Wall -g       # Flags de compilação: -Wall ativa todos os avisos, -g adiciona símbolos de depuração
TARGET = l10e4       # Nome do executável
SRC = LISTA_10_EXERCICIO_4.c        # Arquivo-fonte

# Regra para compilar o programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regra para limpar arquivos compilados
clean:
	rm -f $(TARGET)