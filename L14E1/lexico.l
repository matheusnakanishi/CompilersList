%option noyywrap

%{

#include <stdio.h>
#include <string.h>
#include <sintatico.tab.h>

int lex_error = 0;
int text_before = 0;
int col = 0;
int eof = 0;

void char_error() {
    if (!lex_error) {
        if (text_before)
            printf("\n");
        printf("Caractere(s) invalido(s) -> [%s", yytext);
    }
    else {
        printf(",%s", yytext);
    }
    lex_error = 1;
}

%}

%%

"+"     { col++; return ADD; }
"-"     { col++; return SUB; }
"*"     { col++; return MUL; }
"/"     { col++; return DIV; }
"^"     { col++; return EXP; }
"%"     { col++; return MOD; }

"("     { col++; return L_PAREN; }
")"     { col++; return R_PAREN; }

"sen"   { col+= 3; return SEN; }
"cos"   { col+= 3; return COS; }
"tan"   { col+= 3; return TAN; }
"abs"   { col+= 3; return ABS; }

("+"|"-")?[0-9]+                            { col+= strlen(yytext); return NUM_INT; }
("+"|"-")?(("."[0-9]+)|([0-9]+"."[0-9]*))   { col+= strlen(yytext); return NUM_REAL; }
[a-z][a-z0-9]*                              { col+= strlen(yytext); return VAR; }

\n        { if(lex_error) printf("]"); col = 0; text_before = 1; lex_error = 0;  return EOL; }
[ \t]     { col++; }
<<EOF>>   { if(lex_error) printf("]"); eof = 1; return EOL; }
.         { col++; char_error(); return ERRO; }

%%