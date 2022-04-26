%{
#include "FuncionsBison.h"
#include <stdio.h>
#include "go.tab.h"
#include "TaboaSimbolos.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lex.yy.h"

#define NUMFICHEIROS 5

void yyerror(char *s);

extern int yylex();

void yyerror(char *s);
int codErro=0; //Variable usada para non mostrar a saída numérica por defecto (porque hai un erro ou porque se está executando unha función silenciosa)
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
%token  EQ
%token  GT
%token  LT
%token  NE


%token END

%right '='
%left '+' '-'
%left '*' '/'
%right '^'
%left '>' '<'

%type <val> expr
%type <val> id
%type <val> comparacion

%%

input:	/* Baleiro */
	| input line
;

line:	'\n'
	| expr '\n' {if(codErro==0 && echo==1)printf("%g\n", $1); else{codErro=0;}}
	| expr ';' '\n'
	| comparacion '\n' {if(codErro==0 && echo==1){if($1==1) printf("true\n"); else printf("false");} else{codErro=0;}}
        | comparacion ';' '\n'
;
expr:	NUM {$$ = $1;}
	| id {$$ = $1;}
	| '-' expr {$$ = -$2;}
	| '(' expr ')' {$$ = $2;}
	| expr '+' expr {$$ = $1 + $3;}
	| expr '-' expr {$$ = $1 - $3;}
	| expr '*' expr {$$ = $1 * $3;}
	| expr '/' expr {if($3!=0) $$ = $1 / $3; else{ printf("INDETERMINACIÓN: División por 0\n"); codErro=1;}}
	| expr '^' expr {$$ = pow($1, $3);}
	| IDENTIFIER '=' expr {$$ = $3;modificaValorTS($1, $3, NULL);}
	| IDENTIFIER '(' ')' {$$ = executaFuncion0TS($1, &codErro); codErro=1;}
	| IDENTIFIER '(' STRING ')' {$$ = executaFuncionIDTS($1, $3, &codErro); if($$==0) codErro=1; free($3);}
	| IDENTIFIER '(' expr ')' {$$ = executaFuncionTS($1, $3, &codErro);}
	| IDENTIFIER '(' expr ',' expr ')' {$$ = executaFuncion2TS($1, $3, $5, &codErro);}
;
id:	IDENTIFIER {if(buscaTS($1)){$<val>$ = buscaValorTS($1);} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}

comparacion: expr '>' expr {if($1 > $3) $$=1; else $$=0;}
	| expr '<' expr {if($1 < $3) $$=1; else $$=0;}
	| expr GT expr {if($1 >= $3) $$=1; else $$=0;}
	| expr LT expr {if($1 <= $3) $$=1; else $$=0;}
	| expr EQ expr {if($1 == $3) $$=1; else $$=0;}
	| expr NE expr {if($1 != $3) $$=1; else $$=0;}
	;
%%

//Función que imprime un erro da análise
void yyerror(char *s) {
	fprintf(stderr, "Error: %s\n", s);
}

//Función que devolve o estado do sistema
int verEstado(){
	return estado;
}

//Función que modifica o estado do sistema
void cambiarEstado(int i){
	estado = i;
	codErro=1;
}

//Función que realiza unha pseudoexecución do programa a partir dun ficheiro
void pseudoExecucion(char *entrada){
	lerEntrada(entrada, 0);
	yyparse();
}

//Función que cambia a saída da consola
void cambiarEcho(int i){
	echo = i;
}

//Función que establece un ficheiro como aberto no sistema para evitar chamadas en bucle
void establecerFicheiro(char *nomeFicheiro){
	int i; //Variable de iteración

	ficheiro[numFicheiro] = (char*)malloc(sizeof(char)*(strlen(nomeFicheiro)+1));
	strcpy(ficheiro[numFicheiro], nomeFicheiro);
	numFicheiro++;
	codErro=0; //Ó ler un novo ficheiro, o código de erro ponse a 0
}

//Función que comproba se un ficheiro está aberto ou non
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

//Función que pecha un ficheiro aberto no sistema
void liberarFicheiro(){
	free(ficheiro[numFicheiro]);
	ficheiro[numFicheiro]=NULL;
	codErro=1; //Ó rematar de ler un ficheiro, a variable ponse a 1 para non mostrar a saída numérica do comando load()
	numFicheiro=numFicheiro-1;
}

//Función que realiza a inicialización inicial do sistema
void inicializarSistema(){
	int i; //Variable de iteración

	ficheiro=(char**)malloc(NUMFICHEIROS*sizeof(char*));

	for(i=0; i<NUMFICHEIROS; i++){
		ficheiro[i]=NULL;
	}
}

//Función que libera a memoria reservada por Bison
void liberarBison(){
	int i; //Variable de iteración

	//Recorremos todos os ficheiros e liberamos a memoria reservada
	for(i=0; i<NUMFICHEIROS; i++){
		if(ficheiro[i]!=NULL){
			free(ficheiro[i]);
		}
	}

	free(ficheiro);

}