%option noyywrap

%{
#include <stdio.h>
int i = 0;
%}

%%

[0-9]+"e"("+"|"-")?[0-9]+	{if(i == 1){printf("\n");}printf("REAL %s", yytext);i=1;}
"+"				{if(i == 1){printf("\n");}printf("MAIS");i=1;}
"-"				{if(i == 1){printf("\n");}printf("MENOS");i=1;}
[0-9]+				{if(i == 1){printf("\n");}printf("INTEIRO %s", yytext);i=1;}
"his"				{if(i == 1){printf("\n");}printf("DELE");i=1;}
"hers"				{if(i == 1){printf("\n");}printf("DELA");i=1;}
"he"				{if(i == 1){printf("\n");}printf("ELE");i=1;}
"she"				{if(i == 1){printf("\n");}printf("ELA");i=1;}
"cats"				{if(i == 1){printf("\n");}printf("GATOS");i=1;}
"cat"				{if(i == 1){printf("\n");}printf("GATO");i=1;}
"cars"				{if(i == 1){printf("\n");}printf("CARROS");i=1;}
"car"				{if(i == 1){printf("\n");}printf("CARRO");i=1;}
\n				;
[[:space:]]+			;
.				{if(i == 1){printf("\n");}printf("ERRO");i=1;}


%%
int main(){
	yylex();
	return 0;
}

