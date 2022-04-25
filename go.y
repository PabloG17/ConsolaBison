%{
#include <stdio.h>
#include "lex.yy.h"
#include "TaboaSimbolos.h"
#include <ctype.h>
#include <stdlib.h>

#define NUMFICHEIROS 5

void yyerror(char *s);

extern int yylex();
void yyerror(char *s);
int codErro=0;
int estado=0;
int echo=1;
int numFicheiro=0;
char *linha;
char** ficheiro;
%}

%union{
double val;
char *ptr;
char *lex;
}

%start input
%token <val> NUM
%token <lex> IDENTIFIER
%token <lex> STRING

%token END

%right '='
%left '+' '-'
%left '*' '/'
%right '^'

%type <val> expr
%type <val> id

%%

input:	/* Baleiro */
	| input line
;

line:	'\n'
	| expr '\n' {if(codErro==0 && echo==1) printf("%g\n", $1); else if (numFicheiro==0) codErro=0;}
	| expr ';' '\n'
;
expr:	NUM {$$ = $1;}
	| id {$$ = $1;}
	| '-' expr {$$ = -$2;}
	| '(' expr ')' {$$ = $2;}
	| expr '+' expr {$$ = $1 + $3;}
	| expr '-' expr {$$ = $1 - $3;}
	| expr '*' expr {$$ = $1 * $3;}
	| expr '/' expr {$$ = $1 / $3;}
	| expr '^' expr {$$ = pow($1, $3);}
	| IDENTIFIER '=' expr {$$ = $3;modificaValorTS($1, $3, NULL);}
	| IDENTIFIER '(' ')' {$$ = executaFuncion0TS($1, &codErro);}
	| IDENTIFIER '(' STRING ')' {$$ = executaFuncionIDTS($1, $3, &codErro);}
	| IDENTIFIER '(' expr ')' {$$ = executaFuncionTS($1, $3, &codErro);}
	| IDENTIFIER '(' expr ',' expr ')' {$$ = executaFuncion2TS($1, $3, $5, &codErro);}
;
id:	IDENTIFIER {if(buscaTS($1)){$$ = buscaValorTS($1);} else {printf("O elemento non está inicializado"); codErro=1;}}
%%

void yyerror(char *s) {
	fprintf(stderr, "Error: %s\n", s);
}

int verEstado(){
	return estado;
}

void cambiarEstado(int i){
	estado = i;
}

void pseudoExecucion(char *entrada){
	lerEntrada(entrada);
	yyparse();
}

void cambiarEcho(int i){
	echo = i;
}

void establecerFicheiro(char *nomeFicheiro){
	int i; //Variable de iteración

	ficheiro[numFicheiro] = (char*)malloc(sizeof(char)*(strlen(nomeFicheiro)+1));
	strcpy(ficheiro[numFicheiro], nomeFicheiro);
	numFicheiro++;
}

int comprobarFicheiro(char *nomeFicheiro){
	int i; //Variable de iteración

	if(numFicheiro== NUMFICHEIROS){
		printf("Número máximo de ficheiros excedido\n");
		return 1;
	}

	for(i=0; i<NUMFICHEIROS; i++){
		if(ficheiro[i]!=NULL && strcmp(ficheiro[i], nomeFicheiro)==0){
			return 0;
		}
	}
	return 1;
}

void liberarFicheiro(){
	numFicheiro=numFicheiro-1%5;
	free(ficheiro[numFicheiro]);
	ficheiro[numFicheiro]==NULL;
}

void inicializarSistema(){
	int i; //Variable de iteración

	ficheiro=(char**)malloc(NUMFICHEIROS*sizeof(char*));

	for(i=0; i<NUMFICHEIROS; i++){
		ficheiro[i]=NULL;
	}
}