%{
    #include <stdlib.h> 
    #include <stdio.h>
    #include <string.h>

    void yyerror(char *); 
    int yylex(void); 
    
    typedef struct simb_table {
      char lex[64];
      int val;
    } st;
    
    st table[100];
    int count_table = 0;

    int getVarIndex(st table[], char* name) {

      for (int i = 0; i < count_table; i++) {
        if ( !strcmp(table[i].lex,name) ) {
          return i;
        }
        
      }
      return -1;
    }

    void addVariable(st table[], char* name, int value) {

      if(count_table < 100){

        int auxIndex = getVarIndex(table, name);
        if (auxIndex != -1) {
          table[auxIndex].val = value;
          return;
        }
        strcpy(table[count_table].lex, name);
        table[count_table].val = value;
        count_table++;
      }
      return;

    }

%}

%union {
  struct var_table {
    char lex[64];
    int val;
  } vt;
  
}

%type <vt> program statement expr
%token <vt> INTEGER VARIABLE
%left '+' '-' 
%left '*' '/' 

%% 

program: 
        program statement '\n' 
        | %empty  { $$.lex[0] = '\0';}
        ; 
statement: 
        expr                      { printf("%d\n", $1.val); } 
        | VARIABLE '=' expr       { addVariable(table,$1.lex,$3.val); } 
        ; 
expr: 
        INTEGER                   { $$.val = $1.val;      }
        | VARIABLE                { $$.val = table[getVarIndex(table,$1.lex)].val; } 
        | expr '+' expr           { $$.val = $1.val + $3.val; } 
        | expr '-' expr           { $$.val = $1.val - $3.val; } 
        | expr '*' expr           { $$.val = $1.val * $3.val; } 
        | expr '/' expr           { $$.val = $1.val / $3.val; } 
        | '(' expr ')'            { $$.val = $2.val; } 
        ; 
%% 

void yyerror(char *s) { 
    printf("%s\n", s); 
} 

int main(void) { 
    yyparse(); 
    return 0; 
} 
