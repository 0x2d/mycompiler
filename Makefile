LEX=flex
YACC=bison
CC=g++
OBJECT=lex.yy.o parser.tab.o symtable.o ast.o main.o

mycompiler: $(OBJECT)
	$(CC) $(OBJECT) -o mycompiler

main.o: main.cpp parser.tab.h ast.h symtable.h
	$(CC) -c main.cpp

ast.o: ast.cpp ast.h
	$(CC) -c ast.cpp

symtable.o: symtable.cpp symtable.h
	$(CC) -c symtable.cpp

lex.yy.o: lex.yy.c parser.tab.h ast.h
	$(CC) -c lex.yy.c

parser.tab.o: parser.tab.c parser.tab.h ast.h symtable.h
	$(CC) -c parser.tab.c

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: lexer.l
	$(LEX) lexer.l

clean:
	@rm -f mycompiler *.o