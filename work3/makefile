compiler: lex.yy.o gramatica.tab.o
	gcc -o comp lex.yy.o gramatica.tab.o

gramatica.tab.c: gramatica.y
	bison -d gramatica.y

lex.yy.c: gramflex.l
	flex gramflex.l

gramatica.tab.o: gramatica.tab.c
	gcc -c gramatica.tab.c 

lex.yy.o: lex.yy.c 
	gcc -c lex.yy.c

clean:
	rm *.o *.c *.tab.h comp