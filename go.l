/* Incluímos as librerías necesarias */

%{
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include "Definicions.h"
#include "XesErros.h"
#include "go.tab.h"
%}

%option noyywrap
%option nounput
%option noinput


/* Definimos as expresións regulares */
NEWLINE           \n
TAB               \t
SPACE             [ ]
RETURN            \r
LINE_COMMENT      \/\/.*

UNICODE_CHAR      .
UNICODE_LETTER    [A-Za-z]
UNICODE_DIGIT     [0-9]

LETTER            {UNICODE_LETTER}|_
DECIMAL_DIGIT     {UNICODE_DIGIT}
BINARY_DIGIT      0|1
OCTAL_DIGIT       0|1|2|3|4|5|6|7
HEX_DIGIT         {DECIMAL_DIGIT}|A|B|C|D|E|F|a|b|c|d|e|f
SEMICOLON         ;
IDENTIFIER        {LETTER}({LETTER}|{UNICODE_DIGIT})*

PLUS              \+
MINUS             -
MULTIPLY          \*
DIVIDE            \/
MODULO            %
EQUAL             ==
NOT_EQUAL         !=
LESS_THAN         <
LESS_THAN_EQUAL   <=
GREATER_THAN      >
GREATER_THAN_EQUAL >=
AND               &
OR                \|
NOT               !
OPEN_PAREN        \(
CLOSE_PAREN       \)
OPEN_BRACKET      \[
CLOSE_BRACKET     \]
OPEN_BRACE        \{
CLOSE_BRACE       \}
COMMA             ,
DOT               \.
AND_OP            &&
OR_OP             \|\|
INCREMENT         \+\+
DECREMENT         --
INCREMENT_EQUAL   \+=
DECREMENT_EQUAL   -=
MULTIPLY_EQUAL    \*=
DIVIDE_EQUAL      \/=
MODULO_EQUAL      %=
AND_EQUAL         &=
OR_EQUAL          \|=
XOR_EQUAL         ^=

LEFT_SHIFT_EQUAL  <<=
RIGHT_SHIFT_EQUAL >>=
LEFT_SHIFT        <<
RIGHT_SHIFT       >>
XOR               \^
AND_XOR           &\^
AND_XOR_EQUAL     &\^=
DEFINITION        :=
ASSINGMENT        =
COLON             :
TILDE             ~
THREE_DOTS        \.\.\.

DECIMAL_DIGITS    {DECIMAL_DIGIT}+
INT_LITERAL       {DECIMAL_DIGITS}
FLOAT_LITERAL     {DECIMAL_DIGITS}\.{DECIMAL_DIGITS}|{DECIMAL_DIGITS}[eE][+-]?{DECIMAL_DIGITS}

RAW_STRING_LITERAL `(_|.)*`
INTERPRETED_STRING_LITERAL \"(_|.)*\"
STRING_LITERAL     {RAW_STRING_LITERAL}|{INTERPRETED_STRING_LITERAL}


/* Definimos as regras devolvendo o valor correspondente a cada expresión. */

%%

{PLUS}              return('+');
{MINUS}             return('-');
{MULTIPLY}          return('*');
{DIVIDE}            return('/');
{MODULO}            return('%');
{AND}               return('&&');
{OR}                return('||');
{XOR}               return('^');
{ASSINGMENT}        return('=');
{EQUAL}             return(EQ);
{LESS_THAN}         return('<');
{GREATER_THAN}      return('>');
{NOT}               return('!');
{NOT_EQUAL}         return(NE);
{LESS_THAN_EQUAL}   return(LT);
{GREATER_THAN_EQUAL}   return(GT);
{OPEN_PAREN}        return('(');
{CLOSE_PAREN}       return(')');
{COMMA}             return(',');
{SEMICOLON}         return(';');
{DOT}               return('.');

{NEWLINE}           return('\n');
{TAB}
{SPACE}
{RETURN}
{LINE_COMMENT}

{STRING_LITERAL}    {yylval.lex = (char *) malloc(sizeof (yytext));yylval.lex = strdup(yytext);return(STRING);}
{INT_LITERAL}       {yylval.val=atof(yytext);return(NUM);}
{FLOAT_LITERAL}     {yylval.val=atof(yytext);return(NUM);}
{IDENTIFIER}        {yylval.lex = (char *) malloc(sizeof (yytext));yylval.lex = strdup(yytext); return (IDENTIFIER);}

.                   erro(yytext, LEXEMANONRECONHECIDO); return(0);

%%


//Función que abre o ficheiro de lectura, se non se pode abrir sacamos un erro
void lerEntrada(char* entrada, int modo){
    yy_scan_string(entrada);
    if(entrada==NULL){
        printf("Erro ó ler a entrada\n");
        exit(1);
    }
    else if (modo){
        free(entrada);
    }
}

//Función que pecha o ficheiro de lectura
void liberarFlex(){
    yylex_destroy();
}