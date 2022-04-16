#include "AnaSintactico.h"
#include "TaboaSimbolos.h"
#include "lex.yy.h"

int main(){

    abrirFicheiro("concurrentSum.go"); //Abrimos o ficheiro
    inicializarTS(); //Inicializamos a táboa de símbolos
    imprimeTS(); //Imprimimos o contido da táboa de símbolos ó iniciar a execución
    analizarSintacticamente(); //Comezamos a análise sintáctica
    imprimeTS(); //Imprimimos o contido da táboa de símbolos ó finalizar a execución
    eliminarTS(); //Eliminamos a táboa de símbolos
    pecharFicheiro(); //Pechamos o ficheiro
}