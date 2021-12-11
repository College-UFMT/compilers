/**
 * @file gen.c
 * @author kaio-nink & Ivairton M. Santos
 * @date Sat Dec 11 2021
 * @brief Modulo para definicao de constantes 
 * e estruturas de dados do Sistema Compilador de C Simplificado 
 *
 */
#ifndef _STRUCT_COMPILER_
#define _STRUCT_COMPILER_

// Definicao de constantes para todo o compilador
#define MAX_CHAR 32
#define MAX_TOKEN 32

#define true 1  //por conveniencia, para facilitar leitura de codigo
#define false 0 //por conveniencia, para facilitar leitura de codigo

// Definicao dos codigos
#define ENDTOKEN '\0'
#define ERROR -1
#define NUM 1
#define PLUS '+'
#define MINUS '-'
//Definicao de codigos para multiplicacao, divisao e parenteses
#define MULT '*'
#define DIV '/'
#define PAROPEN '('
#define PARCLOSE ')'

// Definicao da estrutura de dados 'token'
struct st_token {
    int tag;
    char lexema[MAX_CHAR];
};
typedef struct st_token type_token;

#endif //_STRUCT_COMPILER_