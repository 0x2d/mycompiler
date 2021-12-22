%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    //保持以下顺序
    #include"ast.h"
    #include"parser.tab.hpp"
    //保持以上顺序
%}

%x COMMENTS

ident   ([_a-zA-Z][_a-zA-Z0-9]*)
symbol  ("("|")"|"["|"]"|"{"|"}"|";"|",")
operator ("="|">"|"<"|"+"|"-"|"*"|"/"|"%"|"!")
decimal ([1-9][0-9]*)|0
oct 0[0-7]*
hex 0[xX][0-9A-Fa-f]+
comment ("//".*)


%%

"/*"    {BEGIN COMMENTS;}
<COMMENTS>.
<COMMENTS>\n
<COMMENTS>"*/"  {BEGIN INITIAL;}

"int"   {
    AST *temp = new AST(_INT);
    yylval.ast = temp;
    return INT;
}
"void"  {
    AST *temp = new AST(_VOID);
    yylval.ast = temp;
    return VOID;
}
"const" {
    AST *temp = new AST(_CONST);
    yylval.ast = temp;
    return CONST;
}
"if"    {
    AST *temp = new AST(_IF);
    yylval.ast = temp;
    return IF;
}
"else"  {
    AST *temp = new AST(_ELSE);
    yylval.ast = temp;
    return ELSE;
}
"while" {
    AST *temp = new AST(_WHILE);
    yylval.ast = temp;
    return WHILE;
}
"break" {
    AST *temp = new AST(_BREAK);
    yylval.ast = temp;
    return BREAK;
}
"continue"  {
    AST *temp = new AST(_CONTINUE);
    yylval.ast = temp;
    return CONTINUE;
}
"return"    {
    AST *temp = new AST(_RETURN);
    yylval.ast = temp;
    return RETURN;
}
"<="    {
    AST *temp = new AST(_LE);
    yylval.ast = temp;
    return LE;
}
">="    {
    AST *temp = new AST(_GE);
    yylval.ast = temp;
    return GE;
}
"=="    {
    AST *temp = new AST(_EQ);
    yylval.ast = temp;
    return EQ;
}
"!="    {
    AST *temp = new AST(_NE);
    yylval.ast = temp;
    return NE;
}
"&&"    {
    AST *temp = new AST(_AND);
    yylval.ast = temp;
    return AND;
}
"||"    {
    AST *temp = new AST(_OR);
    yylval.ast = temp;
    return OR;
}
{ident} {
    char *id = (char *)malloc(sizeof(yytext));
    memset(id, '\0', sizeof(id));
    strcpy(id,yytext);
    AST *temp = new AST(_IDENT, id);
    yylval.ast = temp;
    return IDENT;
}
{operator} {
    AST *temp = new AST(_OP, yytext[0]);
    yylval.ast = temp;
    return yytext[0];
}
{symbol} {
    return yytext[0];
}
{decimal}   {
    AST *temp = new AST(_INT_CONST,atoi(yytext));
    yylval.ast = temp;
    return INT_CONST;
}
{oct}   {
    int val = strtol(yytext, NULL, 8);
    AST *temp = new AST(_INT_CONST,val);
    yylval.ast = temp;
    return INT_CONST;
}
{hex}   {
    int val = strtol(yytext, NULL, 16);
    AST *temp = new AST(_INT_CONST,val);
    yylval.ast = temp;
    return INT_CONST;
}
{comment}
\n
.

%%

int yywrap(){
    return 1;
}