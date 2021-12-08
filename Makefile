LEX=flex
YACC=bison
CC=gcc
OBJECT=mycompiler

$(OBJECT): lex.yy.o y.tab.o main.o
	$(CC) lex.yy.o y.tab.o main.o -o $(OBJECT)

lex.yy.o: lex.yy.c y.tab.h
	$(CC) -c lex.yy.c

y.tab.o: y.tab.c y.tab.h
	$(CC) -c y.tab.c

y.tab.c  y.tab.h: parser.y
	$(YACC) -d y.tab.c

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	@rm -f $(OBJECT)  *.o