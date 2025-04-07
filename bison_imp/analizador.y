%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void yyerror(char *s, ...);
extern int yylex(void);
extern int yylineno;
%}

%token EOL NUMBER NAME opSuma opMul
%%
S: exp EOL
 | EOL
 ;

exp: NAME | NUMBER | '(' parenCierre
 | exp derechaSuma
 | term derechaMul
 ;

derechaSuma: opSuma term;
derechaMul: opMul factor;
parenCierre: exp ')';

term: NAME | NUMBER | '(' parenCierre
 | term derechaMul
 ;

factor: NAME | NUMBER | '(' parenCierre;
%%

int main()
{
  return yyparse();
}
