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
void abrirFicheiro(char* nomeFicheiro);

//Función que pecha o ficheiro de lectura
void pecharFicheiro();

#endif //COMPILADORGO_LEX_YY_H
