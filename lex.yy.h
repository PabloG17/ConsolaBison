//Estructura dun lexema
typedef struct lexema{
    char* lexema;
    int componhente;
}lexema;

#ifndef COMPILADORGO_LEX_YY_H
#define COMPILADORGO_LEX_YY_H

//Función que devolve o seguinte compoñente léxico que sexa reelevante
lexema* seguinteComponhente();

//Función que abre o ficheiro de lectura
void lerEntrada(char* entrada);

//Función que pecha o ficheiro de lectura
void pecharFicheiro();

//Función que devolve o lexema actual
extern int yylex (void);

#endif //COMPILADORGO_LEX_YY_H
