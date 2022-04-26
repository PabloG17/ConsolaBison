#ifndef COMPILADORGO_FUNCIONS_H
#define COMPILADORGO_FUNCIONS_H

#include <math.h>

#define FUNCIONS 22

typedef struct {
    char *nome;
    double (*func)();
    int args;
} Funcion;

//Función que sirve para cargar as operacións dende un ficheiro externo
double load(char* nomeFicheiro);

//Función que serve para imprimir todas as variables que están na memoria
double workspace();

//Función que serve para eliminar as variables da memoria
double clear();

//Función que serve para cambiar o estado do sistema e pechalo
double sair();

//Función que imprime mensaxes de axuda
double help();

double print(double num);

//Función que serve para cambiar o estado do sistema e pechalo
double saida(char* str);

static Funcion funcions[]={
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
        "pow", pow , 2,
        "workspace", workspace, 0,
        "clear", clear, 0,
        "exit", sair, 0,
        "help", help, 0,
        "print", print, 1,
        "echo", saida, 1
};

#endif //COMPILADORGO_FUNCIONS_H