%{
  // @author Kaio Felipe Nink Cardoso && Fillipe Augusto de Siqueira Gomes
  #include <stdio.h>
  int yylex(void);
  void yyerror(char *);
%}
  %union {
      char str[64];
    };
  %type <str> oracao sujeito predicado artigo substantivo verbo complemento
  %token <str> O A GATO CACHORRO COMIDA BISCOITO EH COME BONITO FEIO

%%
  oracao: sujeito predicado{
    strcpy($$,$1);
    strcat($$," ");
    strcat($$, $2);
    printf("Oracao: %s\n", $$);}
  ;
  sujeito : artigo substantivo {
    strcpy($$,$1);
    strcat($$," ");
    strcat($$, $2);
    printf("Sujeito: %s\n", $$); }
  ; 
  artigo : O { 
      strcpy($$,$1);
      printf("Artigo: %s\n",$$); }
  | A {
      strcpy($$,$1);
      printf("Artigo: %s\n",$$); }
  ; 
  substantivo : GATO {
      strcpy($$,$1);
      printf("Substantivo: %s\n",$$); }
    | CACHORRO {
      strcpy($$,$1);
      printf("Substantivo: %s\n",$$); }
    | COMIDA {
      strcpy($$,$1); 
      printf("Substantivo: %s\n",$$); }
    | BISCOITO {
      strcpy($$,$1); 
      printf("Substantivo: %s\n",$$); }
  ;

  predicado: verbo complemento {
    strcpy($$,$1);
    strcat($$," ");
    strcat($$, $2);
    printf("Predicado: %s\n", $$);
  }
  ;
  verbo : EH { 
      strcpy($$,$1);
      printf("Verbo: %s\n",$$); }
    | COME {
      strcpy($$,$1);
      printf("Verbo: %s\n",$$); }
  ; 
  complemento : BONITO { 
      strcpy($$,$1);
      printf("Verbo: %s\n",$$); }
    | FEIO {
      strcpy($$,$1);
      printf("Verbo: %s\n",$$); }
    | substantivo {
      strcpy($$,$1);
      strcat($$," ");
    }
  ; 

%%
void yyerror(char *s){
    printf("%s\n", s);
}
int main(void) {
    yyparse();
    return 0;
}