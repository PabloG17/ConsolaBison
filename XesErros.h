#ifndef COMPILADORGO_XESERROS_H
#define COMPILADORGO_XESERROS_H

#define FICHEIRONONABERTO 00
#define LEXEMANONRECONHECIDO 01
#define NUMARGUMENTOSINVALIDO 02
#define FUNCIONNONEXISTE 03


//Función que informa dun erro por pantalla
void erro(char* info, int codigo);

#endif //COMPILADORGO_XESERROS_H
