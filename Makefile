LEX=flex
YACC=bison
CC=gcc
OBJECT=mycompiler

$(OBJECT): lex.yy.o parser.tab.o main.o
	$(CC) lex.yy.o parser.tab.o main.o -o $(OBJECT)

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) -c lex.yy.c

parser.tab.o: parser.tab.c parser.tab.h
	$(CC) -c parser.tab.c

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	@rm -f $(OBJECT)  *.o