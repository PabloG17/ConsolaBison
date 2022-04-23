%{
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"
void yyerror(char *s);

extern int yylex();
void yyerror(char *s);
int codErro=0;
%}

%union{
double val;
char *ptr;
char *lex;
}

%start input
%token <val> NUM
%token <lex> IDENTIFIER

%token END

%right '='
%left '+' '-'
%left '*' '/'
%right '^'

%type <val> expr
%type <lex> id

%%

input:	/* Baleiro */
	| input line
;

line:	'\n'
	| expr '\n'
	| id '\n'
;
expr:	NUM {$$ = $1;}
	| '-' expr {$$ = -$2;}
	| '(' expr ')' {$$ = $2; printf("%g\n", $$);}
	| expr '+' expr {$$ = $1 + $3; printf("%g\n", $$);}
	| expr '-' expr {$$ = $1 - $3; printf("%g\n", $$);}
	| expr '*' expr {$$ = $1 * $3; printf("%g\n", $$);}
	| expr '/' expr {$$ = $1 / $3; printf("%g\n", $$);}
	| expr '^' expr {$$ = pow($1, $3); printf("%g\n", $$);}
	| IDENTIFIER '=' expr {$$ = $3;modificaValorTS($1, $3, NULL);}
	| IDENTIFIER '(' expr ')' {$$ = executaFuncionTS($1, $3, &codErro); if(codErro==0) printf("%g\n", $$); else codErro=0;}
	| IDENTIFIER '(' expr ',' expr ')' {$$ = executaFuncion2TS($1, $3, $5, &codErro); if(codErro==0) printf("%g\n", $$); else codErro=0;}
	| IDENTIFIER '(' IDENTIFIER ')' {if(buscaTS($3)){$$ = executaFuncionTS($1, buscaValorTS($3), &codErro); if(codErro==0) printf("%g\n", $$); else codErro=0;}else{yyerror("Non se atopou a variable");}}
	| IDENTIFIER '(' IDENTIFIER ',' IDENTIFIER ')' {if(buscaTS($5) && buscaTS($3)){$$ = executaFuncion2TS($1, buscaValorTS($3), buscaValorTS($5), &codErro);if(codErro==0) printf("%g\n", $$); else codErro=0;}else{yyerror("Non se atopou a variable");}}
	| IDENTIFIER '(' expr ',' IDENTIFIER ')' {if(buscaTS($5)){$$ = executaFuncion2TS($1, $3, buscaValorTS($5), &codErro); if(codErro==0) printf("%g\n", $$); else codErro=0;}else{yyerror("Non se atopou a variable");}}
	| IDENTIFIER '(' IDENTIFIER ',' expr ')' {if(buscaTS($3)){$$ = executaFuncion2TS($1, buscaValorTS($3), $5, &codErro); if(codErro==0) printf("%g\n", $$); else codErro=0;}else{yyerror("Non se atopou a variable");}}
;
id:	IDENTIFIER {$$ = $1; if(buscaTS($1)){printf("%g\n", buscaValorTS($1));} else {printf("O elemento non está inicializado");}}
%%

void yyerror(char *s) {
	fprintf(stderr, "Error: %s\n", s);
}
