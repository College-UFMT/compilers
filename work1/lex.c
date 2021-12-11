/**
 * @file gen.c
 * @author kaio-nink & Ivairton M. Santos
 * @date Sat Dec 11 2021
 * @brief Codificacao do modulo do analisador lexico
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
    //Verifica se PAROPEN ('(')
    else if (string[pos] == PAROPEN) {
       token->tag = PAROPEN;
       strcpy(token->lexema, "(");
       pos++;
    }
    //Verifica se PARCLOSE (')')
    else if (string[pos] == PARCLOSE) {
       token->tag = PARCLOSE;
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