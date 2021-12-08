%{
    #include<stdio.h>
    extern FILE *yyin;
    extern FILE *yyout;
    extern int yylex();
%}

%union{
    int val;
}

%token CONST INT VOID IF ELSE WHILE BREAK CONTINUE RETURN
%token IDENT
%token <val> INT_CONST

%%

CompUnit    : CompUnit Decl 
            | CompUnit FuncDef
            ;

Decl    : ConstDecl 
        | VarDecl
        ;

ConstDecl   : CONST BType ConstDef 
            | ConstDecl "," ConstDef ";"
            ;

BType   : INT
        ;

ConstDef    : IDENT ConstExp_temp "=" ConstInitVal
            ;

ConstExp_temp   : ConstExp_temp "[" ConstExp "]"
                |
                ;

ConstInitVal    : ConstExp 
                | "{" "}"
                | "{" ConstInitVal_temp "}"
                ;

ConstInitVal_temp   : ConstInitVal
                    | ConstInitVal_temp "," ConstInitVal
                    ;

VarDecl : BType VarDef_temp ";"
        ;

VarDef_temp : VarDef
            | VarDef_temp "," VarDef
            ;

VarDef  : IDENT ConstExp_temp
        | IDENT ConstExp_temp "=" InitVal
        ;

InitVal : Exp 
        | "{" "}"
        | "{" InitVal_temp "}"
        ;

InitVal_temp    : InitVal
                | InitVal_temp "," InitVal
                ;

FuncDef : FuncType IDENT "(" FuncFParams ")" Block
        | FuncType IDENT "(" ")" Block
        ;

FuncType    : VOID 
            | INT
            ;

FuncFParams : FuncFParam
            | FuncFParams "," FuncFParam
            ;

FuncFParam  : BType IDENT "[" "]" ConstExp_temp
            | BType IDENT
            ;

Block   : "{" BlockItem_temp "}"
        ;

BlockItem_temp  : BlockItem_temp BlockItem
                | 
                ;

BlockItem   : Decl 
            | Stmt
            ;

Stmt    : LVal "=" Exp ";"
        | Exp ";"
        | ";"
        | Block
        | IF "(" Cond ")" Stmt ELSE Stmt
        | IF "(" Cond ")" Stmt
        | WHILE "(" Cond ")" Stmt
        | BREAK ";"
        | CONTINUE ";"
        | RETURN Exp ";"
        | RETURN ";"
        ;

Exp : AddExp
    ;

Cond    : LOrExp
        ;

LVal    : IDENT
        | LVal "[" Exp "]"
        ;

PrimaryExp  : "(" Exp ")" 
            | LVal 
            | Number
            ;

Number  : INT_CONST
        ;

UnaryExp    : PrimaryExp 
            | IDENT "(" FuncRParams ")" 
            | IDENT "(" ")" 
            | UnaryOp UnaryExp
            ;

UnaryOp : "+" 
        | "-" 
        | "!"
        ;

FuncRParams : Exp 
            | FuncRParams "," Exp
            ;

MulExp  : UnaryExp 
        | MulExp "*" UnaryExp
        | MulExp "/" UnaryExp
        | MulExp "%" UnaryExp
        ;

AddExp  : MulExp 
        | AddExp "+" MulExp
        | AddExp "-" MulExp
        ;

RelExp  : AddExp 
        | RelExp "<" AddExp
        | RelExp ">" AddExp
        | RelExp "<=" AddExp
        | RelExp ">=" AddExp
        ;

EqExp   : RelExp 
        | EqExp "==" RelExp
        | EqExp "!=" RelExp
        ;

LAndExp : EqExp 
        | LAndExp "&&" EqExp
        ;

LOrExp  : LAndExp 
        | LOrExp "||" LAndExp
        ;

ConstExp    : AddExp
            ;

%%