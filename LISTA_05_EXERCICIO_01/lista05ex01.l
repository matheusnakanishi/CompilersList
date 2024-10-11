%option noyywrap

%{
#include <stdio.h>
%}

%%

"+"|"-"           { printf("%s\n", yytext); }
[a-z]+[0-9]*[a-z] { printf("%s\n", yytext); }
[0-9]+("e"([0-9]+|([+-][0-9]+)))? { printf("%s\n", yytext); }
\n		  ;
.                 { printf("ERRO\n"); }

%%

int main() {
    yylex();
    return 0;
}

