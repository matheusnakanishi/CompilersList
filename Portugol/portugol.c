#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Palavras reservadas
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
char last_token[15];
int error_flag;
int first_print = 1;
int row = 0;
int col = 0;
int block_comment = 0;
int error_col;

int getToken() {

    // Continuação de comentário em bloco em outra linha
    if (block_comment) {
        while (*input != '}') {
            if (*input == '\n')
                return 0;
            if (*input == '\0') {
                if(!first_print)
                    printf("\n");
                printf("ERRO LEXICO. Comentario em bloco nao finalizado");
                return 0; //comentário em bloco não finalizado
            }
            input++;
            col++;
        }

        block_comment = 0;
        return 0;
    }

    // Ignora espaços em branco
    while (*input == ' ') {
        input++; 
        col++;
    }

    // Comentário de uma linha
    if (strncmp(input, "//", 2) == 0)
        return 0;

    // Comentário em bloco
    if (*input == '{') {
        block_comment = 1;
        input++;
        col++;
        error_col = col;

        while (*input != '}') {
            if (*input == '\n')
                return 0;
            if (*input == '\0'){
                error_col = col;
                return -1; //comentário em bloco não finalizado
            }
            input++;
            col++;
        }

        block_comment = 0;
        return 0;
    }

    // Palavras reservadas
    if (strncasecmp(input, "algoritmo", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return ALGORITMO;
    }
    if (strncasecmp(input, "inicio", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return INICIO;
    }
    if (strncasecmp(input, "fim", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return FIM;
    }
    if (strncasecmp(input, "variaveis", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return VARIAVEIS;
    }
    if (strncasecmp(input, "inteiro", 7) == 0 && !isalnum(input[7])) {
        strncpy(last_token, input, 7);
        last_token[7] = '\0';
        input += 7;
        col += 7;
        return INTEIRO;
    }
    if (strncasecmp(input, "real", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return REAL;
    }
    if (strncasecmp(input, "caractere", 9) == 0 && !isalnum(input[9])) {
        strncpy(last_token, input, 9);
        last_token[9] = '\0';
        input += 9;
        col += 9;
        return CARACTERE;
    }
    if (strncasecmp(input, "logico", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return LOGICO;
    }
    if (strncasecmp(input, "vetor", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return VETOR;
    }
    if (strncasecmp(input, "matriz", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return MATRIZ;
    }
    if (strncasecmp(input, "tipo", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return TIPO;
    }
    if (strncasecmp(input, "funcao", 6) == 0 && !isalnum(input[6])) {
        strncpy(last_token, input, 6);
        last_token[6] = '\0';
        input += 6;
        col += 6;
        return FUNCAO;
    }
    if (strncasecmp(input, "procedimento", 12) == 0 && !isalnum(input[12])) {
        strncpy(last_token, input, 12);
        last_token[12] = '\0';
        input += 12;
        col += 12;
        return PROCEDIMENTO;
    }
    if (strncasecmp(input, "se", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return SE;
    }
    if (strncasecmp(input, "entao", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return ENTAO;
    }
    if (strncasecmp(input, "senao", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return SENAO;
    }
    if (strncasecmp(input, "enquanto", 8) == 0 && !isalnum(input[8])) {
        strncpy(last_token, input, 8);
        last_token[8] = '\0';
        input += 8;
        col += 8;
        return ENQUANTO;
    }
    if (strncasecmp(input, "faca", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return FACA;
    }
    if (strncasecmp(input, "para", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return PARA;
    }
    if (strncasecmp(input, "de", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return DE;
    }
    if (strncasecmp(input, "ate", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return ATE;
    }
    if (strncasecmp(input, "passo", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return PASSO;
    }
    if (strncasecmp(input, "leia", 4) == 0 && !isalnum(input[4])) {
        strncpy(last_token, input, 4);
        last_token[4] = '\0';
        input += 4;
        col += 4;
        return LEIA;
    }
    if (strncasecmp(input, "imprima", 7) == 0 && !isalnum(input[7])) {
        strncpy(last_token, input, 7);
        last_token[7] = '\0';
        input += 7;
        col += 7;
        return IMPRIMA;
    }
    if (strncasecmp(input, "verdadeiro", 10) == 0 && !isalnum(input[10])) {
        strncpy(last_token, input, 10);
        last_token[10] = '\0';
        input += 10;
        col += 10;
        return VERDADEIRO;
    }
    if (strncasecmp(input, "falso", 5) == 0 && !isalnum(input[5])) {
        strncpy(last_token, input, 5);
        last_token[5] = '\0';
        input += 5;
        col += 5;
        return FALSO;
    }
    if (strncasecmp(input, "e", 1) == 0 && !isalnum(input[1])) {
        strncpy(last_token, input, 1);
        last_token[1] = '\0';
        input++;
        col++;
        return E;
    }
    if (strncasecmp(input, "ou", 2) == 0 && !isalnum(input[2])) {
        strncpy(last_token, input, 2);
        last_token[2] = '\0';
        input += 2;
        col += 2;
        return OU;
    }
    if (strncasecmp(input, "nao", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return NAO;
    }
    if (strncasecmp(input, "div", 3) == 0 && !isalnum(input[3])) {
        strncpy(last_token, input, 3);
        last_token[3] = '\0';
        input += 3;
        col += 3;
        return DIV;
    }

    // Delimitadores
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

    // Número
    if (isdigit(*input)) {
        char *start = input;
        input++;
        col++;
        error_col = col;

        while (isdigit(*input)) {
            input++;
            col++;
        }

        if (*input == '.') {
            input++;
            col++;

            if (isdigit(*input)) {
                input++;
                col++;

                while (isdigit(*input)) {
                    input++;
                    col++;
                }

                strncpy(last_token, start, input - start);  
                last_token[input - start] = '\0';           
                return NUM_REAL;
            }
            else
                strncpy(last_token, start, input - start);  
                last_token[input - start] = '\0';
                return -1;
        }
        else if (*input == ' ' || *input == '\n' || *input == '\0') {
            strncpy(last_token, start, input - start);  
            last_token[input - start] = '\0';           
            return NUM_INT;
        }
        else { 
            while (*input != ' ' && *input && '\n' && *input != '\0') {
                input++;
                col++;
            }
            strncpy(last_token, start, input - start);  
            last_token[input - start] = '\0';
            return -1;
        }
    }

    //Identificador
    if (isalpha(*input) || *input == '_') {
        char *start = input;
        input++;
        col++;
        error_col = col;

        while(isalnum(*input) || *input == '_') {
            col++;
            input++;
        }

        strncpy(last_token, start, input - start);  
        last_token[input - start] = '\0';           
        return ID;
    }

    if (*input == '\0' || *input == '\n') {
        last_token[0] = '\0';
    }
    
    // Armazena o input de erro
    strncpy(last_token, input, 1);
    last_token[1] = '\0';
    error_flag = 1;
    col++; 
    error_col = col;

    return -1; // Token inválido
}



int main() {
    char buffer[60000];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        input = buffer;
        error_flag = 0;
        row++;
        col = 0;

        token = getToken();
        //printf("%d\n", token);

        if (token == -1) {
            if(!first_print)
                printf("\n");

            first_print = 0;
            printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%s'", row, error_col, last_token);
        }
        
        /*if (error_flag != 1){
            if(!first_print)
                printf("\n");
            first_print = 0;
        }*/
    }
    
    return 0;
}