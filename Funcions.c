#include <stdio.h>
#include "Funcions.h"
#include <stdlib.h>
#include <string.h>
#include "Definicions.h"
#include "lex.yy.h"
#include "TaboaSimbolos.h"

//Función que sirve para cargar as operacións dende un ficheiro externo
double load(char* nomeFicheiro){

    FILE *fp;
    char linha[256];
    char *token;

    //Eliminamos as comillas do nome do ficheiro
    nomeFicheiro = strtok(nomeFicheiro, "\"");
    fp = fopen(nomeFicheiro, "r");
    if(fp == NULL){
        printf("Erro ó abrir o ficheiro %s\n", nomeFicheiro);
    }
    else if(comprobarFicheiro(nomeFicheiro)){
        establecerFicheiro(nomeFicheiro);
        printf("\n"); //Escribimos un salto de linha para separar no caso de que se lean varios ficheiros de forma encadeada
        while(fgets(linha, sizeof(linha), fp)){
            printf("> %s", linha);
            strcat(linha, "\n"); //Engadimos un retorno de carro para asegurar que todas as liñas son válidas
            pseudoExecucion(linha);
        }
        printf("\nFicheiro %s lido con éxito\n", nomeFicheiro);
        liberarFicheiro();
        //Escribimos un salto de liña ó final para abrir unha nova liña na consola
        lerEntrada("\n");
    }
    else{
        printf("\nIntentouse facer unha lectura de ficheiros recursiva!\n");
    }
    return 0;
}

//Función que serve para imprimir todas as variables que están na memoria
double workspace(){

    int i; //Variable de iteración
    int num=numVariablesDefinidasTS(); //Número de variables definidas
    double **valores;
    char ***chaves;

    if(num!=0) {

        //Reservamos memoria para as variables e os seus valores
        valores = (double **) malloc(num * sizeof(double *));
        chaves = (char ***) malloc(num * sizeof(char **));

        //Calculamos o número de variables a imprimir e recollémolas
        workspaceTS(valores, chaves);

        //Imprimimos as variables
        for (i = 0; i < num; i++) {
            printf("%s = %g\n", *chaves[i], *valores[i]);
        }

        //Liberamos a memoria reservada
        free(valores);
        free(chaves);
    }
    else{
        printf("Non hai variables definidas\n");
    }

}

//Función que serve para eliminar as variables da memoria
double clear(){

    int i; //Variable de iteración
    int num=numVariablesDefinidasTS(); //Número de variables definidas
    char ***chaves;

    if(num!=0) {

        chaves = (char ***) malloc(num * sizeof(char **));

        //Calculamos o número de variables a imprimir e recollémolas
        workspaceSVTS(chaves);

        //Imprimimos as variables
        for (i = 0; i < num; i++) {
            buscaEDestrueTS(*chaves[i]);
        }

        //Liberamos a memoria reservada
        free(chaves);
    }
    else{
        printf("Non hai variables definidas\n");
    }


}

//Función que serve para cambiar o estado do sistema e pechalo
double sair(){
    cambiarEstado(-1);
}

//Función que imprime mensaxes de axuda
double help(){
    printf(AZUL"***** TERMINAL DE OPERACIÓNS *****\n"RESET);
    printf("Este programa permite realizar operacións matemáticas e calcular a través de variables definidas\n");
    printf("Tamén se permite cargar un ficheiro de texto que conteña as operacións matemáticas que se desexan realizar\n");
    printf("Existen algunhas funcións básicas como sin, cos, exp, log, etc. que xa veñen incorporadas por defecto\n");
    printf("Ademais tamén existen unha serie de comandos que poden ser de axuda:\n");
    printf("\n");
    printf("* Para cargar un ficheiro de texto, escribe load (\"<nome do ficheiro>\")\n");
    printf("* Para imprimir as variables definidas, escribe workspace()\n");
    printf("* Para limpar as variables definidas, escribe clear()\n");
    printf("* Para sair, escribe exit()\n");
    printf("* Para ver a axuda, escribe help()\n");
    printf("\n");

}

double print(double num){
    return num;
}

double saida(char* str){
    if(str!=NULL){
        if(strcmp(str,"\"on\"")==0){
            cambiarEcho(1);
        }
        else if(strcmp(str,"\"off\"")==0){
            cambiarEcho(0);
        }
        else{
            printf("Esa opción non existe. Introduce \"on\" ou \"off\"\n");
        }
    }
}
