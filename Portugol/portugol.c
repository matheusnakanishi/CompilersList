#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Palavras reservadas
#define ERRO -1
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
#define END 54
#define STRING 55

void START();
void PROGRAMA();
void BV();
void PF();
void BC();
void DPROC();
void PARAMETROS();
void DPARAM();
void TB();
void DI();
void DS();
void DS_PRIME();
void DT();
void VM();
void DIMENSAO();   
void DI_PRIME();
void DIMENSAO_PRIME();
void LC();
void COMANDOS();
void LC_PRIME();
void C_PRIME1();
void C_PRIME2();
void C_PRIME3();
void EXPRESSAO();
void VARIAVEL();
void EI();
void ES();
void EXPRESSAO_PRIME();
void OPR();
void TERMO();
void OPB();
void TERMO_PRIME();
void FATOR();
void FATOR_PRIME();
void VARIAVEL_PRIME();
void EI_PRIME();
void ES_PRIME();

char *input;
int token;
char last_token[15];
int error_flag;
int first_print = 1;
int row = 0;
int col = 0;
int block_comment = 0;
int error_col;
char buffer[131072];
int nova_linha = 0;
    
void prox_linha() {
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;

    row++;
    col = 0;
}


void erro(int flag) {
    if(!first_print)
        printf("\n");
    first_print = 0;

    if(flag)
        printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%s'", row, error_col, last_token);
    else
        printf("ERRO DE SINTAXE. Linha: %d Coluna: %d -> '%s'", row, error_col, last_token);

    exit(1);
}

int getToken() {

    while(1) {
        if (nova_linha) {
            row++;
            col = 0;
            fgets(buffer, sizeof(buffer), stdin);
            input = buffer;
            nova_linha = 0;
        }
        
        // Continuação de comentário em bloco em outra linha
        if (block_comment) {

            while (*input != '}') {

                if (*input == '\n') {
                    nova_linha = 1;
                    continue;
                }

                if (*input == '\0')
                    erro(1);
                
                input++;
                col++;
            }

            block_comment = 0;
        }

        // Ignora espaços em branco
        while (*input == ' ') {
            input++; 
            col++;
        }

        // Comentário de uma linha
        if (strncmp(input, "//", 2) == 0) {
            nova_linha = 1;
            continue;
        }

        // Comentário em bloco
        if (*input == '{') {
            block_comment = 1;
            input++;
            col++;
            error_col = col;

            while (*input != '}') {
                if (*input == '\n') {
                    nova_linha = 1;
                    continue;
                }
                //comentário em bloco não finalizado
                if (*input == '\0')
                    erro(1);
                
                input++;
                col++;
            }

            if (!nova_linha)
                block_comment = 0;
            
            continue;
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
        if (*input == '&') {
            strncpy(last_token, input, 1);
            last_token[1] = '\0';
            input++;
            col++;
            return END;
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

        //String
        if (*input == '"') {
            input++;
            col++;
            error_col = col;

            while (*input != '"') {
                if (*input == '\n' || *input == '\0') 
                    erro(1);
                
                input++;
                col++;
            }
            
            return STRING;
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
                    erro(1);
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
                erro(1);
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
    }
    erro(1); // Token inválido
}

// Sintatico

void advance() {
    token = getToken();
}

void eat(int t) {
    if (token == t)
        advance();
    else    
        printf("erro");
}

void START() {
    if (token == ALGORITMO) {
        PROGRAMA();
        eat(END);
    }
}

void PROGRAMA() {
    if (token == ALGORITMO) {
        eat(ALGORITMO);
        eat(ID);
        eat(PONTO_VIRG);
        BV();
        PF();
        BC();
    }
    else
        printf("erro");
}

void PF() {
    if (token == PROCEDIMENTO){
        DPROC();
        PF();
    }
    else if (token == FUNCAO) {
        PF();
    }
    else if (token == INICIO) {
        return;
    }
}

void DPROC() {
    if (token == PROCEDIMENTO) {
        eat(PROCEDIMENTO);
        eat(ID);
        PARAMETROS();
        eat(PONTO_VIRG);
        DPARAM();
        BV();
        BC();
    }
}

void DF() {
    if (token == FUNCAO) {
        eat(FUNCAO);
        eat(ID);
        PARAMETROS();
        eat(DOIS_PONTOS);
        TB();
        eat(PONTO_VIRG);
        DPARAM();
        BV();
        BC();
        eat(PONTO_VIRG);
    }
}

void PARAMETROS() {
    if (token == DOIS_PONTOS || token) {
        return;
    }
    else if (token == ABRE_PAREN) {
        eat(ABRE_PAREN);
        DI();
        eat(FECHA_PAREN);
    }

}

void DPARAM() {
    if (token == ID || token == TIPO || token == INTEIRO || token == REAL || token == CARACTERE || token == LOGICO) {
        DS();
    }
    else if (token == PROCEDIMENTO || token == FUNCAO || token == VARIAVEIS || token == INICIO) {
        return;
    }

}

void BV() {
    if (token == END || token == PROCEDIMENTO || token == FUNCAO || token == INICIO) {
        return;
    }
    if (token == VARIAVEIS) {
        eat(VARIAVEIS);
        DS();
    }
}

void DS() {
    if (token == ID || token == INTEIRO || token == REAL || token == CARACTERE || token == LOGICO) {
        DV();
        DS_PRIME();
    }
    else if (token == TIPO) {
        DT();
        DS_PRIME();
    }
}

void DS_PRIME() {
    if (token == END || token == PROCEDIMENTO || token == FUNCAO || token == VARIAVEIS || token == INICIO) {
        return;
    }
    else if (token == ID || token == TIPO || token == INTEIRO || token == REAL || token == CARACTERE || token == LOGICO) {
        DS();
    }
}

void DT() {
    if (token == TIPO) {
        eat(TIPO);
        eat(ID);
        eat(IGUAL);
        VM();
        eat(ABRE_COLCH);
        DIMENSAO();
        eat(FECHA_COLCH);
        TB();
        eat(PONTO_VIRG);
    }
}

void DV() {
    if (token == ID || token == INTEIRO || token == REAL || token == CARACTERE || token == LOGICO) {
        TB();
        eat(DOIS_PONTOS);
        DI();
        eat(PONTO_VIRG);
    }
}

void DI() {
    if (token == ID) {
        eat(ID);
        DI_PRIME();
    }
}

void DI_PRIME() {
    if (token == PONTO_VIRG || token == FECHA_PAREN) {
        return;
    }
    else if (token == VIRGULA) {
        eat(VIRGULA);
        DI();
    }
}

void VM() {
    if (token == VETOR) {
        eat(VETOR);
    }
    else if (token == MATRIZ) {
        eat(MATRIZ);
    }
}

void DIMENSAO() {
    if (token == NUM_INT) {
        eat(NUM_INT);
        eat(DOIS_PONTOS);
        eat(NUM_INT);
        DIMENSAO_PRIME();
    }
}

void DIMENSAO_PRIME() {
    if (token == FECHA_COLCH) {
        return;
    }
    else if (token == VIRGULA) {
        eat(VIRGULA);
        DIMENSAO();
    }
}

void TB() {
    if (token == ID) {
        eat(ID);
    }
    else if (token == INTEIRO) {
        eat(INTEIRO);
    }
    else if (token == REAL) {
        eat(REAL);
    }
    else if (token == CARACTERE) {
        eat(CARACTERE);
    }
    else if (token == LOGICO) {
        eat(LOGICO);
    }
}

void BC() {
    if (token == INICIO) {
        eat(INICIO);
        LC();
        eat(FIM);
    }
}

void LC() {
    if (token == ID || token == SE || token == ENQUANTO || token == PARA || token == REPITA || token == LEIA || token == IMPRIMA) {
        COMANDOS();
        eat(PONTO_VIRG);
        LC_PRIME();
    }
}

void LC_PRIME() {
    if (token == ID || token == SE || token == ENQUANTO || token == PARA || token == REPITA || token == LEIA || token == IMPRIMA) {
        LC();
    }
    else if (token == FIM || token == SENAO || token == ATE) {
        return;
    }
}

void COMANDOS() {
    if (token == ID) {
        eat(ID);
        C_PRIME1();
    }
    else if (token == SE) {
        eat(SE);
        EXPRESSAO();
        eat(ENTAO);
        LC();
        C_PRIME2;
    }
    else if (token == ENQUANTO) {
        eat(ENQUANTO);
        EXPRESSAO();
        eat(FACA);
        LC();
        eat(FIM);
        eat(ENQUANTO);
    }
    else if (token == PARA) {
        eat(PARA);
        eat(ID);
        eat(DE);
        EXPRESSAO();
        eat(ATE);
        EXPRESSAO();
        eat(ATE);
        EXPRESSAO();
        C_PRIME3();
    }
    else if (token == REPITA) {
        eat(REPITA);
        LC();
        eat(ATE);
        EXPRESSAO();
    }
    else if (token == LEIA) {
        eat(LEIA);
        eat(ABRE_PAREN);
        VARIAVEL();
        eat(FECHA_PAREN);
    }
    else if (token == IMPRIMA) {
        eat(IMPRIMA);
        eat(ABRE_PAREN);
        EI();
        eat(FECHA_PAREN);
    }
}

void C_PRIME1() {
    if (token == PONTO_VIRG) {
        return;
    }
    else if (token == ABRE_PAREN) {
        eat(ABRE_PAREN);
        EI();
        eat(FECHA_PAREN);
    }
    else if (token == ABRE_COLCH) {
        eat(ABRE_COLCH);
        EI();
        eat(FECHA_COLCH);
        eat(ATRIBUICAO);
        EXPRESSAO();
    }
    else if (token == ATRIBUICAO) {
        eat(ATRIBUICAO);
        EXPRESSAO();
    }
}

void C_PRIME2() {
    if (token == FIM) {
        eat(FIM);
        eat(SE);
    }
    if (token == SENAO) {
        eat(SENAO);
        LC();
        eat(FIM);
        eat(SE);
    }
}

void C_PRIME3() {
    if (token == FACA) {
        eat(FACA);
        LC();
        eat(FIM);
        eat(PARA);
    }
    else if (token == PASSO) {
        eat(PASSO);
        EXPRESSAO();
        eat(FACA);
        LC();
        eat(FIM);
        eat(PARA);
    }
    
}

void EXPRESSAO() {
    if (token == ID || token == ABRE_PAREN || token == NUM_INT || token == MAIS || token == MENOS || token == NAO || token == NUM_REAL || token == VERDADEIRO || token == FALSO || token == STRING) {
        ES();
        EXPRESSAO_PRIME();
    }
}

void EXPRESSAO_PRIME() {
    if (token == PONTO_VIRG || token == FECHA_PAREN || token == FECHA_COLCH || token == VIRGULA || token == ENTAO || token == FACA || token == ATE || token == PASSO) {
        return;
    }
    else if (token == IGUAL || token == DIFERENTE || token == MENOR || token == MAIOR || token == MENOR_IGUAL || token == MAIOR_IGUAL) {
        OPR();
        ES();
        EXPRESSAO_PRIME();
    }
}

void ES() {
    if (token == ID || token == ABRE_PAREN || token == NUM_INT || token == NAO || token == NUM_REAL || token == VERDADEIRO || token == FALSO || token == STRING) {
        TERMO();
        ES_PRIME();
    }
    else if (token == MAIS || token == MENOS) {
        OPB();
        TERMO();
        ES_PRIME();
    }
}

void ES_PRIME() {
    if (token == PONTO_VIRG || token == FECHA_PAREN || token == IGUAL || token == FECHA_COLCH || token == VIRGULA || token == ENTAO || token == FACA || token == ATE || token == PASSO || token == DIFERENTE || token == MENOR
        || token == MAIOR || token == MENOR_IGUAL || token == MAIOR_IGUAL) {
        return;
    }
    else if (token == OU) {
        eat(OU);
        TERMO();
        ES_PRIME();
    }
    else if (token == MAIS || token == MENOS) {
        OPB();
        TERMO();
        ES_PRIME();
    }
}

void OPR() {
    if (token == IGUAL) {
        eat(IGUAL);
    }
    else if (token == DIFERENTE) {
        eat(DIFERENTE);
    }
    else if (token == MENOR) {
        eat(MENOR);
    }
    else if (token == MAIOR) {
        eat(MAIOR);
    }
    else if (token == MENOR_IGUAL) {
        eat(MENOR_IGUAL);
    }
    else if (token == MAIOR_IGUAL) {
        eat(MAIOR_IGUAL);
    }
}

void OPB() {
    if (token == MAIS) {
        eat(MAIS);
    }
    else if (token == MENOS) {
        eat(MENOS);
    }
}

void TERMO() {
    if (token == ID || token == ABRE_PAREN || token == NUM_INT || token == NAO || token == NUM_REAL || token == VERDADEIRO || token == FALSO || token == STRING) {
        FATOR();
        TERMO_PRIME();
    }
}

void TERMO_PRIME() {
    if (token == PONTO_VIRG || token == FECHA_PAREN || token == IGUAL || token == FECHA_COLCH || token == VIRGULA || token == ENTAO || token == FACA || token == ATE || token == PASSO || token == OU || token == DIFERENTE
        || token == MENOR || token == MAIOR || token == MENOR_IGUAL || token == MAIOR_IGUAL || token == MAIS || token == MENOS) {
        return;
    }
    else if (token == VEZES) {
        eat(VEZES);
        FATOR();
        TERMO_PRIME();
    }
    else if (token == DIVISAO) {
        eat(DIVISAO);
        FATOR();
        TERMO_PRIME();
    }
    else if (token == DIV) {
        eat(DIV);
        FATOR();
        TERMO_PRIME();
    }
    else if (token == E) {
        eat(E);
        FATOR();
        TERMO_PRIME();
    }
}

void FATOR() {
    if (token == ID) {
        eat(ID);
        FATOR_PRIME();
    }
    else if (token == ABRE_PAREN) {
        eat(ABRE_PAREN);
        EXPRESSAO();
        eat(FECHA_PAREN);
    }
    else if (token == NUM_INT) {
        eat(NUM_INT);
    }
    else if (token == NAO) {
        eat(NAO);
        FATOR();
    }
    else if (token == NUM_REAL) {
        eat(NUM_REAL);
    }
    else if (token == VERDADEIRO) {
        eat(VERDADEIRO);
    }
    else if (token == FALSO) {
        eat(FALSO);
    }
    else if (token == STRING) {
        eat(STRING);
    }
}

void FATOR_PRIME() {
    if (token == PONTO_VIRG || token == FECHA_PAREN || token == IGUAL || token == FECHA_COLCH || token == VIRGULA || token == ENTAO || token == FACA || token == ATE || token == PASSO
        || token == OU || token == DIFERENTE || token == MENOR || token == MAIOR || token == MENOR_IGUAL || token == MAIOR_IGUAL || token == MAIS || token == MENOS || token == VEZES
        || token == DIVISAO || token == DIV || token == E) {
        return;
    }
    else if (token == ABRE_PAREN) {
        eat(ABRE_PAREN);
        EI();
        eat(FECHA_PAREN);
    }
    else if (token == ABRE_COLCH) {
        eat(ABRE_COLCH);
        EI();
        eat(FECHA_COLCH);
    }
}

void VARIAVEL() {
    if (token == ID) {
        eat(ID);
        VARIAVEL_PRIME();
    }
}

void VARIAVEL_PRIME() {
    if (token == FECHA_PAREN) {
        return;
    }
    else if (token == ABRE_COLCH) {
        eat(ABRE_COLCH);
        EI();
        eat(FECHA_COLCH);
    }
}

void EI() {
    if (token == ID || token == ABRE_PAREN || token == NUM_INT || token == MAIS || token == MENOS || token == NAO || token == NUM_REAL || token == VERDADEIRO || token == FALSO || token == STRING) {
        EXPRESSAO();
        EI_PRIME();
    }
}

void EI_PRIME() {
    if (token == FECHA_PAREN || token == FECHA_COLCH) {
        return;
    }
    else if (token == VIRGULA) {
        eat(VIRGULA);
        EI();
    }
}

int main() {
    char buffer[131072];
    
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

// Tirar while
// Quando encontrar \n chamar fgets input = buffer e getToken()
// Reconhecer String