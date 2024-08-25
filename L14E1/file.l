%option noyywrap

%{

#include <stdio.h>
#include <sintatico.tab.h>

int lex_error = 0;
int text_before = 0;

void char_error() {
    if (text_before)
        printf("\n");

    if (!lex_error) {
        printf("Caractere(s) invalido(s) -> [%s", yytext)
    }
    else {
        printf(",%s", yytext);
    }
}

%}

%%

"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"^"     { return EXP; }
"%"     { return MOD; }

"("     { return L_PAREN; }
")"     { return R_PAREN; }

"sen"   { return SEN; }
"cos"   { return COS; }
"tan"   { return TAN; }
"abs"   { return ABS; }

("+"|"-")?[0-9]+    { return NUM_INT; }

("+"|"-")?(("."[0-9]+)|([0-9]+"."[0-9]*))   { return NUM_REAL; }

[a-z][a-z0-9]*  { return VAR; }

\n        { if(lex_error) printf("]"); text_before = 1; return EOL; }

[ \t]     {}

.         { char_error(); lex_error = 1; return -1; }

%%