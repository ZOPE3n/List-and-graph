
SOURCES = Lex.c List.c List.h ListClient.c Makefile README

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

submit:
	submit cmps101-pt.f14 pa2 $(SOURCES)

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o
