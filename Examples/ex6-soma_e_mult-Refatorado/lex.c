/**
 * @file lex.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador lexico
 * @version 0.2
 * @date 2021-11-30
 * 
 */

// Inclusao do cabecalho
#include "lex.h"

/**
 * @brief Processo de inicializacao do lexico. Tem funcao de receber o codigo
 *        de entrada.
 * 
 */
void initLex() {
    printf("Informe um código para ser avaliado:");
    gets(string);
    //strcpy(string, "22*33");
}

/**
 * @brief Analisa o proximo comando no código de entrada e retorna estrutura de
 * dados com Token correspondente (ponteiro).
 * 
 * @return type_token* 
 */
type_token *getToken() {
    char buffer[MAX_CHAR];
    int pos_buffer;
    type_token *token;
    
    pos_buffer = 0;
    token = (type_token*) malloc(sizeof(type_token));

    // Consome espacos
    while ( isspace(string[pos]) ) {
        pos++;
    }

    // Verifica se NUMERO
    if ( isdigit(string[pos]) ) {
        // constroi buffer com os digitos
        while ( isdigit(string[pos]) ) {
            buffer[pos_buffer++] = string[pos++];
        }
        buffer[pos_buffer] = '\0';
        token->tag = NUM;
        strcpy( token->lexema, buffer ); //copia buffer para lexema
    } 
    //Verifica se PLUS (+)
    else if (string[pos] == PLUS) {
        token->tag = PLUS;
        strcpy(token->lexema, "+");
        pos++;
    }
    //Verifica se MINUS (-)
    else if (string[pos] == MINUS) {
        token->tag = MINUS;
        strcpy(token->lexema, "-");
        pos++;
    }
    //Verifica se MULT (*)
    else if (string[pos] == MULT) {
        token->tag = MULT;
        strcpy(token->lexema, "*");
        pos++;
    }
    //Verifica se DIV (/)
    else if (string[pos] == DIV) {
        token->tag = DIV;
        strcpy(token->lexema, "/");
        pos++;
    }
    //Verifica se OPEN_PAR -> "("
    else if (string[pos] == OPEN_PAR) {
        token->tag = OPEN_PAR;
        strcpy(token->lexema, "(");
        pos++;
    }
    //Verifica se CLOSE_PAR -> ")"
    else if (string[pos] == CLOSE_PAR) {
        token->tag = CLOSE_PAR;
        strcpy(token->lexema, ")");
        pos++;
    }
    //Verifica se FIM DE CADEIA
    else if (string[pos] == ENDTOKEN) {
        token->tag = ENDTOKEN;
        strcpy(token->lexema, "");
    }
    //ERRO
    else {
        token->tag = ERROR;
        strcpy(token->lexema, "");
    }

    return token;
}