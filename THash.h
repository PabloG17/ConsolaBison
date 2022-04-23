#ifndef COMPILADORGO_THASH_H
#define COMPILADORGO_THASH_H

struct celda;
struct taboaHash;

//Función que inicializa unha táboa hash
struct taboaHash* inicializarTaboa();

//Función que devolve o valor hash dun lexema
int hash(char *lexema);

//Función que busca unha chave na táboa hash
double buscaValor(struct taboaHash *t, char *chave);

//Función que modifica un valor almacenado na táboa hash ou se non existe insértao
double modificaValor(struct taboaHash *t, char *chave, double valor, void *ptr);

//Función que devolve un se o elemento está na táboa hash e 0 en caso contrario
int busca(struct taboaHash *t, char *chave);

//Función que devolve a función asociada a un lexema
void * buscaFuncion(struct taboaHash *t, char *chave);

//Función que inserta un valor na táboa hash
void insertarHash (struct taboaHash *t, char* lexema, double componhente, void *ptr);

//Función que imprime o contido dunha táboa hash
void imprimirTaboaHash(struct taboaHash *t);

//Función que destrue unha táboa hash
void destruirHash(struct taboaHash *t);

#endif //COMPILADORGO_THASH_H
