/**
 * @file gen.c
 * @author kaio-nink & Ivairton M. Santos
 * @date Sat Dec 11 2021
 * @brief Codificacao do modulo do analisador lexico
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
 * @brief Regra de derivacao da gramatica: E->TE'
 * 
 * @return int true/false 
 */
int E() {
    int test1, test2;
    test1 = T();
    if (test1) {
        test2 = ER();
    }
    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: E'->+TE' | E'-> -TE'| vazio
 * 
 * @return int true/false 
 */
int ER() {
    int test1, test2;
    //Verificacao para PLUS (+)
    if ( lookahead->tag == PLUS ) {
        match(PLUS);
        test1 = T();
        if (test1)
            test2 = ER();
        genAdd();
        return test1 && test2;
    //Verificacao para MINUS (-)
    } else if ( lookahead->tag == MINUS ) {
        match(MINUS);
        test1 = T();
        if(test1)
            test2 = ER();
        genSub();
        return test1 && test2;
    } 
    //Verificacao para PARCLOSE (')')
    else if ( lookahead->tag == PARCLOSE ) {
        return true;
    //Verificacao para ENDTOKEN ('\0')
    } else if ( match(ENDTOKEN) ) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: T->FT'
 * 
 * @return int true/false 
 */
int T() {
    int test1, test2;
    test1 = F();
    if (test1)
        test2 = TR();
    return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: TR->*FT' | TR->/FT' | vazio
 * 
 * @return int true/false 
 */
int TR() {
    int test1, test2;
    //Verificacao para MULT (*)
    if ( lookahead->tag == MULT ) {
        match(MULT);
        test1 = F();
        if (test1)
            test2 = TR();
        genMult();
        return test1 && test2;
    //Verificacao para DIV (/)
    } else if( lookahead->tag == DIV) {
        match(DIV);
        test1 = F();
        if(test1)
            test2 = TR();
        genDiv();
        return test1 && test2;
    }
    //Verificacao para PARCLOSE (')')
    else if ( lookahead->tag == PARCLOSE) {
        return true;
    } //Verificacao para ENDTOKEN ('\0')
    else if ( match(ENDTOKEN) ) {
        return true;
    } //Verificacao para PLUS (+)
    else if ( lookahead->tag == PLUS) {
        return true;
    } //Verificacao para MINUS (-)
    else if ( lookahead->tag == MINUS){
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Regra de derivacao da gramatica: F->(E)
 * 
 * @return int true/false 
 */
int F() {
    if ( lookahead->tag == PAROPEN ) {
        int test1, test2;
        match(PAROPEN);
        test1 = E();
        if (test1)
            test2 = match(PARCLOSE);
        return test1 && test2;
    } else if ( digit() ) {
        //Aqui iremos editar no futuro para processar o digito (a partir do lexico) e gerar codigo
        
        return true;
    } else {
        return false;
    }
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

    acept = E(); //Chamada da derivacao/funcao inicial da gramatica: E()

    //Verifica aceitacao da cadeia/codigo
    if (acept) {
        printf("\tCadeia PERTENCENTE a linguagem\n");
    } else {
        printf("\tCadeia NAO pertencente a linguagem\n");
    }

    return 1;
}