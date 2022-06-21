%{
    #include <stdlib.h> 
    #include <stdio.h>
    #include <string.h>

    void yyerror(char *); 
    int yylex(void); 
    
    typedef struct simb_table {
      int val;
      char lex[64];
    } st;
    
    st table[100];
    int count_table = 0;

%}

%union {
  struct simb_table {
    int val;
    char lex[64];
  } st;
}

%type <int> program statement expr
%token <st> VARIABLE  
%token <int> INTEGER 
%left '+' '-' 
%left '*' '/' 

%% 

program: 
        program statement '\n' 
        | %empty {$$ = '\0';}  
        ; 
statement: 
        expr                      { printf("%d\n", $1); } 
        | VARIABLE '=' expr       { table[count_table].val = $3;  
                                    strcpy(table[count_table].lex,$1.lex);
                                    count_table++; } 
        ; 
expr: 
        INTEGER                   { $$ = $1;      }
        | VARIABLE                { strcpy($$,$1.lex); } 
        | expr '+' expr           { $$ = $1 + $3; } 
        | expr '-' expr           { $$ = $1 - $3; } 
        | expr '*' expr           { $$ = $1 * $3; } 
        | expr '/' expr           { $$ = $1 / $3; } 
        | '(' expr ')'            { $$ = $2; } 
        ; 
%% 

void yyerror(char *s) { 
    printf("%s\n", s); 
    //return 0; 
} 

int main(void) { 
    yyparse(); 
    return 0; 
} 
