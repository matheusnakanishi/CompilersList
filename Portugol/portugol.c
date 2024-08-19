#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ALGORITMO 1
#define INICIO 2
#define FIM 3
#define VARIAVEIS 4
#define REAL 5
#define INTEIRO 6
#define CARACTERE 7
#define LOGICO 8
#define VETOR 9
#define MATRIZ 10
#define TIPO 11
#define FUNCAO 12
#define PROCEDIMENTO 13
#define SE 14
#define ENTAO 15
#define SENAO 16
#define ENQUANTO 17
#define FACA 18
#define PARA 19
#define DE 20
#define ATE 21
#define PASSO 22
#define REPITA 23
#define LEIA 24
#define IMPRIMA 25
#define VERDADEIRO 26
#define FALSO 27
#define E 28
#define OU 29
#define NAO 30
#define DIV 31
#define PONTO_VIRG 32
#define VIRGULA 33
#define DOIS_PONTOS 34
#define PONTO 35
#define ABRE_COLCH 36
#define FECHA_COLCH 37
#define ABRE_PAREN 38
#define FECHA_PAREN 39
#define IGUAL 40
#define DIFERENTE 41
#define MAIOR 42
#define MAIOR_IGUAL 43
#define MENOR 44
#define MENOR_IGUAL 45
#define MAIS 46
#define MENOS 47
#define VEZES 48
#define DIVISAO 49
#define ATRIBUICAO 50
#define ID 51
#define NUM_INT 52
#define NUM_REAL 53

char *input;
int token;
char last_token[5];
int error_flag;
int first_print = 1;
int row = 1;
int col = 1;

int getToken() {
    while (*input == ' ') 
        input++; // Ignora espaços em branco

    if (*input == '\t') {
        input++;
        col += 4;
    }

    if (strncmp(input, "algoritmo", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return ALGORITMO;
    }
    if (strncmp(input, "inicio", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return INICIO;
    }
    if (strncmp(input, "fim", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return FIM;
    }
    if (strncmp(input, "variaveis", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return VARIAVEIS;
    }
    if (strncmp(input, "inteiro", 7) == 0 && !isalnum(input[7])) {
        strncpy(last_token, input, 7);
        last_token[7] = '\0';
        input += 7;
        col += 7;
        return INTEIRO;
    }
    if (strncmp(input, "real", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return REAL;
    }
    if (strncmp(input, "caractere", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return CARACTERE;
    }
    if (strncmp(input, "logico", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return LOGICO;
    }
    if (strncmp(input, "vetor", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return VETOR;
    }
    if (strncmp(input, "matriz", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return MATRIZ;
    }
    if (strncmp(input, "tipo", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return TIPO;
    }
    if (strncmp(input, "funcao", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return FUNCAO;
    }
    if (strncmp(input, "procedimento", 12) == 0 && !isalnum(input[12])) {
        strncpy(last_token, input, 12);
        last_token[12] = '\0';
        input += 12;
        col += 12;
        return PROCEDIMENTO;
    }
    if (strncmp(input, "se", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return SE;
    }
    if (strncmp(input, "entao", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return ENTAO;
    }
    if (strncmp(input, "senao", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return SENAO;
    }
    if (strncmp(input, "enquanto", 8) == 0 && !isalnum(input[8])) {
        strncpy(last_token, input, 8);
        last_token[8] = '\0';
        input += 8;
        col += 8;
        return ENQUANTO;
    }
    if (strncmp(input, "faca", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return FACA;
    }
    if (strncmp(input, "para", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return PARA;
    }
    if (strncmp(input, "de", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return DE;
    }
    if (strncmp(input, "ate", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return ATE;
    }
    if (strncmp(input, "passo", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return PASSO;
    }
    if (strncmp(input, "leia", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return LEIA;
    }
    if (strncmp(input, "imprima", 7) == 0 && !isalnum(input[7])) {
        strncpy(last_token, input, 7);
        last_token[7] = '\0';
        input += 7;
        col += 7;
        return IMPRIMA;
    }
    if (strncmp(input, "verdadeiro", 10) == 0 && !isalnum(input[10])) {
        strncpy(last_token, input, 10);
        last_token[10] = '\0';
        input += 10;
        col += 10;
        return VERDADEIRO;
    }
    if (strncmp(input, "falso", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return FALSO;
    }
    if (*input == 'e') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return E;
    }
    if (strncmp(input, "ou", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return OU;
    }
    if (strncmp(input, "nao", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return NAO;
    }
    if (strncmp(input, "div", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return DIV;
    }

    if (*input == ';') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return PONTO_VIRG;
    }
    if (*input == ',') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return VIRGULA;
    }
    if (*input == ':') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return DOIS_PONTOS;
    }
    if (*input == '.') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return PONTO;
    }
    if (*input == '[') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return ABRE_COLCH;
    }
    if (*input == ']') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return FECHA_COLCH;
    }
    if (*input == '(') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return ABRE_PAREN;
    }
    if (*input == ')') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return FECHA_PAREN;
    }
    if (*input == '=') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return IGUAL;
    }
    if (*input == '>') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return MAIOR;
    }
    if (*input == '<') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return MENOR;
    }
    if (*input == '+') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return MAIOR;
    }
    if (*input == '-') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return MENOS;
    }
    if (*input == '*') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return VEZES;
    }
    if (*input == '/') {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return DIVISAO;
    }
    if (strncmp(input, "<>", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return DIFERENTE;
    }
    if (strncmp(input, ">=", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return MAIOR_IGUAL;
    }
    if (strncmp(input, "<=", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return MENOR_IGUAL;
    }
    if (strncmp(input, "<-", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return ATRIBUICAO;
    }

    // Verifica se é um número
    if (isdigit(*input)) {
        char *start = input;
        input++;
        while (isdigit(*input)) 
            input++;
        strncpy(lastTokenValue, start, input - start);  // Copia o número para lastTokenValue
        lastTokenValue[input - start] = '\0';           // Adiciona o terminador de string
        return NUM_INT;
    }
    if (isdigit(*input)) {
        char *start = input;
        input++;
        row++;
        while (isdigit(*input)) {
            input++;
            row++
        }
            
        if (*input == '.') {
            input++;
            row++;
            if (isdigit(*input)) {
                input++
                row++;
                while (isdigit(*input)) {
                    input++;
                    row++
                }
            }
            else
                return -1;
        }
            
        strncpy(lastTokenValue, start, input - start);  // Copia o número para lastTokenValue
        lastTokenValue[input - start] = '\0';           // Adiciona o terminador de string
        return NUM_REAL;
    }
    //Identificador
    if (isalpha(*input) || *input == '_') {
        char *start = input;
        input++;
        row++;

        while(isalnum(*input) || *input == '_') {
            row++;
            input++;
        }

        strncpy(lastTokenValue, start, input - start);  
        lastTokenValue[input - start] = '\0';           
        return ID;
    }

    if (*input == '\0' || *input == '\n') {
        last_token[0] = '\0';
    }
    
    return -1; // Token inválido
}


int main() {
    char buffer[60000];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        input = buffer;
        error_flag = 0;
        row++;
        col = 1;
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