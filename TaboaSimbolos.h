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

//Función que executa unha función alamacenada na táboa de símbolos sen argumentos
double executaFuncion0TS(char *chave, int* codErro);

//Función que executa unha función almacenada na táboa de símbolos
double executaFuncionTS(char *chave, double valor, int* codErro);

//Función que executa unha función almacenada na táboa de símbolos de dous argumentos
double executaFuncion2TS(char *chave, double valor, double valor2, int* codErro);

//Función que executa unha función almacenada na táboa de símbolos que ten como argumento un identificador
double executaFuncionIDTS(char *chave, char* valor, int* codErro);

//Función que imprime a táboa de símbolos
void imprimeTS();

//Función que devolve as variables almacenadas polo usuario na táboa de símbolos e os seus valores
void workspaceTS(double **val, char ***chaves);

//Función que devolve as variables almacenadas polo usuario na táboa de símbolos e os seus valores
void workspaceSVTS(char ***chaves);

//Función que devolve o número de variables definidas ata o momento
int numVariablesDefinidasTS();

//Función que libera unha determinada posición da táboa de símbolos
void buscaEDestrueTS(char *chave);

//Función que fai que unha variable da táboa de símbolos sexa constante no resto do programa
int facerConstanteTS(char *chave);

#endif //COMPILADORGO_TABOASIMBOLOS_H
