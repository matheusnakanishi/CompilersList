#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ID 1
#define PLUS 2
#define AST 3
#define L_PAREN 4
#define R_PAREN 5
#define END 6

char *input;
int token;
char last_token[5];
int error_flag;
int first_print = 1;

int getToken() {
    while (*input == ' ') 
        input++; // Ignora espaços em branco

    if (*input == '+') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return PLUS;
    }
    if (*input == '*') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return AST;
    }
    if (*input == '(') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return L_PAREN;
    }
    if (*input == ')') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return R_PAREN;
    }
    if (*input == '$') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        return END;
    }
    
    // Verifica se é um id
    if (isalpha(*input)) {
        input++;
        while(isalnum(*input))
            input++;
        strcpy(last_token, "id");
        last_token[2] = '\0';
        return ID;
    }

    if (*input == '\0' || *input == '\n') {
        last_token[0] = '\0';
    }
    else {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        if(!first_print)
                printf("\n");
            first_print = 0;
        printf("ERRO LEXICO: %s", last_token);
        error_flag = 1;
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
        
        switch (t) {
        case ID:
            expected = "id";
            break;
        
        case PLUS:
            expected = "+";
            break;
        
        case AST:
            expected = "*";
            break;
            
        case L_PAREN:
            expected = "(";
            break;
            
        case R_PAREN:
            expected = ")";
            break;
            
        case END:
            expected = "$";
            break;
        }

        if(!first_print)
                printf("\n");
            first_print = 0;

        printf("ERRO SINTATICO EM: %s ESPERADO: %s", last_token, expected);
        error_flag = 1;
    }
}

void F() {
    if(error_flag == 1)
        return;

    switch(token) {
        case L_PAREN:
            eat(L_PAREN);
            E();
            eat(R_PAREN);
            break;

        case ID:
            eat(ID);
            break;

        default:
            if (!first_print)
                printf("\n");
            first_print = 0;
            printf("ERRO SINTATICO EM: %s ESPERADO: id, (", last_token);
            error_flag = 1;
            break;
    }
}

void TL() {
    if(error_flag == 1)
        return;
    
    if (token == AST) {
        eat(AST);
        F();
        TL();
    }
    else {
        if (token != PLUS && token != R_PAREN && token != END) {
            if (!first_print)
                printf("\n");
            first_print = 0;
            printf("ERRO SINTATICO EM: %s ESPERADO: +, *, ), $", last_token);
            error_flag = 1;
        }
    }
    
}

void T() {
    if(error_flag == 1)
        return;

    if (token == ID || token == L_PAREN) {
        F();
        TL();
    }
    else {
        if (!first_print)
            printf("\n");
        first_print = 0;
        printf("ERRO SINTATICO EM: %s ESPERADO: id, (", last_token);
        error_flag = 1;
    }
    
}

void EL() {
    if(error_flag == 1)
        return;
    
    if(token == PLUS){
        eat(PLUS);
        T();
        EL();
    }
    else {
        if (token != R_PAREN && token != END) {
            if (!first_print)
                printf("\n");
            first_print = 0;
            printf("ERRO SINTATICO EM: %s ESPERADO: +, ), $", last_token);
            error_flag = 1;
        }
    }

}

void E() {
    if(error_flag == 1)
        return;
    
    if (token == ID || token == L_PAREN) {
        T();
        EL();
    }
    else {
        if (!first_print)
            printf("\n");
        first_print = 0;
        printf("ERRO SINTATICO EM: %s ESPERADO: id, (", last_token);
        error_flag = 1;
    }
}

void S() {
    if(error_flag == 1)
        return;

    if (token == ID || token == L_PAREN) {
        E();
        eat(END);
    }
    else {
        if (!first_print)
            printf("\n");
        first_print = 0;
        printf("ERRO SINTATICO EM: %s ESPERADO: id, (", last_token);
        error_flag = 1;
    }
    
}



int main() {
    char buffer[131072];
    
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