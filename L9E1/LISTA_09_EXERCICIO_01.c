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
int error_flag;
int first_print = 1;

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
        input++;
        while (isdigit(*input)) input++;
        strcpy(last_token,"num\0");
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
    if(error_flag == 1)
        return;
    
    char *expected;
    if (token == t)
        advance();
    else{
        if (last_token[0] == '\0') {
            if(!first_print)
                printf("\n");
            first_print = 0;
            printf("ERRO SINTATICO: CADEIA INCOMPLETA");
            error_flag = 1;
            return;
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

        if(!first_print)
                printf("\n");
            first_print = 0;

        printf("ERRO SINTATICO EM: %s ESPERADO: %s", last_token, expected);
        error_flag = 1;
    }
}

void L() {
    if(error_flag == 1)
        return;

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
            if(!first_print)
                printf("\n");
            first_print = 0;

            printf("ERRO SINTATICO EM: %s ESPERADO: end, ;", last_token);
            error_flag = 1;
    }
}

void E() {
    if(error_flag == 1)
        return;

    eat(NUM);
    eat(EQ);
    eat(NUM);
}

void S() {
    if(error_flag == 1)
        return;

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
            if(!first_print)
                printf("\n");
            first_print = 0;

            printf("ERRO SINTATICO EM: %s ESPERADO: if, begin, print", last_token);
            error_flag = 1;
    }
}



int main() {
    char buffer[60000];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        input = buffer;
        error_flag = 0;
        advance();  // Inicializa o primeiro token
        S();        // Inicia a análise sintática
        if (error_flag != 1){
            if(!first_print)
                printf("\n");
            first_print = 0;

            printf("CADEIA ACEITA");
        }
    }
    
    return 0;
}