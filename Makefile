LEX=flex
YACC=bison
CC=g++
OBJECT=lex.yy.o parser.tab.o ast.o main.o

mycompiler: $(OBJECT)
	$(CC) $(OBJECT) -o mycompiler

main.o: main.c parser.tab.h
	$(CC) -c main.c

ast.o: ast.cpp ast.h
	$(CC) -c ast.cpp

lex.yy.o: lex.yy.c parser.tab.h ast.h
	$(CC) -c lex.yy.c

parser.tab.o: parser.tab.c parser.tab.h ast.h
	$(CC) -c parser.tab.c

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	@rm -f mycompiler *.o