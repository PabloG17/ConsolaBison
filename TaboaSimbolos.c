#include <stdio.h>
#include "TaboaSimbolos.h"
#include "Definicions.h"
#include "THash.h"
#include "Funcions.h"
#include "XesErros.h"
#include <string.h>

#define tamhash 1024 //Número de entradas da táboa hash
#define numIdentificadores 500 //Número identificador dos identificadores

struct taboaHash *taboaSimbolos; //Declaramos a táboa de símbolos como unha táboa hash

//Inicializamos a táboa de símbolos
void inicializaTS(){
    int i;

    //Creamos a táboa hash
    taboaSimbolos=inicializarTaboa();

    //Insertamos as funcións iniciais
    for(i=0; i<FUNCIONS_EXPR; i++){
        insertarHash(taboaSimbolos, funcions_expr[i].nome, 0, funcions_expr[i].func);
    }

    for(i=0; i<FUNCIONS_ID; i++){
        insertarHash(taboaSimbolos, funcions_ID[i].nome, 0, funcions_ID[i].func);
    }

    insertarHash(taboaSimbolos, "pi", PI, (void*)2);
    insertarHash(taboaSimbolos, "e", E, (void*)2);

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

//Función que executa unha función almacenada na táboa de símbolos sen argumentos
double executaFuncion0TS(char *chave, int* codErro){
    void *ptr;
    int i=0; //Variable de iteración

    //Buscamos as funcións entre a lista e vemos se ten o número adecuado de argumentos
    for(i=0;i<FUNCIONS_EXPR; i++){
        if(strcmp(funcions_expr[i].nome, chave)==0){
            if(funcions_expr[i].args==0){
                //Se a función existe e os argumentos coinciden, invocámola
                ptr=buscaFuncionTS(chave);
                return ((double (*)())ptr)();
            }
            //En caso contrario, sacamos unha mensaxe de erro
            else{
                erro("A función á que se quere chamar ten 0 argumentos",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }

    for(i=0;i<FUNCIONS_ID; i++) {
        if (strcmp(funcions_ID[i].nome, chave) == 0) {
            erro(chave,FUNCIONID);
            *codErro=FUNCIONID;
            return 0;
        }
    }

    erro(chave, FUNCIONNONEXISTE);
    *codErro=FUNCIONNONEXISTE;
    return(0);
}

//Función que executa unha función almacenada na táboa de símbolos
double executaFuncionTS(char *chave, double valor, int* codErro){
    void *ptr;
    int i=0; //Variable de iteración

    //Buscamos as funcións entre a lista e vemos se ten o número adecuado de argumentos
    for(i=0;i<FUNCIONS_EXPR; i++){
        if(strcmp(funcions_expr[i].nome, chave)==0){
            if(funcions_expr[i].args==1){
                //Se a función existe e os argumentos coinciden, invocámola
                ptr=buscaFuncionTS(chave);
                return ((double (*)(double))ptr)(valor);
            }
                //En caso contrario, sacamos unha mensaxe de erro
            else{
                erro("A función á que se quere chamar ten 1 argumento",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }

    for(i=0;i<FUNCIONS_ID; i++) {
        if (strcmp(funcions_ID[i].nome, chave) == 0) {
            erro(chave,FUNCIONID);
            *codErro=FUNCIONID;
            return 0;
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

    //Buscamos as funcións entre a lista e vemos se ten o número adecuado de argumentos
    for(i=0;i<FUNCIONS_EXPR; i++){
        if(strcmp(funcions_expr[i].nome, chave)==0){
            if(funcions_expr[i].args==2){
                //Se a función existe e os argumentos coinciden, invocámola
                ptr=buscaFuncionTS(chave);
                return ((double (*)(double, double))ptr)(valor, valor2);
            }
                //En caso contrario, sacamos unha mensaxe de erro
            else{
                erro("A función á que se quere chamar ten 2 argumentos",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }

    for(i=0;i<FUNCIONS_ID; i++) {
        if (strcmp(funcions_ID[i].nome, chave) == 0) {
            erro(chave,FUNCIONID);
            *codErro=FUNCIONID;
            return 0;
        }
    }

    erro(chave, FUNCIONNONEXISTE);
    *codErro=FUNCIONNONEXISTE;
    return(0);
}

//Función que executa unha función almacenada na táboa de símbolos que ten como argumento un identificador
double executaFuncionIDTS(char *chave, char* valor, int* codErro){

    void *ptr;
    int i; //Variable de iteración

    //Buscamos as funcións entre a lista e vemos se ten o número adecuado de argumentos
    for(i=0;i<FUNCIONS_ID; i++){
        if(strcmp(funcions_ID[i].nome, chave)==0){
            if(funcions_ID[i].args==1){
                //Se a función existe e os argumentos coinciden, invocámola
                ptr=buscaFuncionTS(chave);
                return ((double (*)(char*))ptr)(valor);
            }
                //En caso contrario, sacamos unha mensaxe de erro
            else{
                erro("A función á que se quere chamar ten 1 argumento",NUMARGUMENTOSINVALIDO);
                *codErro=NUMARGUMENTOSINVALIDO;
                return(0);
            }
        }
    }

    for(i=0;i<FUNCIONEXPR; i++) {
        if (strcmp(funcions_expr[i].nome, chave) == 0) {
            erro(chave,FUNCIONEXPR);
            *codErro=FUNCIONEXPR;
            return 0;
        }
    }

    erro(chave, FUNCIONNONEXISTE);
    *codErro=FUNCIONNONEXISTE;
    return(0);
}

//Función que devolve as variables almacenadas polo usuario na táboa de símbolos e os seus valores
void workspaceTS(double **val, char ***chaves){
    return workspaceHash(taboaSimbolos,val, chaves);
}

//Función que devolve as variables almacenadas polo usuario na táboa de símbolos
void workspaceSVTS(char ***chaves){
    return workspaceHashSV(taboaSimbolos, chaves);
}

//Función que imprime a táboa de símbolos
void imprimeTS(){
    printf(AZUL"-----------------------CONTIDO DA TABOA DE SÍMBOLOS-----------------------\n");
    imprimirTaboaHash(taboaSimbolos);
    printf("-------------------------------------------------------------------------\n"RESET);
}

//Función que devolve o número de variables definidas ata o momento
int numVariablesDefinidasTS(){
    return numVariablesDefinidas();
}

//Función que libera unha determinada posición da táboa de símbolos
void buscaEDestrueTS(char *chave){
    buscaEDestrue(taboaSimbolos, chave);
}

//Función que fai que unha variable sexa constante no resto do programa
int facerConstanteTS(char *chave){
    return facerConstante(taboaSimbolos, chave);
}