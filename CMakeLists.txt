cmake_minimum_required(VERSION 3.19)
project(compiladorGov2 C)

set(CMAKE_C_STANDARD 99)

add_executable(compiladorGov2 main.c Definicions.h lex.yy.c lex.yy.h TaboaSimbolos.c TaboaSimbolos.h THash.c THash.h XesErros.c XesErros.h go.tab.c go.tab.h Funcions.c Funcions.h FuncionsBison.h)
target_link_libraries(compiladorGov2 m)