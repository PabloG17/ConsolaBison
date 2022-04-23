#include <stdio.h>
#include "TaboaSimbolos.h"
#include "Definicions.h"
#include "THash.h"
#include "Funcions.h"
#include "XesErros.h"
#include <string.h>

#define tamhash 1024 //Número de entradas da táboa hash
#define numIdentificadores 500 //Número identificador dos identificadores

//Cores para a impresión
#define AZUL            "\x1b[36m"
#define RESET           "\x1b[0m"

struct taboaHash *taboaSimbolos; //Declaramos a táboa de símbolos como unha táboa hash

//Inicializamos a táboa de símbolos
void inicializaTS(){
    int i;

    //Creamos a táboa hash
    taboaSimbolos=inicializarTaboa();

    //Insertamos as funcións iniciais
    for(i=0; i<FUNCIONS; i++){
        insertarHash(taboaSimbolos, funcions[i].nome, 0, funcions[i].func);
    }
    insertarHash(taboaSimbolos, "PI", PI, (void*)2);
    insertarHash(taboaSimbolos, "E", E, (void*)2);

    //Insertamos todas as palabras chave
    /*
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

    */


}


//Función que elimina a táboa de símbolos
void eliminaTS(){
    destruirHash(taboaSimbolos);
}

int buscaTS(char *chave){
    return busca(taboaSimbolos, chave);
}

//Función que busca un lexema na táboa de símbolos e devolve o valor asociado
double buscaValorTS(char* chave){
    return buscaValor(taboaSimbolos, chave);
}

//Función que busca un lexema na táboa de símbolos e devolve o compoñente léxico asociado
void* buscaFuncionTS(char* chave){
    return buscaFuncion(taboaSimbolos, chave);
}

//Función que busca un lexema na táboa de símbolos e modifica os seus valores
double modificaValorTS(char *chave, double valor, void *ptr){
    return modificaValor(taboaSimbolos, chave, valor, ptr);
}

//Función que executa unha función almacenada na táboa de símbolos
double executaFuncionTS(char *chave, double valor, int* codErro){
    void *ptr;
    int i=0; //Variable de iteración

    for(i=0;i<FUNCIONS; i++){
        if(strcmp(funcions[i].nome, chave)==0){
            if(funcions[i].args==1){
                ptr=buscaFuncionTS(chave);
                return ((double (*)(double))ptr)(valor);
            }
            else{
                erro("A función á que se quere chamar ten 2 argumentos",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }
    erro(chave, FUNCIONNONEXISTE);
    *codErro=FUNCIONNONEXISTE;
    return(0);
}

//Función que executa unha función almacenada na táboa de símbolos de dous argumentos
double executaFuncion2TS(char *chave, double valor, double valor2, int* codErro){
    void *ptr;
    int i; //Variable de iteración

    for(i=0;i<FUNCIONS; i++){
        if(strcmp(funcions[i].nome, chave)==0){
            if(funcions[i].args==2){
                ptr=buscaFuncionTS(chave);
                return ((double (*)(double, double))ptr)(valor, valor2);
            }
            else{
                erro("A función á que se quere chamar ten 1 argumento",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }
    erro(chave, FUNCIONNONEXISTE);
    *codErro=FUNCIONNONEXISTE;
    return(0);
}

//Función que executa unha función almacenada na táboa de símbolos que ten como argumento un identificador
double executaFuncionIDTS(char *chave, char* valor){
    void *ptr;
    ptr=buscaFuncionTS(chave);
    return ((double (*)(char*))ptr)(valor);
}

//Función que imprime a táboa de símbolos
void imprimeTS(){
    printf(AZUL"-----------------------CONTIDO DA TABOA DE SÍMBOLOS-----------------------\n");
    imprimirTaboaHash(taboaSimbolos);
    printf("-------------------------------------------------------------------------\n"RESET);
}