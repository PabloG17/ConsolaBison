#include "go.tab.h"
#include "TaboaSimbolos.h"
#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>
#include "Funcions.h"

#define MAX_ENTRADA 128

char * lerConsola(){
    char * entrada = (char *) malloc(MAX_ENTRADA * sizeof(char));
    printf("\n> ");
    //Leer linea completa de la consola
    fgets(entrada, MAX_ENTRADA, stdin);
    return entrada;
}

int main(int argc, char **argv){

    char* entrada;

    inicializaTS(); //Inicializamos a táboa de símbolos
    inicializarSistema(); //Inicializamos o sistema de lectura
    //imprimeTS(); //Imprimimos o contido da táboa de símbolos ó iniciar a execución

    if(argc > 1) {
        load(argv[1]);
    }
    do {
        entrada = lerConsola();
        lerEntrada(entrada); //Abrimos a entrada
        yyparse(); //Comezamos a análise sintáctica
    } while (verEstado() == 0);

    //imprimeTS(); //Imprimimos o contido da táboa de símbolos ó finalizar a execución
    eliminaTS(); //Eliminamos a táboa de símbolos
    pecharFicheiro(); //Pechamos o ficheiro
}

