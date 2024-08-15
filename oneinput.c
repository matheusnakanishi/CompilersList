#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define IF 1
#define THEN 2
#define ELSE 3
#define BEGIN 4
#define END 5
#define PRINT 6
#define SEMI 7
#define NUM 8
#define EQ 9

char *input;
int token;
char last_token[5];

int getToken() {
    while (*input == ' ') 
        input++; // Ignora espaços em branco

    if (strncmp(input, "if", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        return IF;
    }
    if (strncmp(input, "then", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        return THEN;
    }
    if (strncmp(input, "else", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        return ELSE;
    }
    if (strncmp(input, "begin", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        return BEGIN;
    }
    if (strncmp(input, "end", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        return END;
    }
    if (strncmp(input, "print", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        return PRINT;
    }
    if (*input == ';') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return SEMI;
    }
    if (*input == '=') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return EQ;
    }

    // Verifica se é um número
    if (isdigit(*input) || ((*input == '+' || *input == '-') && isdigit(*(input + 1)))) {
        char *start = input;
        input++;
        while (isdigit(*input)) input++;
        strncpy(last_token, start, input - start);
        last_token[input - start] = '\0'; 
        return NUM;
    }

    if (*input == '\0' || *input == '\n') {
        last_token[0] = '\0';
    }
    
    return -1; // Token inválido
}

void advance() {
    token = getToken();
}

void eat(int t) {
    char *expected;
    if (token == t)
        advance();
    else{
        if (last_token[0] == '\0') {
            printf("ERRO SINTATICO: CADEIA INCOMPLETA");
            exit(1);
        }
        
        switch (t) {
        case IF:
            expected = "if";
            break;
        
        case THEN:
            expected = "then";
            break;
        
        case ELSE:
            expected = "else";
            break;
            
        case BEGIN:
            expected = "begin";
            break;
            
        case END:
            expected = "end";
            break;
            
        case PRINT:
            expected = "print";
            break;
            
        case SEMI:
            expected = ";";
            break;

        case NUM:
            expected = "num";
            break;
        
        case EQ:
            expected = "=";
            break;
        }

        printf("ERRO SINTATICO EM: %s ESPERADO: %s", last_token, expected);
        exit(1);
    }
}

void L() {
    switch (token) {
        case END:
            eat(END);
            break;

        case SEMI:
            eat(SEMI);
            S();
            L();
            break;

        default:
            printf("ERRO SINTATICO EM: %s ESPERADO: end, =", last_token);
            exit(1);
    }
}

void E() {
    eat(NUM);
    eat(EQ);
    eat(NUM);
}

void S() {
    switch (token) {
        case IF:
            eat(IF);
            E();
            eat(THEN);
            S();
            eat(ELSE);
            S();
            break;

        case BEGIN:
            eat(BEGIN);
            S();
            L();
            break;

        case PRINT:
            eat(PRINT);
            E();
            break;

        default:
            printf("ERRO SINTATICO EM: %s ESPERADO: if, begin, print", last_token);
            exit(1);
    }
}



int main() {
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin)) {
        input = buffer;
        advance();  // Inicializa o primeiro token
        S();        // Inicia a análise sintática
        if (token == -1) 
            printf("CADEIA ACEITA");
    }
    
    return 0;
}