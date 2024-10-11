%option noyywrap

%{
#include <stdio.h>
int print_newline = 0;
%}

%%

[0-9]+"e"("+"|"-")?[0-9]+       { if (print_newline) printf("\n"); printf("REAL %s", yytext); print_newline = 1; }
"+"                             { if (print_newline) printf("\n"); printf("MAIS"); print_newline = 1; }
"-"                             { if (print_newline) printf("\n"); printf("MENOS"); print_newline = 1; }
[0-9]+                          { if (print_newline) printf("\n"); printf("INTEIRO %s", yytext); print_newline = 1; }
"his"                           { if (print_newline) printf("\n"); printf("DELE"); print_newline = 1; }
"hers"                          { if (print_newline) printf("\n"); printf("DELA"); print_newline = 1; }
"he"                            { if (print_newline) printf("\n"); printf("ELE"); print_newline = 1; }
"she"                           { if (print_newline) printf("\n"); printf("ELA"); print_newline = 1; }
"cats"                          { if (print_newline) printf("\n"); printf("GATOS"); print_newline = 1; }
"cat"                           { if (print_newline) printf("\n"); printf("GATO"); print_newline = 1; }
"cars"                          { if (print_newline) printf("\n"); printf("CARROS"); print_newline = 1; }
"car"                           { if (print_newline) printf("\n"); printf("CARRO"); print_newline = 1; }
\n                              ;
[[:space:]]+                    ;
.                               { if (print_newline) printf("\n"); printf("ERRO"); print_newline = 1; }

%%
int main(){
        yylex();
        return 0;
}

