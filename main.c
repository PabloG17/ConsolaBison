#include "go.tab.h"
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRADA 128

char * lerConsola(){
    char * entrada = (char *) malloc(MAX_ENTRADA * sizeof(char));
    printf("\n> ");
    //Leer linea completa de la consola
    fgets(entrada, MAX_ENTRADA, stdin);
    return entrada;
}

int main(){

    char* entrada;

    inicializaTS(); //Inicializamos a táboa de símbolos
    //imprimeTS(); //Imprimimos o contido da táboa de símbolos ó iniciar a execución
    do {
        entrada=lerConsola();
        lerEntrada(entrada); //Abrimos a entrada
        yyparse(); //Comezamos a análise sintáctica
    }
    while(strcmp(entrada, ";")!=0);
    //imprimeTS(); //Imprimimos o contido da táboa de símbolos ó finalizar a execución
    eliminaTS(); //Eliminamos a táboa de símbolos
    pecharFicheiro(); //Pechamos o ficheiro
}

