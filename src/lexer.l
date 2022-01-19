%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"ast_sysy.h"
    #include"parser.tab.hpp" //保持此顺序
    
    int lineno = 1;
%}

%option prefix="sysy"
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
    sysylval.ast = temp;
    return INT;
}
"void"  {
    AST *temp = new AST(_VOID);
    sysylval.ast = temp;
    return VOID;
}
"const" {
    AST *temp = new AST(_CONST);
    sysylval.ast = temp;
    return CONST;
}
"if"    {
    AST *temp = new AST(_IF);
    sysylval.ast = temp;
    return IF;
}
"else"  {
    AST *temp = new AST(_ELSE);
    sysylval.ast = temp;
    return ELSE;
}
"while" {
    AST *temp = new AST(_WHILE);
    sysylval.ast = temp;
    return WHILE;
}
"break" {
    AST *temp = new AST(_BREAK);
    sysylval.ast = temp;
    return BREAK;
}
"continue"  {
    AST *temp = new AST(_CONTINUE);
    sysylval.ast = temp;
    return CONTINUE;
}
"return"    {
    AST *temp = new AST(_RETURN);
    sysylval.ast = temp;
    return RETURN;
}
"<="    {
    AST *temp = new AST(_LE);
    sysylval.ast = temp;
    return LE;
}
">="    {
    AST *temp = new AST(_GE);
    sysylval.ast = temp;
    return GE;
}
"=="    {
    AST *temp = new AST(_EQ);
    sysylval.ast = temp;
    return EQ;
}
"!="    {
    AST *temp = new AST(_NE);
    sysylval.ast = temp;
    return NE;
}
"&&"    {
    AST *temp = new AST(_AND);
    sysylval.ast = temp;
    return AND;
}
"||"    {
    AST *temp = new AST(_OR);
    sysylval.ast = temp;
    return OR;
}
{ident} {
    AST *temp = new AST(_IDENT);
    temp->id = yytext;
    sysylval.ast = temp;
    return IDENT;
}
{operator} {
    AST *temp = new AST(_OP, yytext[0]);
    sysylval.ast = temp;
    return yytext[0];
}
{symbol} {
    return yytext[0];
}
{decimal}   {
    AST *temp = new AST(_INT_CONST,atoi(yytext));
    sysylval.ast = temp;
    return INT_CONST;
}
{oct}   {
    int val = strtol(yytext, NULL, 8);
    AST *temp = new AST(_INT_CONST,val);
    sysylval.ast = temp;
    return INT_CONST;
}
{hex}   {
    int val = strtol(yytext, NULL, 16);
    AST *temp = new AST(_INT_CONST,val);
    sysylval.ast = temp;
    return INT_CONST;
}
{comment}
\n  {lineno++;}
.

%%

int yywrap(){
    return 1;
}