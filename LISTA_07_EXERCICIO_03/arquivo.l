%option noyywrap

%{
#include <stdio.h>
%}

%%

("aba")+	{printf("%s action 1\n", yytext);}

"a"("b")*"a"	{printf("%s action 2\n", yytext);}

"a"|"b"		{printf("%s action 3\n", yytext);}

%%
int main(){
yylex();
return 0;
}
