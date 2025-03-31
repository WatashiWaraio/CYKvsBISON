# CYKvsBISON

## Gramática en forma normal de Chomsky (CNF) para la comparación

```
OPMUL -> * | /
OPSUMA -> + | -
PARI -> (
PARD -> )

E -> E DERECHASUMA | T DERECHAMUL | id | num | PARI PARENCIERRE
DERECHASUMA -> OPSUMA T
T -> T DERECHAMUL
DERECHAMUL -> OPMUL F

T -> id | num | PARI PARENCIERRE
F -> id | num | PARI PARENCIERRE

PARENCIERRE -> E PARD
```
