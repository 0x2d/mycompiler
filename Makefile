LEX=flex
YACC=bison
CC=g++
OBJECT=main

$(OBJECT): lex.yy.o  y.tab.o main.o
    $(CC) lex.yy.o y.tab.o -o $(OBJECT)
    @./$(OBJECT) #编译后立刻运行

lex.yy.o: lex.yy.c  y.tab.h 
    $(CC) -c lex.yy.c

yacc.tab.o: yacc.tab.c
    $(CC) -c yacc.tab.c

yacc.tab.c  yacc.tab.h: yacc.y
# bison使用-d参数编译.y文件
    $(YACC) -d yacc.y

lex.yy.c: lex.l
    $(LEX) lex.l

clean:
    @rm -f $(OBJECT)  *.o