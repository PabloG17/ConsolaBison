#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "THash.h"

#define tamhash 128 //Número de entradas da táboa hash

//Cada un dos compoñentes da táboa hash
typedef struct celda{
    char *lexema;
    double valor;
    void *ptr;
    struct celda *seguinte;
}celda;

//Táboa hash
typedef struct taboaHash{
    struct celda *hash[tamhash];
} taboaHash;

//Función que inicializa unha celda
celda* inicializarCelda(){
    celda *c;
    c = (celda*)malloc(sizeof(celda));
    c->lexema = NULL;
    c->ptr = NULL;
    c->seguinte = NULL;
    return c;
}

//Función que libera a memoria unha celda
void destruirCelda(celda *c){
    free(c->lexema);
}

//Función que libera a memoria dunha táboa hash
void destruirHash(taboaHash *t){

    int i; //Variable de iteración
    struct celda *c; //Celda mediante a que iteraremos para borrar as listas
    struct celda *celdaDestruir; //Celda cuxa memoria se libera en cada iteración

    for(i=0; i<tamhash; i++){

        c = t->hash[i];
        while(c!=NULL){
            celdaDestruir=c;
            c=c->seguinte;
            if(celdaDestruir->lexema!=NULL)
                destruirCelda(celdaDestruir);
            free(celdaDestruir);
        }
    }
    free(t);
}

//Función que crea unha táboa hash
taboaHash* inicializarTaboa(){
    struct taboaHash *t;
    int i; //Variable de iteración

    t=(taboaHash*)malloc(sizeof(taboaHash));

    for(i=0; i<tamhash;i++){
        t->hash[i]=inicializarCelda();
    }

    return t;
}

//Función que deolve o código hash dunha función
int hash(char *lexema){

    int i; //Variable de iteración
    int valorHash=0; //Índice que ocuparía o lexema na táboa hash
    int tamanho=(int)strlen(lexema); //Tamaño da cadea


    for(i=0; i<tamanho; i++){
        valorHash+=(int)lexema[i];
    }

    return valorHash%tamhash;
}

//Función que devolve un se o elemento está na táboa hash e 0 en caso contrario
int busca(taboaHash *t, char *chave){

    int pos = hash(chave); //Calculamos o valor hash do lexema

    struct celda *celda = t->hash[pos];

    while(celda!=NULL && celda->lexema!=NULL){ //Iteramos polas celdas ata atopar o lexema que buscamos
        if(strcmp(celda->lexema, chave)==0){
            return 1;
        }
        else{
            celda = celda->seguinte;
        }
    }
    return 0;
}


//Función que devolve o valor numérico asociado ó lexema
double buscaValor(taboaHash *t, char *chave){

    int pos = hash(chave); //Calculamos o valor hash do lexema

    struct celda *celda = t->hash[pos];

    while(celda!=NULL && celda->lexema!=NULL){ //Iteramos polas celdas ata atopar o lexema que buscamos
        if(strcmp(celda->lexema, chave)==0){
            return celda->valor;
        }
        else{
            celda = celda->seguinte;
        }
    }
    return 0;
}

//Función que devolve o compoñente léxico asociado ó lexema
double modificaValor(taboaHash *t, char *chave, double valor, void *ptr){

    int pos = hash(chave); //Calculamos o valor hash do lexema

    struct celda *celda = t->hash[pos];

    while(celda!=NULL && celda->lexema!=NULL){ //Iteramos polas celdas ata atopar o lexema que buscamos
        if(strcmp(celda->lexema, chave)==0) {
            //Relízase unha comprobación de se estamos intentando modificar unha constante
            if (celda->ptr == NULL) {
                celda->valor = valor;
                celda->ptr = ptr;
            }
            return 0;
        }
        else{
            celda = celda->seguinte;
        }
    }
    insertarHash(t, chave, valor, ptr);
    return 0;
}

//Función que devolve a función asociada ó lexema
void * buscaFuncion(taboaHash *t, char *chave){

    int pos = hash(chave); //Calculamos o valor hash do lexema

    struct celda *celda = t->hash[pos];

    while(celda!=NULL && celda->lexema!=NULL){ //Iteramos polas celdas ata atopar o lexema que buscamos
        if(strcmp(celda->lexema, chave)==0){
            return celda->ptr;
        }
        else{
            celda = celda->seguinte;
        }
    }
    return 0;
}

//Función que inserta un lexema na táboa hash
void insertarHash (taboaHash *t, char* lexema, double valor, void *ptr){
    int pos; //Posición na que se vai insertar o elemento
    pos =hash(lexema); //Calculamos a posición da táboa na que se insertaría o elemento
    struct celda *celda = t->hash[pos]; //Creamos un punteiro á primeira celda da lista enlazada da posición hash
    struct celda *celdaInsertar; //Creamos a nova celda co novo elemento a insertar

    //Se a primeira celda está baleira insertamos aí o elemento
    if(celda->lexema==NULL){
        celda->lexema=(char*)malloc((strlen(lexema)+1)*sizeof(char));
        strcpy(celda->lexema, lexema);
        celda->valor=valor;
        if(ptr!=NULL) {
            celda->ptr = ptr;
        }
    }

    //Se a primeira celda non está baleira
    else{
        //Creamos a nova celda
        celdaInsertar = (struct celda*)malloc(sizeof(struct celda));
        celdaInsertar->lexema=(char*)malloc((strlen(lexema)+1)*sizeof(char));
        strcpy(celdaInsertar->lexema, lexema);
        celdaInsertar->seguinte=NULL;
        celdaInsertar->valor=valor;
        if(ptr!=NULL) {
            celdaInsertar->ptr = ptr;
        }

        //Cando atopemos o último elemento da lista enlazada insertamos a nova celda
        while(celda->seguinte!=NULL){
            celda = celda->seguinte;
        }
        celda->seguinte = celdaInsertar;
    }
}

//Función que imprime o contido dunha táboa hash
void imprimirTaboaHash(taboaHash *t){

    int i; //Variable de iteración
    struct celda *celda; //Celda mediante a que iteraremos para imprimir o contido

    for(i=0; i<tamhash; i++){
        celda=t->hash[i];
        //Se a celda está baleira, non a imprimimos
        if(celda->lexema!=NULL){
            printf("%i --> %s\n", i, celda->lexema);
            while(celda->seguinte!=NULL){
                celda = celda->seguinte;
                printf("\t--> %s\n", celda->lexema);
            }
        }
    }
}