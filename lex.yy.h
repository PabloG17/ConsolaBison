#ifndef COMPILADORGO_LEX_YY_H
#define COMPILADORGO_LEX_YY_H


//Función que abre o ficheiro de lectura
void lerEntrada(char* entrada, int modo);

//Función que pecha o ficheiro de lectura
void liberarFlex();

//Función que devolve o lexema actual
extern int yylex (void);

#endif //COMPILADORGO_LEX_YY_H
