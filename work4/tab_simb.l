%{ 
    #include <stdio.h>
    #include <stdlib.h> 
    void yyerror(char *); 
    #include "tab_simb.tab.h" 
%} 

letter [A-Za-z]
digit [0-9]

%% 

{letter}({letter}|{digit}|_)* { 	
                strcpy(yylval.vt.lex,yytext);
		            // printf("Variavel: %s\n",yylval.vt.lex); 
                return VARIABLE; } 
{digit}+   {    yylval.vt.val = atoi(yytext);
		            // printf("Valor inteiro: %d\n",yylval.vt.val);
                return INTEGER; } 
[-+()=/*\n] { 	
		//printf("Operador: %c\n", yytext[0]);
		return *yytext; } 

[ \t]  {     }

.             	yyerror("invalid character"); 

%%
 
int yywrap(void) { 
    return 1; 
} 
