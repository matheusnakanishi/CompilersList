CC = gcc                
CFLAGS = -Wall -g       
TARGET = portugol       
SRC = portugol.c        

# Regra para compilar o programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regra para limpar arquivos compilados
clean:
	rm -f $(TARGET)