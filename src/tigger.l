%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"ast_tigger.h"
    #include"tigger.tab.hpp"    //保持以上顺序make
%}

%option prefix="tigger"

function    f_([_a-zA-Z][_a-zA-Z0-9]*)
variable    v{decimal}
reg x0|s0|s1|s2|s3|s4|s5|s6|s7|s8|s9|s10|s11|t0|t1|t2|t3|t4|t5|t6|a0|a1|a2|a3|a4|a5|a6|a7
label   l{decimal}
other  ("["|"]"|":"|"=")
operator ("&&"|"||"|"+"|"-"|"*"|"/"|"%"|"!")
logicop ("!="|"=="|">"|"<"|">="|"<=")
decimal (-?[1-9][0-9]*)|0
comment ("//".*)

%%

"if"    {
    AST *temp = new AST(_IF);
    tiggerlval.ast = temp;
    return IF;
}
"goto"  {
    AST *temp = new AST(_GOTO);
    tiggerlval.ast = temp;
    return GOTO;
}
"call"  {
    AST *temp = new AST(_CALL);
    tiggerlval.ast = temp;
    return CALL;
}
"load"  {
    AST *temp = new AST(_LOAD);
    tiggerlval.ast = temp;
    return LOAD;
}
"store" {
    AST *temp = new AST(_STORE);
    tiggerlval.ast = temp;
    return STORE;
}
"loadaddr"  {
    AST *temp = new AST(_LOADADDR);
    tiggerlval.ast = temp;
    return LOADADDR;
}
"return"    {
    AST *temp = new AST(_RETURN);
    tiggerlval.ast = temp;
    return RETURN;
}
"malloc"    {
    AST *temp = new AST(_MALLOC);
    tiggerlval.ast = temp;
    return MALLOC;
}
"end"   {
    AST *temp = new AST(_END);
    tiggerlval.ast = temp;
    return END;
}
{function} {
    AST *temp = new AST(_FUNCTION);
    temp->id = yytext;
    tiggerlval.ast = temp;
    return FUNCTION;
}
{variable} {
    AST *temp = new AST(_VARIABLE);
    temp->id = yytext;
    tiggerlval.ast = temp;
    return VARIABLE;
}
{reg} {
    AST *temp = new AST(_Reg);
    temp->id = yytext;
    tiggerlval.ast = temp;
    return Reg;
}
{label} {
    AST *temp = new AST(_LABEL);
    temp->id = yytext;
    tiggerlval.ast = temp;
    return LABEL;
}
{operator} {
    AST *temp = new AST(_OP);
    temp->op = yytext;
    tiggerlval.ast = temp;
    return OP;
}
{logicop} {
    AST *temp = new AST(_LOGICOP);
    temp->op = yytext;
    tiggerlval.ast = temp;
    return LOGICOP;
}
{other} {
    return yytext[0];
}
{decimal}   {
    AST *temp = new AST(_NUM);
    temp->val = atoi(yytext);
    tiggerlval.ast = temp;
    return NUM;
}
{comment}
\n
.

%%

int yywrap(){
    return 1;
}
