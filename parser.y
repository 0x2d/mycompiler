%{
    #include<stdio.h>
    extern FILE *yyin;
    extern FILE *yyout;
    extern int yylex();
    void yyerror(char *str){};
%}

%union{
    int val;
}

%token CONST INT VOID IF ELSE WHILE BREAK CONTINUE RETURN
%token IDENT
%token <val> INT_CONST

%%

CompUnit    : CompUnit Decl {printf("r CompUnit\n");}
            | CompUnit FuncDef {printf("r CompUnit\n");}
            | Decl {printf("r CompUnit\n");}
            | FuncDef {printf("r CompUnit\n");}
            ;

Decl    : ConstDecl {printf("r Decl\n");}
        | VarDecl {printf("r Decl\n");}
        ;

ConstDecl   : CONST BType ConstDef {printf("r ConstDecl\n");}
            | ConstDecl "," ConstDef ";" {printf("r ConstDecl\n");}
            ;

BType   : INT {printf("r BType\n");}
        ;

ConstDef    : IDENT ConstExp_temp "=" ConstInitVal {printf("r ConstDef\n");}
            ;

ConstExp_temp   : ConstExp_temp "[" ConstExp "]" {printf("r ConstExp_temp\n");}
                | {printf("r ConstExp_temp\n");}
                ;

ConstInitVal    : ConstExp {printf("r ConstInitVal\n");}
                | "{" "}" {printf("r ConstInitVal\n");}
                | "{" ConstInitVal_temp "}" {printf("r ConstInitVal\n");}
                ;

ConstInitVal_temp   : ConstInitVal {printf("r ConstInitVal_temp\n");}
                    | ConstInitVal_temp "," ConstInitVal {printf("r ConstInitVal_temp\n");}
                    ;

VarDecl : BType VarDef_temp ";" {printf("r VarDecl\n");}
        ;

VarDef_temp : VarDef {printf("r VarDef_temp\n");}
            | VarDef_temp "," VarDef {printf("r VarDef_temp\n");}
            ;

VarDef  : IDENT ConstExp_temp {printf("r VarDef\n");}
        | IDENT ConstExp_temp "=" InitVal {printf("r VarDef\n");}
        ;

InitVal : Exp {printf("r InitVal\n");}
        | "{" "}" {printf("r InitVal\n");}
        | "{" InitVal_temp "}" {printf("r InitVal\n");}
        ;

InitVal_temp    : InitVal {printf("r InitVal_temp\n");}
                | InitVal_temp "," InitVal {printf("r InitVal_temp\n");}
                ;

FuncDef : FuncType IDENT "(" FuncFParams ")" Block {printf("r FuncDef\n");}
        | FuncType IDENT "(" ")" Block {printf("r FuncDef\n");}
        ;

FuncType    : VOID {printf("r FuncType\n");}
            | INT {printf("r FuncType\n");}
            ;

FuncFParams : FuncFParam {printf("r FuncFParams\n");}
            | FuncFParams "," FuncFParam {printf("r FuncFParams\n");}
            ;

FuncFParam  : BType IDENT "[" "]" ConstExp_temp {printf("r FuncFParam\n");}
            | BType IDENT {printf("r FuncFParam\n");}
            ;

Block   : "{" BlockItem_temp "}" {printf("r Block\n");}
        ;

BlockItem_temp  : BlockItem_temp BlockItem {printf("r BlockItem_temp\n");}
                | {printf("r BlockItem_temp\n");}
                ;

BlockItem   : Decl {printf("r BlockItem\n");}
            | Stmt {printf("r BlockItem\n");}
            ;

Stmt    : LVal "=" Exp ";" {printf("r Stmt\n");}
        | Exp ";" {printf("r Stmt\n");}
        | ";" {printf("r Stmt\n");}
        | Block {printf("r Stmt\n");}
        | IF "(" Cond ")" Stmt ELSE Stmt {printf("r Stmt\n");}
        | IF "(" Cond ")" Stmt {printf("r Stmt\n");}
        | WHILE "(" Cond ")" Stmt {printf("r Stmt\n");}
        | BREAK ";" {printf("r Stmt\n");}
        | CONTINUE ";" {printf("r Stmt\n");}
        | RETURN Exp ";" {printf("r Stmt\n");}
        | RETURN ";" {printf("r Stmt\n");}
        ;

Exp : AddExp {printf("r Exp\n");}
    ;

Cond    : LOrExp {printf("r Cond\n");}
        ;

LVal    : IDENT {printf("r LVal\n");}
        | LVal "[" Exp "]" {printf("r LVal\n");}
        ;

PrimaryExp  : "(" Exp ")" {printf("r PrimaryExp\n");}
            | LVal {printf("r PrimaryExp\n");}
            | Number {printf("r PrimaryExp\n");}
            ;

Number  : INT_CONST {printf("r Number\n");}
        ;

UnaryExp    : PrimaryExp {printf("r UnaryExp\n");}
            | IDENT "(" FuncRParams ")" {printf("r UnaryExp\n");}
            | IDENT "(" ")" {printf("r UnaryExp\n");}
            | UnaryOp UnaryExp {printf("r UnaryExp\n");}
            ;

UnaryOp : "+" {printf("r UnaryOp\n");}
        | "-" {printf("r UnaryOp\n");}
        | "!" {printf("r UnaryOp\n");}
        ;

FuncRParams : Exp {printf("r FuncRParams\n");}
            | FuncRParams "," Exp {printf("r FuncRParams\n");}
            ;

MulExp  : UnaryExp {printf("r MulExp\n");}
        | MulExp "*" UnaryExp {printf("r MulExp\n");}
        | MulExp "/" UnaryExp {printf("r MulExp\n");}
        | MulExp "%" UnaryExp {printf("r MulExp\n");}
        ;

AddExp  : MulExp {printf("r AddExp\n");}
        | AddExp "+" MulExp {printf("r AddExp\n");}
        | AddExp "-" MulExp {printf("r AddExp\n");}
        ;

RelExp  : AddExp {printf("r RelExp\n");}
        | RelExp "<" AddExp {printf("r RelExp\n");}
        | RelExp ">" AddExp {printf("r RelExp\n");}
        | RelExp "<=" AddExp {printf("r RelExp\n");}
        | RelExp ">=" AddExp {printf("r RelExp\n");}
        ;

EqExp   : RelExp {printf("r EqExp\n");}
        | EqExp "==" RelExp {printf("r EqExp\n");}
        | EqExp "!=" RelExp {printf("r EqExp\n");}
        ;

LAndExp : EqExp {printf("r LAndExp\n");}
        | LAndExp "&&" EqExp {printf("r LAndExp\n");}
        ;

LOrExp  : LAndExp {printf("r LOrExp\n");}
        | LOrExp "||" LAndExp {printf("r LOrExp\n");}
        ;

ConstExp    : AddExp {printf("r ConstExp\n");}
            ;

%%

int yywrap(){
    return 1;
}