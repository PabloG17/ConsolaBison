#include <stdio.h>
#include <stdlib.h>
#include "XesErros.h"
#include "Definicions.h"

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
    if(codigo==FUNCIONID){
        printf(VERMELLO"\nA seguinte función é de tipo ID e polo tanto non se pode invocar con números ou variables (faltan as comillas?): %s\n" RESET, info);
    }
    if(codigo==FUNCIONEXPR){
        printf(VERMELLO"\nA seguinte función  é de tipo EXPRESION e polo tanto non se pode invocar cunha cadea: %s\n" RESET, info);
    }
}