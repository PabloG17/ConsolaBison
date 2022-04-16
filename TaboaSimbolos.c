#include <stdio.h>
#include "TaboaSimbolos.h"
#include "Definicions.h"
#include "THash.h"

#define tamhash 1024 //Número de entradas da táboa hash
#define numIdentificadores 500 //Número identificador dos identificadores

//Cores para a impresión
#define AZUL            "\x1b[36m"
#define RESET           "\x1b[0m"

struct taboaHash *taboaSimbolos; //Declaramos a táboa de símbolos como unha táboa hash

//Inicializamos a táboa de símbolos
void inicializarTS(){

    //Creamos a táboa hash
    taboaSimbolos=inicializarTaboa();

    //Insertamos todas as palabras chave
    insertarHash(taboaSimbolos, "break", BREAK);
    insertarHash(taboaSimbolos, "case", CASE);
    insertarHash(taboaSimbolos, "chan", CHAN);
    insertarHash(taboaSimbolos, "const", CONST);
    insertarHash(taboaSimbolos, "continue", CONTINUE);
    insertarHash(taboaSimbolos, "default", DEFAULT);
    insertarHash(taboaSimbolos, "defer", DEFER);
    insertarHash(taboaSimbolos, "else", ELSE);
    insertarHash(taboaSimbolos, "fallthrough", FALLTHROUGH);
    insertarHash(taboaSimbolos, "for", FOR);
    insertarHash(taboaSimbolos, "func", FUNC);
    insertarHash(taboaSimbolos, "go", GO);
    insertarHash(taboaSimbolos, "goto", GOTO);
    insertarHash(taboaSimbolos, "if", IF);
    insertarHash(taboaSimbolos, "import", IMPORT);
    insertarHash(taboaSimbolos, "interface", INTERFACE);
    insertarHash(taboaSimbolos, "map", MAP);
    insertarHash(taboaSimbolos, "package", PACKAGE);
    insertarHash(taboaSimbolos, "range", RANGE);
    insertarHash(taboaSimbolos, "return", RETURN);
    insertarHash(taboaSimbolos, "select", SELECT);
    insertarHash(taboaSimbolos, "struct", STRUCT);
    insertarHash(taboaSimbolos, "switch", SWITCH);
    insertarHash(taboaSimbolos, "type", TYPE);
    insertarHash(taboaSimbolos, "var", VAR);


}

//Función que inserta un lexema na táboa de símbolos
int insertarTS(char *lexema){
    insertarHash(taboaSimbolos, lexema, numIdentificadores);
    return numIdentificadores;
}

//Función que elimina a táboa de símbolos
void eliminarTS(){
    destruirHash(taboaSimbolos);
}

//Función que busca un lexema na táboa de símbolos e devolve o compoñente léxico asociado
int buscarTS(char* chave){
    return busca(taboaSimbolos, chave);
}

//Función que imprime a táboa de símbolos
void imprimeTS(){
    printf(AZUL"-----------------------CONTIDO DA TABOA DE SÍMBOLOS-----------------------\n");
    imprimirTaboaHash(taboaSimbolos);
    printf("-------------------------------------------------------------------------\n"RESET);
}