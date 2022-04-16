#ifndef COMPILADORGO_THASH_H
#define COMPILADORGO_THASH_H

struct celda;
struct taboaHash;

//Función que inicializa unha táboa hash
struct taboaHash* inicializarTaboa();

//Función que devolve o valor hash dun lexema
int hash(char *lexema);

//Función que busca unha chave na táboa hash
int busca(struct taboaHash *t, char *chave);

//Función que inserta un valor na táboa hash
void insertarHash (struct taboaHash *t, char* lexema, int componhente);

//Función que imprime o contido dunha táboa hash
void imprimirTaboaHash(struct taboaHash *t);

//Función que destrue unha táboa hash
void destruirHash(struct taboaHash *t);

#endif //COMPILADORGO_THASH_H
