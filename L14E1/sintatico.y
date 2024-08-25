%{

#include <stdio.h>

extern int yylex();
extern char* yytext;

void yyerror(void *s);

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

%start

%%


%%

int main(int argc, char** argv) {
    yyparse();
    return 0;
}