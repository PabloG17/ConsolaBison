/* Incluímos as librerías necesarias */

%{
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include "Definicions.h"
#include "XesErros.h"
%}

%option noyywrap

/* Definimos as expresións regulares */
NEWLINE           \n
TAB               \t
SPACE             [ ]
RETURN            \r
LINE_COMMENT      \/\/.*
BLOCK_COMMENT     \/\*(.|\n)*?\*\/

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
ASSIGN            =
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
ASSINGMENT        <-
COLON             :
TILDE             ~
THREE_DOTS        \.\.\.

HEX_DIGITS        {HEX_DIGIT}(_?{HEX_DIGIT})*
OCTAL_DIGITS      {OCTAL_DIGIT}(_?{OCTAL_DIGIT})*
BINARY_DIGITS     {BINARY_DIGIT}(_?{BINARY_DIGIT})*
DECIMAL_DIGITS    {DECIMAL_DIGIT}(_?{DECIMAL_DIGIT})*

HEX_LITERAL       0[Xx]_?{HEX_DIGITS}
OCTAL_LITERAL     0[Oo]?_?{OCTAL_DIGITS}?
BINARY_LITERAL    0[Bb]_?{BINARY_DIGITS}
DECIMAL_LITERAL   0|[1-9]_?{DECIMAL_DIGITS}?
INT_LITERAL       {HEX_LITERAL}|{OCTAL_LITERAL}|{BINARY_LITERAL}|{DECIMAL_LITERAL}

HEX_EXPONENT      [Pp][+-]?|{DECIMAL_DIGITS}+
HEX_MANTISSA      (_|{HEX_DIGITS}+)|(\.{HEX_DIGITS}+)|({HEX_DIGITS}+\.{HEX_DIGITS}+)
HEX_FLOAT_LITERAL 0[xX]{HEX_MANTISSA}{HEX_EXPONENT}
DECIMAL_EXPONENT  [Ee][+-]?{DECIMAL_DIGITS}
DECIMAL_FLOAT_LITERAL ({DECIMAL_DIGITS}\.{DECIMAL_DIGITS}?{DECIMAL_EXPONENT}?)|({DECIMAL_DIGITS}{DECIMAL_EXPONENT})|(\.{DECIMAL_DIGITS}{DECIMAL_EXPONENT}?)
FLOAT_LITERAL     {HEX_FLOAT_LITERAL}|{DECIMAL_FLOAT_LITERAL}

IMAGINARY_LITERAL ({DECIMAL_DIGITS}|{INT_LITERAL}|{FLOAT_LITERAL})i

RAW_STRING_LITERAL `(_|.)*`
INTERPRETED_STRING_LITERAL \"(_|.)*\"
STRING_LITERAL     {RAW_STRING_LITERAL}|{INTERPRETED_STRING_LITERAL}


/* Definimos as regras devolvendo o valor correspondente a cada expresión. Os valores que devolven 0 son ignorados
e os valores que non se enmarcan en ningunha destas expresións son tratados como erros. */

%%

{PLUS}              return(31);
{MINUS}             return(32);
{MULTIPLY}          return(33);
{DIVIDE}            return(34);
{MODULO}            return(35);
{AND}               return(36);
{OR}                return(37);
{XOR}               return(38);
{LEFT_SHIFT}        return(39);
{RIGHT_SHIFT}       return(40);
{AND_XOR}           return(41);
{INCREMENT_EQUAL}   return(42);
{DECREMENT_EQUAL}   return(43);
{MULTIPLY_EQUAL}    return(44);
{DIVIDE_EQUAL}      return(45);
{MODULO_EQUAL}      return(46);
{AND_EQUAL}         return(47);
{OR_EQUAL}          return(48);
{XOR_EQUAL}         return(49);
{LEFT_SHIFT_EQUAL}  return(50);
{RIGHT_SHIFT_EQUAL} return(51);
{AND_XOR_EQUAL}     return(52);
{AND_OP}            return(53);
{OR_OP}             return(54);
{ASSINGMENT}        return(55);
{INCREMENT}         return(56);
{DECREMENT}         return(57);
{EQUAL}             return(58);
{LESS_THAN}         return(59);
{GREATER_THAN}      return(60);
{ASSIGN}            return(61);
{NOT}               return(62);
{TILDE}             return(63);
{NOT_EQUAL}         return(64);
{LESS_THAN_EQUAL}   return(65);
{GREATER_THAN_EQUAL}   return(66);
{DEFINITION}        return(67);
{THREE_DOTS}        return(68);
{OPEN_PAREN}        return(69);
{CLOSE_PAREN}       return(70);
{OPEN_BRACKET}      return(71);
{CLOSE_BRACKET}     return(72);
{OPEN_BRACE}        return(73);
{CLOSE_BRACE}       return(74);
{COMMA}             return(75);
{SEMICOLON}         return(76);
{DOT}               return(77);
{COLON}             return(78);

{NEWLINE}           return(0);
{TAB}               return(0);
{SPACE}             return(0);
{RETURN}            return(0);
{LINE_COMMENT}      return(0);
{BLOCK_COMMENT}      return(0);

{STRING_LITERAL}    return(STRING);
{INT_LITERAL}       return(INTEGER);
{FLOAT_LITERAL}     return(FLOAT);
{IMAGINARY_LITERAL} return(IMAGINARY);
{IDENTIFIER}        return(IDENTIFIER);

.                   erro(yytext, LEXEMANONRECONHECIDO); return(0);

<<EOF>>             yytext="$"; return(10);

%%


//Función que abre o ficheiro de lectura, se non se pode abrir sacamos un erro
void lerEntrada(char* entrada){
    yy_scan_string(entrada);
    if(entrada==NULL){
        printf("Erro ó ler a entrada\n");
        exit(1);
    }
}

//Función que pecha o ficheiro de lectura
void pecharFicheiro(){
    yylex_destroy();
}

//Función que devolve o seguinte compoñente léxico que sexa reelevante
lexema* seguinteComponhente(){

    int comp;
    int busc;
    lexema *lex=NULL;

    do{
        //Obtemos o identificador relativo á cadea identificada
        comp=yylex();

        if(comp!=0){
            lex = (lexema *) malloc(sizeof(lexema));
            lex->lexema = strdup(yytext);
            lex->lexema[strlen(yytext)]='\0';
            lex->componhente = comp;
            //Se o valor é 500, estamos ante un identificador
            if(comp==500){
                //Buscamos o lexema na táboa de símbolos
                busc = buscarTS(lex->lexema);
                //Se non se atopou o lexema, insértase e engádese o seu compoñente léxico
                if (busc == 0) {
                    lex->componhente = insertarTS(lex->lexema);
                }
                else{
                    lex->componhente = busc;
                }
            }
        }
    }

    while(comp==0);

    return lex;
}