%option noyywrap

%{
#include <stdio.h>
%}

%%

(" ")+				{printf("white space\n");};

"--"[a-z]*				{printf("%s comment\n", yytext);}

("."[0-9]+|[0-9]+"."[0-9]*)		{printf("%s REAL\n", yytext);}

[0-9]+					{printf("%s NUM\n", yytext);}

("if"[a-z0-9]+|[a-hj-z][a-z0-9]*|"i"[a-eg-z0-9][a-z0-9]*)	{printf("%s ID\n", yytext);}

"if"					{printf("%s IF\n", yytext);}

\n					;

.					{printf("%s error\n", yytext);}

%%
int main(){
yylex();
return 0;
}
