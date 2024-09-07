%option noyywrap
%option yylineno
%x COMMENT

%{

#include <sintatico.tab.h>

extern YYSTYPE yylval;

int first_token = 1;	
int col = 1;		
int start_row;
int start_col;
int sintax_error = 0;
char invalid_token[16] = "";
int invToken_col;
int invToken_row;

 
void validToken() {
	yylval.token.value = strdup(yytext);
    yylval.token.col = col;
    yylval.token.row = yylineno;
    col += strlen(yytext);
}

void invalidToken() {
	sintax_error = 1;
    strcpy(invalid_token, yytext);
    invToken_row = yylineno;
    invToken_col = col;
    col += strlen(yytext);
}

%}


%%

"/*"				{ BEGIN(COMMENT); start_row = yylineno; start_col = col; validToken();}
<COMMENT>"*/"		{ BEGIN(INITIAL); col += strlen(yytext); validToken(); col -= strlen(yytext);}

<COMMENT>"/*" { 
    char next = input();
    if (next == '\n') 
		yylineno--;
    if (next == '/') {
        BEGIN(INITIAL); 
        col += 1 + strlen(yytext); 
    } else {
        if (!first_token) 
			printf("\n");

        printf("warning:%d:%d: '%s' within block comment", yylineno, col, yytext); 
        col += strlen(yytext);

        if (next == '\n') 
			yylineno++;

        unput(next);
		first_token = 0;
    }
}

<COMMENT>\n			{ col = 1;}
<COMMENT>.			{ validToken();}
<COMMENT><<EOF>>	{ if(!first_token)printf("\n"); printf("error:lexical:%d:%d: unterminated comment", start_row, start_col); exit(1);}

<<EOF>>			{return END;}

"//"(.)*\n      {validToken();} 

"void"          {validToken(); return VOID;}
"int"           {validToken(); return INT;}
"char"			{validToken(); return CHAR;}
"return"		{validToken(); return RETURN;}
"break"			{invalidToken();}
"switch"		{invalidToken();}
"case"			{invalidToken();}
"default"		{invalidToken();}
"while" 		{validToken(); return WHILE; }
"do"			{validToken(); return DO;}
"for"			{validToken(); return FOR;}
"if"			{validToken(); return IF;}
"typedef"		{invalidToken();}
"struct"		{invalidToken();}
"+"				{validToken(); return PLUS;}
"-"				{validToken(); return MINUS;}
"*"				{validToken(); return MULT;}
"/"				{validToken(); return DIV;}
"%"				{validToken(); return MOD;}
"++"			{validToken(); return INC;}
"--"			{validToken(); return DEC;}
"&"				{validToken(); return BIT_AND;}
"|"				{validToken(); return BIT_OR;}
"~"				{validToken(); return BIT_NOT;}
"^"				{validToken(); return BIT_XOR;}
"!"				{validToken(); return NOT;}
"&&"			{validToken(); return AND;}
"||"			{validToken(); return OR;}
"=="			{validToken(); return EQUAL;}
"!="			{validToken(); return NOT_EQUAL;}
"<"				{validToken(); return LESS;}
">"				{validToken(); return GREATER;}
"<="			{validToken(); return LESS_EQUAL;}
">="			{validToken(); return GREATER_EQUAL;}
">>"			{validToken(); return R_SHIFT;}
"<<"			{validToken(); return L_SHIFT;}
"="				{validToken(); return ASSIGN;}
"+="			{validToken(); return ADD_ASSIGN;}
"-="			{validToken(); return SUB_ASSIGN;}
";"				{validToken(); return SEMICOLON;}
","				{validToken(); return COMMA;}
":"				{validToken(); return COLON;}
"("				{validToken(); return L_PAREN;}
")"				{validToken(); return R_PAREN;}
"{"				{validToken(); return L_CURLY;}
"}"				{validToken(); return R_CURLY;}
"["				{validToken(); return L_SQUARE;}
"]"				{validToken(); return R_SQUARE;}
"?"				{validToken(); return TERNARY;}
"#"				{validToken(); return NUMBER_SIGN;}
"->"			{invalidToken();}
"printf"		{validToken(); return PRINTF;}
"scanf"			{validToken(); return SCANF;}
"define"		{validToken(); return DEFINE;}
"exit"			{validToken(); return EXIT;}


"'"(\\.|[^\\']){1}"'"|"’"(\\.|[^\\']){1}"’"	{validToken(); return CHARACTER;}

\"([^\\\"]|\\.)*\"	{validToken(); return STRING;}

" "		{ validToken();}
\n		{ col = 1; if(sintax_error) return ERRO;}

("_"|[a-zA-Z])[a-zA-Z_0-9]*	{
	if(strlen(yytext) > 255) {
		if(first_token == 0)
			printf("\n");
		first_token = 0;
		printf("error:lexical:%d:%d: identifier too long", yylineno, col);
		exit(1);
	}
	validToken();
	return ID;
}

"0"[1-7][0-7]*					{validToken(); return NUM_OCTAL;}
("0x"[0-9a-f]+|"0X"[0-9A-F]+)	{validToken(); return NUM_HEXA;}
[0-9]+							{validToken(); return NUM_INT;}

. 	{
	if(first_token)
		printf("\n");
	first_token = 0;
	printf("error:lexical:%d:%d: %s", yylineno, col, yytext);
	col += strlen(yytext);
	exit(1);
}

%%