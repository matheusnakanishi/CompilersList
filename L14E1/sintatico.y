%{

#include <stdio.h>

extern int yylex();
extern char* yytext;

extern int text_before;
extern int lex_error;
extern int col;
extern int eof;
extern int yychar;

int sintatic_error = 0;
int error_char;
int erro_aux = 0;

void yyerror(const char *s);

%}

%token ADD
%token SUB
%token MUL
%token DIV
%token EXP
%token MOD
%token L_PAREN
%token R_PAREN
%token SEN
%token COS
%token TAN
%token ABS
%token NUM_INT
%token NUM_REAL
%token VAR
%token EOL
%token ERRO

%start inicial

// Definindo precedência
%left ADD SUB
%left MUL DIV
%right EXP

%%

inicial: expressao EOL  { if(text_before) printf("\n"); if(!lex_error && sintatic_error == 0) printf("EXPRESSAO CORRETA"); sintatic_error = 0; }
    | expressao ERRO    { erro_aux = 1; return 0; }
    | error             { if(sintatic_error == -1 || lex_error) return 0; sintatic_error = 1; error_char = yychar; return 0; }
;

expressao: fator {}
    | expressao ADD fator {} 
    | expressao SUB fator {}
;

fator: termo {}
    | fator MUL termo {}
    | fator DIV termo {}
    | fator EXP termo {}
    | fator MOD termo {} 
;

termo: L_PAREN expressao R_PAREN {} 
    | VAR       {}
    | NUM_INT   {}
    | NUM_REAL  {}
    | ADD termo {}
    | SUB termo {}
    | SEN L_PAREN expressao R_PAREN {}
    | COS L_PAREN expressao R_PAREN {}
    | TAN L_PAREN expressao R_PAREN {}
    | ABS L_PAREN expressao R_PAREN {} 
;

%%

int main(int argc, char** argv) {
    while(!eof){
        yyparse();

        if (sintatic_error == 2) {
            if (yychar == EOL) 
                sintatic_error = 0;
            continue;
        }
        if (lex_error && !erro_aux) 
            continue;

        if (erro_aux) { 
            sintatic_error = 0;
            continue;
        }

        if (text_before) 
            printf("\n");

        if (sintatic_error == 1) { // tem erro sintatico

            if (error_char == 0 || error_char == EOL || error_char == YYEMPTY) {  
                printf("A expressao terminou de forma inesperada.");
            } else {
                printf("Erro sinatico na coluna [%d]: %s", col, yytext);
            }
            sintatic_error = 2;

        } else if (sintatic_error == 0) {
            printf("EXPRESSAO CORRETA");
            sintatic_error = 0;     
        }

        text_before = 1; 
    } 
        
    return 0;
}

void yyerror(const char *s) {}