#ifndef COMPILADORGO_TABOASIMBOLOS_H
#define COMPILADORGO_TABOASIMBOLOS_H

//Función que inicializa a táboa de símbolos
void inicializarTS();

//Función que inserta un elemento na táboa de símbolos
int insertarTS(char *lexema);

//Función que elimina a táboa de símbolos
void eliminarTS();

//Función que busca un lexema na táboa de símbolos
int buscarTS(char* chave);

//Función que imprime a táboa de símbolos
void imprimeTS();

#endif //COMPILADORGO_TABOASIMBOLOS_H
