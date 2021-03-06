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
%left  EQ
%left  GT
%left  LT
%left  NE
%left	MAI
%left	MEI
%left	AND
%left	OR
%left	INCR
%left	DECR

%token END

%right '='
%left '+' '-'
%left '*' '/'
%right '^'
%left '>' '<'

%type <val> expr
%type <val> id
%type <val> booleano

%%

input:	/* Baleiro */
	| input line
;

line:	'\n'
	| expr '\n' {if(codErro==0 && echo==1)printf("%g\n", $1); else{codErro=0;}}
	| expr ';' '\n'
	| booleano '\n' {if(codErro==0 && echo==1){if($1==1) printf("true\n"); else printf("false");} else{codErro=0;}}
        | booleano ';' '\n'
        | STRING '\n' {if(codErro==0 && echo==1) printf("%s\n", $1); else{codErro=0;}}
	| STRING ';' '\n'
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
	| IDENTIFIER MAI expr {if(buscaTS($1)){$$ = modificaValorTS($1, buscaValorTS($1)+$3, NULL);} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}
	| IDENTIFIER MEI expr {if(buscaTS($1)){$$ = modificaValorTS($1, buscaValorTS($1)-$3, NULL);} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}
	| IDENTIFIER INCR {if(buscaTS($1)){$$ = modificaValorTS($1, buscaValorTS($1)+1, NULL);} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}
	| IDENTIFIER DECR {if(buscaTS($1)){$$ = modificaValorTS($1, buscaValorTS($1)-1, NULL);} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}
	| IDENTIFIER '=' expr {$$ = $3;if(modificaValorTS($1, $3, NULL)==-1){printf("As constantes e as funcións non se poden modificar!");codErro=1;} free($1);}
	| IDENTIFIER '(' ')' {$$ = executaFuncion0TS($1, &codErro); codErro=1;}
	| IDENTIFIER '(' STRING ')' {$$ = executaFuncionIDTS($1, $3, &codErro);codErro=1; free($3); free($1);}
	| IDENTIFIER '(' expr ')' {$$ = executaFuncionTS($1, $3, &codErro); free($1);}
	| IDENTIFIER '(' expr ',' expr ')' {$$ = executaFuncion2TS($1, $3, $5, &codErro); free($1);}
;
id:	IDENTIFIER {int a=buscaTS($1); if(a==2){$<val>$ = buscaValorTS($1);} else if(a==1){printf("Este elemento é unha función"); codErro=1;} else {printf("O elemento non está inicializado\n"); codErro=1; free($1);}}

booleano: expr '>' expr {if($1 > $3) $$=1; else $$=0;}
	| expr '<' expr {if($1 < $3) $$=1; else $$=0;}
	| expr GT expr {if($1 >= $3) $$=1; else $$=0;}
	| expr LT expr {if($1 <= $3) $$=1; else $$=0;}
	| expr EQ expr {if($1 == $3) $$=1; else $$=0;}
	| expr NE expr {if($1 != $3) $$=1; else $$=0;}
	| expr AND expr {if($1 && $3) $$=1; else $$=0;}
	| expr OR expr {if($1 || $3) $$=1; else $$=0;}
	| '!' expr {if(!$2) $$=1; else $$=0;}
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