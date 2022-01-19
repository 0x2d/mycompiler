%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"ast_eeyore.h"
    #include"eeyore.tab.hpp"    //保持以上顺序
%}

%option prefix="eeyore"

function    f_([_a-zA-Z][_a-zA-Z0-9]*)
symbol (T|t|p){decimal}
label   l{decimal}
other  ("["|"]"|":"|"=")
operator ("&&"|"||"|"+"|"-"|"*"|"/"|"%"|"!")
logicop ("!="|"=="|">"|"<"|">="|"<=")
decimal (-?[1-9][0-9]*)|0
comment ("//".*)

%%

"if"    {
    AST *temp = new AST(_IF);
    eeyorelval.ast = temp;
    return IF;
}
"goto"  {
    AST *temp = new AST(_GOTO);
    eeyorelval.ast = temp;
    return GOTO;
}
"call"  {
    AST *temp = new AST(_CALL);
    eeyorelval.ast = temp;
    return CALL;
}
"param"  {
    AST *temp = new AST(_PARAM);
    eeyorelval.ast = temp;
    return PARAM;
}
"var"   {
    AST *temp = new AST(_VAR);
    eeyorelval.ast = temp;
    return VAR;
}
"return"    {
    AST *temp = new AST(_RETURN);
    eeyorelval.ast = temp;
    return RETURN;
}
"end"   {
    AST *temp = new AST(_END);
    eeyorelval.ast = temp;
    return END;
}
{function} {
    AST *temp = new AST(_FUNCTION);
    temp->id = yytext;
    eeyorelval.ast = temp;
    return FUNCTION;
}
{symbol} {
    AST *temp = new AST(_SYMBOL);
    temp->id = yytext;
    eeyorelval.ast = temp;
    return SYMBOL;
}
{label} {
    AST *temp = new AST(_LABEL);
    temp->id = yytext;
    eeyorelval.ast = temp;
    return LABEL;
}
{operator} {
    AST *temp = new AST(_OP);
    temp->op = yytext;
    eeyorelval.ast = temp;
    return OP;
}
{logicop} {
    AST *temp = new AST(_LOGICOP);
    temp->op = yytext;
    eeyorelval.ast = temp;
    return LOGICOP;
}
{other} {
    return yytext[0];
}
{decimal}   {
    AST *temp = new AST(_NUM);
    temp->val = atoi(yytext);
    eeyorelval.ast = temp;
    return NUM;
}
{comment}
\n
.

%%

int yywrap(){
    return 1;
}
