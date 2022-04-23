#ifndef COMPILADORGO_TABOASIMBOLOS_H
#define COMPILADORGO_TABOASIMBOLOS_H

//Función que inicializa a táboa de símbolos
void inicializaTS();

//Función que elimina a táboa de símbolos
void eliminaTS();

//Función que devolve un se o elemento está na táboa hash e 0 en caso contrario
int buscaTS(char *chave);

//Función que busca un lexema na táboa de símbolos e devolve o valor asociado
double buscaValorTS(char* chave);

//Función que busca un lexema na táboa de símbolos e devolve a súa función asociada
void* buscaFuncionTS(char* chave);

//Función que busca un lexema na táboa de símbolos e modifica os seus valores
double modificaValorTS(char *chave, double valor, void *ptr);

//Función que executa unha función almacenada na táboa de símbolos
double executaFuncionTS(char *chave, double valor, int* codErro);

//Función que executa unha función almacenada na táboa de símbolos de dous argumentos
double executaFuncion2TS(char *chave, double valor, double valor2, int* codErro);

//Función que executa unha función almacenada na táboa de símbolos que ten como argumento un identificador
double executaFuncionIDTS(char *chave, char* valor);

//Función que imprime a táboa de símbolos
void imprimeTS();

#endif //COMPILADORGO_TABOASIMBOLOS_H
