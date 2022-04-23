#include <stdio.h>
#include <stdlib.h>
#include "XesErros.h"

//Cores para a impresión
#define VERMELLO        "\x1b[31m"
#define RESET           "\x1b[0m"

//Función que informa dun erro por pantalla
void erro(char* info, int codigo){

    if(codigo==FICHEIRONONABERTO){
        printf(VERMELLO"\nNon se deu aberto o ficheiro %s\n" RESET, info);
        exit(-1);
    }
    if(codigo==LEXEMANONRECONHECIDO){
        printf(VERMELLO"\nNon se reconheceu o lexema %s\n" RESET, info);
    }
    if(codigo==NUMARGUMENTOSINVALIDO){
        printf(VERMELLO"\nO número de argumentos é incorrecto: %s\n" RESET, info);
    }
    if(codigo==FUNCIONNONEXISTE){
        printf(VERMELLO"\nA seguinte función non existe: %s\n" RESET, info);
    }
}