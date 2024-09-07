%{
    
#include <stdio.h>
#include <string.h>

extern int yylex();
extern char invalid_token[16];
extern int invToken_col;
extern int invToken_row;
extern int first_token;
extern int yychar;

int s_error = 0;
char buffer[2048] = "";

void yyerror(void *s);

void getBuffer(int nline) {
    fseek(stdin, 0, SEEK_SET);
    for(int i = 0; i < nline; i++) 
        fgets(buffer, 2048, stdin);

    if(buffer[0] == '\n') \
        buffer[0] = ' ';
    if(buffer[strlen(buffer) - 1] == '\n') 
        buffer[strlen(buffer) - 1] = '\0';
}

%}

%union {
    struct {
        char *value;
        int col;
        int row;
    } token;
}

%token END
%token ERRO

%token NUMBER_SIGN
%token DEFINE
%token L_CURLY
%token R_CURLY
%token L_PAREN
%token R_PAREN
%token L_SQUARE
%token R_SQUARE
%token COMMA
%token SEMICOLON
%token PLUS
%token MINUS
%token MULT
%token DIV
%token MOD
%token INT
%token CHAR
%token VOID
%token DO
%token WHILE
%token IF
%token ELSE
%token FOR
%token PRINTF
%token SCANF
%token RETURN
%token EXIT
%token ADD_ASSIGN
%token SUB_ASSIGN
%token ASSIGN
%token EQUAL
%token NOT_EQUAL
%token LESS
%token LESS_EQUAL
%token GREATER
%token GREATER_EQUAL
%token BIT_AND
%token BIT_OR
%token BIT_XOR
%token BIT_NOT
%token AND
%token OR
%token NOT
%token TERNARY
%token COLON
%token R_SHIFT
%token L_SHIFT
%token INC
%token DEC
%token NUM_INT
%token NUM_HEXA
%token NUM_OCTAL
%token STRING
%token CHARACTER
%token ID

%start Start

%%

Start: Programa END     { s_error = 0; return 0; }
     | Programa ERRO    { s_error = 1; return 0; }
     | error            { s_error = 1; return 0; }
;

Programa: Declaracoes Programa_Quote    { }
        | Funcao Programa_Quote         { }
;

Programa_Quote: Programa Programa_Quote { }
              |                         { }
;

Declaracoes: NUMBER_SIGN DEFINE ID Expressao    { }
           | DeclaraVariaveis                   { }
           | DeclaraPrototipos                  { }
;

Funcao: Tipo Ponteiro ID Parametros L_CURLY DeclaraVariaveis_Quote Comandos R_CURLY { } ;

Ponteiro: MULT Ponteiro { }
        |               { } 
;

DeclaraVariaveis_Quote: DeclaraVariaveis DeclaraVariaveis_Quote { }
                      |                                         { }
;

DeclaraVariaveis: Tipo BlocoVariaveis SEMICOLON { } ;

BlocoVariaveis: Ponteiro ID ExpressaoColchete ExpressaoAtribuicao_Quote VirgulaVariaveis    { } ;

ExpressaoColchete: L_SQUARE Expressao R_SQUARE ExpressaoColchete    { }
                 |                                                  { } 
;

ExpressaoAtribuicao_Quote: ASSIGN ExpressaoAtribuicao   { }
                         |                              { } 
;

VirgulaVariaveis: COMMA BlocoVariaveis  { }
                |                       { } 
; 

DeclaraPrototipos: Tipo Ponteiro ID Parametros SEMICOLON    { } ; 

Parametros: L_PAREN BlocoParametros R_PAREN { } ;

BlocoParametros: Tipo Ponteiro ID ExpressaoColchete VirgulaParametros   { }
               |                                                        { } 
;

VirgulaParametros: COMMA BlocoParametros    { }
                 |                          { } 
;

Tipo: INT   { }
    | CHAR  { }
    | VOID  { } 
;

Bloco: L_CURLY Comandos R_CURLY { } ;

Comandos: ListaComandos Comandos_Quote  { } ;

Comandos_Quote: ListaComandos Comandos_Quote    { }
              |                                 { } 
;

ListaComandos: DO Bloco WHILE L_PAREN Expressao R_PAREN SEMICOLON                                               { }
             | WHILE L_PAREN Expressao R_PAREN Bloco                                                            { }
             | IF L_PAREN Expressao R_PAREN Bloco Else                                                          { }
             | FOR L_PAREN Expressao_Quote SEMICOLON Expressao_Quote SEMICOLON Expressao_Quote R_PAREN Bloco    { }
             | PRINTF L_PAREN STRING VirgulaPrint R_PAREN SEMICOLON                                             { }
             | SCANF L_PAREN STRING COMMA BIT_AND ID R_PAREN SEMICOLON                                          { }
             | EXIT L_PAREN Expressao R_PAREN SEMICOLON                                                         { }
             | RETURN Expressao_Quote SEMICOLON                                                                 { }
             | Expressao SEMICOLON                                                                              { }
             | SEMICOLON                                                                                        { }
             | Bloco                                                                                            { } 
;

Else: ELSE Bloco    { }
    |               { } 
;

Expressao_Quote: Expressao  { }
               |            { } 
;

VirgulaPrint: COMMA Expressao   { }
            |                   { } 
;

Expressao: ExpressaoAtribuicao                  { }
         | Expressao COMMA ExpressaoAtribuicao  { } 
;

ExpressaoAtribuicao: ExpressaoCondicional                                   { }
                   | ExpressaoUnaria OperadorAtribuicao ExpressaoAtribuicao { } 
;

OperadorAtribuicao: ASSIGN      { }
                  | ADD_ASSIGN  { }
                  | SUB_ASSIGN  { } 
;

ExpressaoCondicional: ExpressaoOrLogico Condicional_Quote   { } ;

Condicional_Quote: TERNARY Expressao COLON ExpressaoCondicional { }
                 |                                              { } 
;

ExpressaoOrLogico: ExpressaoAndLogico                       { }
                 | ExpressaoOrLogico OR ExpressaoAndLogico  { } 
;

ExpressaoAndLogico: ExpressaoOr                         { }
                  | ExpressaoAndLogico AND ExpressaoOr  { } 
;

ExpressaoOr: ExpressaoXor                       { }
           | ExpressaoOr BIT_OR ExpressaoXor    { } 
;

ExpressaoXor: ExpressaoAnd                      { }
            | ExpressaoXor BIT_XOR ExpressaoAnd { } 
;

ExpressaoAnd: ExpressaoIgual                        { }
            | ExpressaoAnd BIT_AND ExpressaoIgual   { } 
;

ExpressaoIgual: ExpressaoRelacional                             { }
              | ExpressaoIgual EQUAL ExpressaoRelacional        { }
              | ExpressaoIgual NOT_EQUAL ExpressaoRelacional    { }
;

ExpressaoRelacional: ExpressaoShift                                         { }
                   | ExpressaoRelacional OperadorRelacional ExpressaoShift  { } 
;

OperadorRelacional: LESS            { }
                  | LESS_EQUAL      { }
                  | GREATER         { }
                  | GREATER_EQUAL   { } 
;

ExpressaoShift: ExpressaoAditiva                        { }
              | ExpressaoShift R_SHIFT ExpressaoAditiva { }
              | ExpressaoShift L_SHIFT ExpressaoAditiva { } 
;

ExpressaoAditiva: ExpressaoMultiplicativa                           { }
                | ExpressaoAditiva PLUS ExpressaoMultiplicativa     { }
                | ExpressaoAditiva MINUS ExpressaoMultiplicativa    { } 
;

ExpressaoMultiplicativa: ExpressaoCast                                                  { }
                       | ExpressaoMultiplicativa OperadorMultiplicativo ExpressaoCast   { } 
;

OperadorMultiplicativo: MULT        { }
                      | DIV         { }
                      | MOD   { } 
;

ExpressaoCast: ExpressaoUnaria                              { }
             | L_PAREN Tipo Ponteiro R_PAREN ExpressaoCast  { } 
;

ExpressaoUnaria: ExpressaoPosFixa               { }
               | INC ExpressaoUnaria            { }
               | DEC ExpressaoUnaria            { }
               | OperadorUnario ExpressaoCast   { } 
;

OperadorUnario: BIT_AND { }
              | MULT    { }
              | PLUS    { }
              | MINUS   { }
              | NOT     { }
              | BIT_NOT { } 
;

ExpressaoPosFixa: ExpressaoPrimaria                 { }
                | ExpressaoPosFixa PosFixa_Quote    { } 
;

PosFixa_Quote: L_SQUARE Expressao R_SQUARE          { }
             | L_PAREN PosFixaAtribuicao R_PAREN    { }
             | INC                                  { }
             | DEC                                  { } 
;

PosFixaAtribuicao: ExpressaoAtribuicao VirgulaPosFixa   { }
                 |                                      { }
;

VirgulaPosFixa: COMMA ExpressaoAtribuicao VirgulaPosFixa    { }
              |                                             { } 
;

ExpressaoPrimaria: ID                           { }
                 | Numero                       { }
                 | CHARACTER                    { }
                 | STRING                       { }
                 | L_PAREN Expressao R_PAREN    { } 
;

Numero: NUM_INT     { }
      | NUM_HEXA    { }
      | NUM_OCTAL   { } 
;

%%

void yyerror(void *s) {}

int main(int argc, char *argv[]) {
    yyparse();

    if(!first_token) 
        printf("\n");

    if(s_error) {
        int lcol = yylval.token.col;
        if(yychar == 0 || yychar == END) {
            printf("error:syntax:%d:%d: expected declaration or statement at end of input", yylval.token.row, yylval.token.col);
        
        } else {
            if(strlen(invalid_token) > 0) {
                lcol = invToken_col;
                printf("error:syntax:%d:%d: %s", invToken_row, invToken_col, invalid_token);
            } else {
                printf("error:syntax:%d:%d: %s", yylval.token.row, yylval.token.col, yylval.token.value);
            }
        }
        getBuffer(yylval.token.row);
        
        printf("\n%s\n", buffer);
        for(int i = 0; i < lcol - 1; i++) 
            printf(" ");
        printf("^");

    } else {
        printf("SUCCESSFUL COMPILATION.");
    }

    return 0;
}