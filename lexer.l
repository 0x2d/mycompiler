%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"parser.tab.h"
%}

ident   ([_a-zA-Z][_a-zA-Z0-9]*)
symbol  ("="|">"|"<"|"+"|"-"|"*"|"/"|"%"|"!")|("("|")"|"["|"]"|"{"|"}"|";"|",")
integer ([0-9]+)


%%

"int"   {return INT;}
"void"  {return VOID;}
"const" {return CONST;}
"if"    {return IF;}
"else"  {return ELSE;}
"while" {return WHILE;}
"break" {return BREAK;}
"continue"  {return CONTINUE;}
"return"    {return RETURN;}
"<="    {return LE;}
">="    {return GE;}
"=="    {return EQ;}
"!="    {return NE;}
"&&"    {return AND;}
"OR"    {return OR;}
{ident} {return IDENT;}
{symbol} {return yytext[0];}
{integer}   {
    yylval.val = atoi(yytext);
    return INT_CONST;
}
\n
.

%%