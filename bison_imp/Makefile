analizador: analizador.l analizador.y
	bison -d analizador.y
	flex -oanalizador.lex.c analizador.l
	cc -o $@ analizador.tab.c analizador.lex.c

clean:
	rm analizador.tab.c analizador.tab.h analizador.lex.c analizador
