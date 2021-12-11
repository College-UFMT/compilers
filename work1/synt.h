/**
 * @file gen.c
 * @author kaio-nink & Ivairton M. Santos
 * @date Sat Dec 11 2021
 * @brief Modulo do analisador sintatico
 *
 */

#ifndef _SYNT_H_
#define _SYNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"
#include "lex.h"
#include "gen.h"

// Variaveis globais
type_token *lookahead;

// Prototipos
int digit();
int match(int token_tag);

// Prototipos da gramatica
int E();
int ER();
int T();
int TR();
int F(); 

int main();

#endif //_SYNT_H_