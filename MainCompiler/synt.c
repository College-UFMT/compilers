/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico COM GERACAO DE CODIGO INTERMEDIARIO
 * @version 0.3
 * @date 2022-04-25
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
int match(int token_tag)
{
  if (lookahead->tag == token_tag)
  {
    lookahead = getToken(); // Pega o proximo token por meio do lexico
    return true;
  }
  return false;
}

/**
 * @brief Regra de derivacao da gramatica: DIGIT
 *
 * @return int true/false
 */
// int digit()
// {
//   char aux_lexema[MAX_TOKEN];
//   strcpy(aux_lexema, lookahead->lexema); // armazena temporariamente o lexema

//   if (match(NUM))
//   {
//     genNum(aux_lexema); // Geracao de codigo por meio de funcao do GERADOR
//     return true;
//   }
//   return false;
// }

/**
 * @brief Regra de derivacao da gramatica: E->TE'
 *
 * @return int true/false
 */
int E(type_code *e_code)
{
  int test1, test2;
  type_code *t_code;
  type_code *er_code;
  int *last_operation;

  last_operation = (int *)malloc(sizeof(int));
  t_code = (type_code *)malloc(sizeof(type_code));
  er_code = (type_code *)malloc(sizeof(type_code));

  newTemp(e_code->temp);
  // printf("%s",e_code->temp);
  
  test1 = T(t_code);
  // printf("%s",t_code->temp);

  if (test1){
    test2 = ER(last_operation, er_code);
  }

  strcpy(e_code->code, t_code->code);
  test2 = ER(last_operation, er_code);

  strcpy(e_code->code, t_code->code);
  strcat(e_code->code, er_code->code);

  switch (*last_operation)
  {
  case '+':
    strcat(e_code->code, e_code->temp);
    strcat(e_code->code, "=");
    strcat(e_code->code, t_code->temp);
    strcat(e_code->code, "+");
    strcat(e_code->code, er_code->temp);
    break;
  case '-':
    strcat(e_code->code, e_code->temp);
    strcat(e_code->code, "=");
    strcat(e_code->code, t_code->temp);
    strcat(e_code->code, "-");
    strcat(e_code->code, er_code->temp);
    break;
  case '\0':
    printf("[ERRO] Operacao nao definida!\n");
    break;
  }

  return test1 && test2;
}

/**
 * @brief Regra de derivacao da gramatica: E'->+TE'
 *
 * @return int true/false
 */
int ER(int *lastOperation, type_code *erCode)
{
  type_code *tCode;
  type_code *er1Code;
  int *lOperation;

  lOperation = (int *)malloc(sizeof(int));
  tCode = (type_code *)malloc(sizeof(type_code));
  er1Code = (type_code *)malloc(sizeof(type_code));

  if (lookahead->tag == '+')
  {
    int b1, b2;
    match('+');
    *lastOperation = (int)'+';
    b1 = T(tCode);
    strcpy(erCode->temp, tCode->temp);
    if (b1)
      b2 = ER(lOperation, er1Code);
    strcpy(erCode->code, tCode->code);
    strcpy(erCode->code, er1Code->code);
    return b1 && b2;
  }
  else if (lookahead->tag == '-') {
    int b1, b2;
    match('-');
    *lastOperation = (int) '-';
    b1 = T(tCode);
    strcpy(erCode->temp, tCode->temp);
    if (b1)
      b2 = ER(lOperation, er1Code);
    strcpy(erCode->code, tCode->code);
    strcpy(erCode->code, er1Code->code);
    return b1 && b2;
  } 
  else if (lookahead->tag == ')') {
    strcpy(erCode->code, "\0");
    return true;
  }
  else if (lookahead->tag == ENDTOKEN)
  {
    strcpy(erCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else if (lookahead->tag == '*')
  {
    strcpy(erCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else if (lookahead->tag == ENDTOKEN)
  {
    strcpy(erCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * @brief Regra de derivacao da gramatica: T->FT'
 *
 * @return int true/false
 */
int T(type_code *tCode)
{
  type_code *fCode;
  type_code *trCode;
  int b1, b2, *lastOperation;
  newTemp(tCode->temp);

  lastOperation = (int *)malloc(sizeof(int));
  fCode = (type_code *)malloc(sizeof(type_code));
  trCode = (type_code *)malloc(sizeof(type_code));
  
  b1 = F(fCode);
  if (b1)
    b2 = TR(lastOperation, trCode);

  strcpy(tCode->code, fCode->code);
  strcpy(tCode->code, trCode->code);
}

/**
 * @brief Regra de derivacao da gramatica: T'->*FT'
 *
 * @return int true/false
 */
int TR(int *lastOperation, type_code *trCode)
{
  type_code *fCode;
  type_code *tr1Code;
  int *lOperation;

  lOperation = (int *)malloc(sizeof(int));
  fCode = (type_code *)malloc(sizeof(type_code));
  tr1Code = (type_code *)malloc(sizeof(type_code));

  if (lookahead->tag == '*')
  {
    int b1, b2;
    match('*');
    *lastOperation = (int)'*';
    b1 = F(fCode);
    strcpy(trCode->temp, fCode->temp);
    if (b1)
      b2 = TR(lOperation, tr1Code);
    strcpy(trCode->code, fCode->code);
    strcpy(trCode->code, tr1Code->code);
    return b1 && b2;
  }
  else if (lookahead->tag == '/') {
    int b1, b2;
    match('/');
    *lastOperation = (int) '/';
    b1 = F(fCode);
    strcpy(trCode->temp, fCode->temp);
    if (b1)
      b2 = TR(lOperation, tr1Code);
    strcpy(trCode->code, fCode->code);
    strcpy(trCode->code, tr1Code->code);
    return b1 && b2;
  } 
  else if (lookahead->tag == ENDTOKEN)
  {
    strcpy(trCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else if (lookahead->tag == '+')
  {
    strcpy(trCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else if (lookahead->tag == ENDTOKEN)
  {
    strcpy(trCode->temp, "");
    (*lastOperation) = '\0';
    return true;
  }
  else
  {
    return false;
  }

}

/**
 * @brief Regra de derivacao da gramatica: F->(E)
 *
 * @return int true/false
 */
int F(type_code *fCode)
{
  type_code *eCode;
  eCode = (type_code *)malloc(sizeof(type_code));
  if (lookahead->tag == '(')
  {
    int b1, b2;
    match('(');
    b1 = E(eCode);
    if (b1)
      b2 = match(')');
    strcpy(fCode->temp, eCode->temp);
    strcpy(fCode->code, eCode->code);
    return b1 && b2;
  }
  else if (lookahead->tag == NUM)
  {
    int b1;
    char lexema[MAX_TOKEN];
    strcpy(lexema, lookahead->lexema);
    b1 = match(NUM);
    newTemp(fCode->temp);
    strcpy(fCode->code, fCode->temp);
    strcpy(fCode->code, "=");
    strcpy(fCode->code, lexema);
    strcpy(fCode->code, "\n");
    return b1;
  }
  else
  {
    return false;
  }
}

//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 *
 * @return int
 */
int main()
{

  type_code *e_code;
  int accept;

  e_code = (type_code *)malloc(sizeof(type_code));
  accept = false;

  initLex();              // Carrega codigo
  lookahead = getToken(); // Inicializacao do lookahead

  accept = E(e_code); // Chamada da derivacao/funcao inicial da gramatica

  // Imprime na tela o codigo intermediario gerado
  printf("%s\n", e_code->code);

  // Verifica aceitacao da cadeia/codigo
  if (accept)
  {
    printf("\tCadeia PERTENCENTE a linguagem\n");
  }
  else
  {
    printf("\tCadeia NAO pertencente a linguagem\n");
  }

  return 1;
}