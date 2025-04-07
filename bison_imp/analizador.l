%option noyywrap nodefault

%{
#include "analizador.tab.h"
#include <stdarg.h>

void yyerror(char *s, ...);
%}

%%
"+" { return opSuma; }
"-" { return opSuma; }
"*" { return opMul; }
"/" { return opMul; }
"(" { return '('; }
")" { return ')'; }

[0-9]+ { return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return NAME; }

\n { return EOL; }
[ \t] { /* ignorar espacio en blanco */ }
. { yyerror("Carácter misterioso %c\n", *yytext); }
%%

void yyerror(char *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}
