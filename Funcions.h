#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lex.yy.h"
#include "go.tab.h"

#define FUNCIONS 16

typedef struct {
    char *nome;
    double (*func)();
    int args;
} Funcion;

double load(char* nomeFicheiro){

    FILE *fp;
    char linha[256];
    fp = fopen(nomeFicheiro, "r");
    if(fp == NULL){
        printf("Erro ó abrir o ficheiro\n");
    }
    else{
        while(fgets(linha, sizeof(linha), fp)){
            printf("%s", linha);
        }
    }
    return 0;
}


Funcion funcions[]={
        "sin", sin, 1,
        "cos", cos, 1,
        "tan", tan, 1,
        "log", log, 1,
        "exp", exp, 1,
        "acos", acos, 1,
        "asin", asin, 1,
        "atan", atan, 1,
        "sqrt", sqrt, 1,
        "fabs", fabs, 1,
        "floor", floor, 1,
        "ceil", ceil, 1,
        "round", round, 1,
        "trunc", trunc, 1,
        "load", load, 1,
        "pow", pow , 2
};