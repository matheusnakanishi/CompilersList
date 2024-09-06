%option noyywrap
%option yylineno
%x COMMENT

%{
#include <stdio.h>
#include <string.h>

int first_token = 1;	
int col = 1;		
int start_row;
int start_col;
 
void print_token(char *token, int *first_token) {
	if((*first_token) == 0)
		printf("\n");
	
	*first_token = 0;
	printf("%s", token);
}

void print_num(char *token, char *num, int *first_token) {
	if((*first_token) == 0)
		printf("\n");
	*first_token = 0;
	printf("%s(%s)", token, num);
}

%}



%%

"/*"				{ BEGIN(COMMENT); start_row = yylineno; start_col = col; col += strlen(yytext);}
<COMMENT>"*/"		{ BEGIN(INITIAL); col += strlen(yytext);}

<COMMENT>"/*" { 
    char prox = input();
    if (prox == '\n') 
		yylineno--;
    if (prox == '/') {
        BEGIN(INITIAL); 
        col += 1 + strlen(yytext); 
    } else {
        if (first_token == 0) 
			printf("\n");
        printf("warning:%d:%d: '%s' within block comment", yylineno, col, yytext); 
        col += strlen(yytext);
        if (prox == '\n') yylineno++;
        unput(prox);
    }
    first_token = 0;
}

<COMMENT>\n			{ col = 1;}
<COMMENT>\t 		{ col += 4;}
<COMMENT>.			{ col += strlen(yytext);}
<COMMENT><<EOF>>	{ if(first_token == 0)printf("\n"); printf("error:lexical:%d:%d: unterminated comment", start_row, start_col); exit(1);}

"//"(.)*\n      {} 

"void"          {print_token("VOID", &first_token); col += strlen(yytext);}
"int"           {print_token("INT", &first_token); col += strlen(yytext);}
"char"			{print_token("CHAR", &first_token); col += strlen(yytext);}
"return"		{print_token("RETURN", &first_token); col += strlen(yytext);}
"break"			{print_token("BREAK", &first_token); col += strlen(yytext);}
"switch"		{print_token("SWITCH", &first_token); col += strlen(yytext);}
"case"			{print_token("CASE", &first_token); col += strlen(yytext);}
"default"		{print_token("DEFAULT", &first_token); col += strlen(yytext);}
"do"			{print_token("DO", &first_token); col += strlen(yytext);}
"while"			{print_token("WHILE", &first_token); col += strlen(yytext);}
"for"			{print_token("FOR", &first_token); col += strlen(yytext);}
"if"			{print_token("IF", &first_token); col += strlen(yytext);}
"else"			{print_token("ELSE", &first_token); col += strlen(yytext);}
"typedef"		{print_token("TYPEDEF", &first_token); col += strlen(yytext);}
"struct"		{print_token("STRUCT", &first_token); col += strlen(yytext);}
"+"				{print_token("PLUS", &first_token); col += strlen(yytext);}
"-"				{print_token("MINUS", &first_token); col += strlen(yytext);}
"*"				{print_token("MULTIPLY", &first_token); col += strlen(yytext);}
"/"				{print_token("DIV", &first_token); col += strlen(yytext);}
"%"				{print_token("REMAINDER", &first_token); col += strlen(yytext);}
"++"			{print_token("INC", &first_token); col += strlen(yytext);}
"--"			{print_token("DEC", &first_token); col += strlen(yytext);}
"&"				{print_token("BITWISE_AND", &first_token); col += strlen(yytext);}
"|"				{print_token("BITWISE_OR", &first_token); col += strlen(yytext);}
"~"				{print_token("BITWISE_NOT", &first_token); col += strlen(yytext);}
"^"				{print_token("BITWISE_XOR", &first_token); col += strlen(yytext);}
"!"				{print_token("NOT", &first_token); col += strlen(yytext);}
"&&"			{print_token("LOGICAL_AND", &first_token); col += strlen(yytext);}
"||"			{print_token("LOGICAL_OR", &first_token); col += strlen(yytext);}
"=="			{print_token("EQUAL", &first_token); col += strlen(yytext);}
"!="			{print_token("NOT_EQUAL", &first_token); col += strlen(yytext);}
"<"				{print_token("LESS_THAN", &first_token); col += strlen(yytext);}
">"				{print_token("GREATER_THAN", &first_token); col += strlen(yytext);}
"<="			{print_token("LESS_EQUAL", &first_token); col += strlen(yytext);}
">="			{print_token("GREATER_EQUAL", &first_token); col += strlen(yytext);}
">>"			{print_token("R_SHIFT", &first_token); col += strlen(yytext);}
"<<"			{print_token("L_SHIFT", &first_token); col += strlen(yytext);}
"="				{print_token("ASSIGN", &first_token); col += strlen(yytext);}
"+="			{print_token("ADD_ASSIGN", &first_token); col += strlen(yytext);}
"-="			{print_token("MINUS_ASSIGN", &first_token); col += strlen(yytext);}
";"				{print_token("SEMICOLON", &first_token); col += strlen(yytext);}
","				{print_token("COMMA", &first_token); col += strlen(yytext);}
":"				{print_token("COLON", &first_token); col += strlen(yytext);}
"("				{print_token("L_PAREN", &first_token); col += strlen(yytext);}
")"				{print_token("R_PAREN", &first_token); col += strlen(yytext);}
"{"				{print_token("L_CURLY_BRACKET", &first_token); col += strlen(yytext);}
"}"				{print_token("R_CURLY_BRACKET", &first_token); col += strlen(yytext);}
"["				{print_token("L_SQUARE_BRACKET", &first_token); col += strlen(yytext);}
"]"				{print_token("R_SQUARE_BRACKET", &first_token); col += strlen(yytext);}
"?"				{print_token("TERNARY_CONDITIONAL", &first_token); col += strlen(yytext);}
"#"				{print_token("NUMBER_SIGN", &first_token); col += strlen(yytext);}
"->"			{print_token("POINTER", &first_token); col += strlen(yytext);}
"printf"		{print_token("PRINTF", &first_token); col += strlen(yytext);}
"scanf"			{print_token("SCANF", &first_token); col += strlen(yytext);}
"define"		{print_token("DEFINE", &first_token); col += strlen(yytext);}
"exit"			{print_token("EXIT", &first_token); col += strlen(yytext);}


"'"(\\.|[^\\']){1}"'"|"’"(\\.|[^\\']){1}"’"	{
	if(!first_token)
		printf("\n"); 
	printf("CHARACTER(%.*s)", (int)(strlen(yytext) - 2), yytext + 1);
	first_token = 0;
	col += strlen(yytext);
}

\"([^\\\"]|\\.)*\"	{
	if(!first_token)
		printf("\n");
	printf("STRING(%.*s)", (int)(strlen(yytext) - 2), yytext + 1);
	first_token = 0;
	col += strlen(yytext);
}

" "		{ col++;}
\n		{ col = 1;}
\r 		{}
\t 		{ col += 4;}

("_"|[a-zA-Z])[a-zA-Z_0-9]*	{
	if(first_token == 0)
		printf("\n");
	first_token = 0;
	if(strlen(yytext) > 255)
		printf("error:lexical:%d:%d: identifier too long", yylineno, col);
	else
		printf("IDENTIFIER(%s)", yytext);
	col += strlen(yytext);
}

"0"[1-7][0-7]*					{print_num("NUM_OCTAL", yytext, &first_token); col += strlen(yytext);}
("0x"[0-9a-f]+|"0X"[0-9A-F]+)	{print_num("NUM_HEXA", yytext, &first_token); col += strlen(yytext);}
[0-9]+							{print_num("NUM_INTEGER", yytext, &first_token); col += strlen(yytext);}

. 	{
	if(first_token = 1)
		printf("\n");
	first_token = 0;
	printf("error:lexical:%d:%d: %s", yylineno, col, yytext);
	col += strlen(yytext);
}

%%

int main(int argc, char *argv[]) {
	yylex();
	return 0;
}