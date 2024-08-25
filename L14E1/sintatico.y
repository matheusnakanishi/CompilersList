%{

#include <stdio.h>

extern int yylex();
extern char* yytext;

extern int text_before;
extern int lex_error;
extern int col;
extern int eof;

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

// Definindo precedência e associatividade
%left ADD SUB
%left MUL DIV MOD
%right EXP

%%

inicial: expressao EOL  { if(text_before) printf("\n"); if(!lex_error) printf("EXPRESSAO CORRETA"); }
;

expressao: L_PAREN expressao R_PAREN    {}
    | expressao ADD expressao           {}
    | expressao SUB expressao           {}
    | SUB expressao                     {}
    | ADD expressao                     {}
    | expressao MUL expressao           {}
    | expressao DIV expressao           {}
    | expressao EXP expressao           {}
    | expressao MOD expressao           {}
    | final L_PAREN expressao R_PAREN   {}
    | NUM_INT                           {}
    | NUM_REAL                          {}
;

final: SEN  {}
    | COS   {}
    | TAN   {}
    | ABS   {}
;

%%

int main(int argc, char** argv) {
    while(!eof){
        yyparse();
    }
        
    return 0;
}

void yyerror(const char *s) {}