/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.1
 * @date 2021-11-24
 * 
 */

// Inclusao do cabecalho
#include "synt.h"

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 * 
 * @param token_tag (int) codigo do token a ser verificado 
 * @return int true/false
 */
int match(int token_tag) {
    if ( lookahead->tag == token_tag ) {
        lookahead = getToken(); //Pega o proximo token por meio do lexico
        return true;
    }
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: LIST
 * 
 * @return int true/false
 */
int list() {
    if ( digit() && listR() ) 
        return true;
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: LIST_RECURSIVO
 * 
 * @return int true/false
 */
int listR() {
    int test1, test2;
    //Verifica ocorrencia de terminal '+'
    if ( lookahead->tag == PLUS ) {
        test1 = match(PLUS);
        test2 = digit();
        genAdd(); //Geracao de codigo por meio de funcao do GERADOR
        if (test1 && test2)
            return listR();
        return false;
    } //Verifica ocorrencia de terminal '-' 
    else if ( lookahead->tag == MINUS ) {
        test1 = match(MINUS);
        test2 = digit();
        genSub(); //Geracao de codigo por meio de funcao do GERADOR
        if (test1 && test2)
            return listR();
        return false;
    } //Verifica se fim de entrada
    else {
        if ( lookahead->tag == ENDTOKEN )
            return true;
        //Caso todos os testes falhem, retorna erro (false)
        return false; 
    }
}

/**
 * @brief Regra de derivacao da gramatica: DIGIT
 * 
 * @return int true/false
 */
int digit() {
    char aux_lexema[MAX_TOKEN];
    strcpy(aux_lexema, lookahead->lexema); //armazena temporariamente o lexema

    if ( match(NUM) ) {
        genNum(aux_lexema); //Geracao de codigo por meio de funcao do GERADOR
        return true;
    }
    return false;
}



/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main() {

    int acept;
    acept = false;
    
    initLex(); //Carrega codigo
    lookahead = getToken(); //Inicializacao do lookahead

    acept = list(); //Chamada da derivacao/funcao inicial da gramatica

    //Verifica aceitacao da cadeia/codigo
    if (acept) {
        printf("\tCadeia PERTENCENTE a linguagem\n");
    } else {
        printf("\tCadeia NAO pertencente a linguagem\n");
    }

    return 1;
}