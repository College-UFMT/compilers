%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);
%}
%token INTEGER
%left '+' '-'
%left '*' '/'
%%
program:
    program expr '\n' { printf("%d\n", $2); }
    | 
    ;
expr: term { $$ = $1; } |
    expr '+' term { $$ = $1 + $3; } |
    expr '-' term { $$ = $1 - $3; }
    ;
term: factor { $$ = $1; } |
    term '*' factor { $$ = $1 * $3; } |
    term '/' factor { $$ = $1 / $3; }
    ;
factor: INTEGER { $$ = $1; } |
      '(' expr ')' { $$ = $2; }
      ;
%%
void yyerror(char *s){
    printf("%s\n", s);
}
int main(void) {
    yyparse();
    return 0;
}