all: cminor

cminor: token.o lex.yy.o
	gcc token.o lex.yy.o -o cminor
token.o: token.c token.h
	gcc -c token.c
lex.yy.o: lex.yy.c token.h
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex scanner.l
clean:
	rm *.o lex.yy.c cminor
