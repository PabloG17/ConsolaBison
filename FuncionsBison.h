#ifndef COMPILADORGOV2_FUNCIONSBISON_H
#define COMPILADORGOV2_FUNCIONSBISON_H

//Función que permite ver o estado no que se atopa a execución
int verEstado();

//Función que permite modificar o estado da execución
void cambiarEstado(int i);

//Función que realiza unha execución do programa a partir dunha entrada dada
void pseudoExecucion(char* entrada);

//Función que acmbia o estado echo da execución
void cambiarEcho(int i);

//Función que establece o nome do ficheiro que se está lendo
void establecerFicheiro(char *nomeFicheiro);

//Ficheiro que comproba o nome do fichero que se está lendo coa finalidade de evitar chamadas recursivas
int comprobarFicheiro(char *nomeFicheiro);

//Función que indica que se deixou de ler o ficheiro
void liberarFicheiro();

//Función que inicializa o sistema de lectura
void inicializarSistema();

//Función que libera a memoria reservada por Bison
void liberarBison();

#endif //COMPILADORGOV2_FUNCIONSBISON_H
