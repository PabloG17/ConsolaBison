#include <stdio.h>
#include "stdlib.h"

#include "AnaSintactico.h"
#include "lex.yy.h"

//Función que analiza sintacticamente os elementos do sistema de entrada
void analizarSintacticamente(){

    struct lexema *lex; //Lexema que se vai imprimir
    int componhente; //Componhente léxico

    do{
        lex=seguinteComponhente();
        printf("< %s, %i >\n", lex->lexema, lex->componhente);
        componhente=lex->componhente;
        free(lex->lexema);
        free(lex);
    }
    //Pedimos compoñentes ata que nos chega o compoñente co identificador 10 que é o fin de ficheiro
    while(componhente!=10);
}