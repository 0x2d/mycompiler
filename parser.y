%{
    #include<stdio.h>
    #include"ast.h"
    extern FILE *yyin;
    extern FILE *yyout;
    extern int yylex();
    extern int yylineno;
    extern char *yytext;
    extern class AST *root;
    void yyerror(char *str){
        printf("LINE %d in %s : %s\n",yylineno, yytext, str);
    };
%}

%union{
    class AST *ast; //class关键字必需添加
}

%token <ast> CONST INT VOID IF ELSE WHILE BREAK CONTINUE RETURN
%token <ast> '=' '>' '<' '+' '-' '*' '/' '%' '!'
%token <ast> '(' ')' '[' ']' '{' '}' ';' ','
%token <ast> LE GE EQ NE AND OR
%token <ast> IDENT
%token <ast> INT_CONST
%type <ast> PROG CompUnit Decl ConstDecl ConstDef_temp BType ConstDef ConstExp_temp ConstInitVal
%type <ast> ConstInitVal_temp VarDecl VarDef_temp VarDef InitVal InitVal_temp FuncDef FuncFParams FuncFParam
%type <ast> Block BlockItem_temp BlockItem Stmt Exp Cond LVal PrimaryExp UnaryExp UnaryOp FuncRParams
%type <ast> MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp

%%

PROG    : CompUnit {
            printf("r, PROG\n");
            root = new AST(_PROG);
            root->son.push_back($1);
        }

CompUnit    : CompUnit Decl {printf("r CompUnit\n");}
            | CompUnit FuncDef {printf("r CompUnit\n");}
            | Decl {
                printf("r CompUnit\n");
                AST *temp = new AST(_CompUnit);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncDef {printf("r CompUnit\n");}
            ;

Decl    : ConstDecl {printf("r Decl\n");}
        | VarDecl {
            printf("r Decl\n");
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDecl   : CONST BType ConstDef_temp ';' {printf("r ConstDecl\n");}
            ;

ConstDef_temp   : ConstDef {printf("r ConstDef_temp\n");}
                | ConstDef_temp ',' ConstDef {printf("r ConstDef_temp\n");}
                ;

BType   : INT {
            printf("r BType\n");
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VOID {printf("r BType\n");}
        ;

ConstDef    : IDENT ConstExp_temp '=' ConstInitVal {printf("r ConstDef\n");}
            ;

ConstExp_temp   : ConstExp_temp '[' ConstExp ']' {printf("r ConstExp_temp\n");}
                | {
                    printf("r ConstExp_temp\n");
                    AST *temp = new AST(_ConstExp_temp);
                    $$ = temp;
                }
                ;

ConstInitVal    : ConstExp {printf("r ConstInitVal\n");}
                | '{' '}' {printf("r ConstInitVal\n");}
                | '{' ConstInitVal_temp '}' {printf("r ConstInitVal\n");}
                ;

ConstInitVal_temp   : ConstInitVal {printf("r ConstInitVal_temp\n");}
                    | ConstInitVal_temp ',' ConstInitVal {printf("r ConstInitVal_temp\n");}
                    ;

VarDecl : BType VarDef_temp ';' {
            printf("r VarDecl\n");
            AST *temp = new AST(_VarDecl);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        ;

VarDef_temp : VarDef {
                printf("r VarDef_temp\n");
                AST *temp = new AST(_VarDef_temp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | VarDef_temp ',' VarDef {printf("r VarDef_temp\n");}
            ;

VarDef  : IDENT ConstExp_temp {printf("r VarDef\n");}
        | IDENT ConstExp_temp '=' InitVal {
            printf("r VarDef\n");
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            temp->son.push_back($4);
            $$ = temp;
        }
        ;

InitVal : Exp {
            printf("r InitVal\n");
            AST *temp = new AST(_InitVal);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '{' '}' {printf("r InitVal\n");}
        | '{' InitVal_temp '}' {printf("r InitVal\n");}
        ;

InitVal_temp    : InitVal {printf("r InitVal_temp\n");}
                | InitVal_temp ',' InitVal {printf("r InitVal_temp\n");}
                ;

FuncDef : BType IDENT '(' FuncFParams ')' Block {printf("r FuncDef\n");}
        | BType IDENT '(' ')' Block {printf("r FuncDef\n");}
        ;

FuncFParams : FuncFParam {printf("r FuncFParams\n");}
            | FuncFParams ',' FuncFParam {printf("r FuncFParams\n");}
            ;

FuncFParam  : BType IDENT '[' ']' ConstExp_temp {printf("r FuncFParam\n");}
            | BType IDENT {printf("r FuncFParam\n");}
            ;

Block   : '{' BlockItem_temp '}' {printf("r Block\n");}
        ;

BlockItem_temp  : BlockItem_temp BlockItem {printf("r BlockItem_temp\n");}
                | {printf("r BlockItem_temp\n");}
                ;

BlockItem   : Decl {printf("r BlockItem\n");}
            | Stmt {printf("r BlockItem\n");}
            ;

Stmt    : LVal '=' Exp ';' {printf("r Stmt\n");}
        | Exp ';' {printf("r Stmt\n");}
        | ';' {printf("r Stmt\n");}
        | Block {printf("r Stmt\n");}
        | IF '(' Cond ')' Stmt ELSE Stmt {printf("r Stmt\n");}
        | IF '(' Cond ')' Stmt {printf("r Stmt\n");}
        | WHILE '(' Cond ')' Stmt {printf("r Stmt\n");}
        | BREAK ';' {printf("r Stmt\n");}
        | CONTINUE ';' {printf("r Stmt\n");}
        | RETURN Exp ';' {printf("r Stmt\n");}
        | RETURN ';' {printf("r Stmt\n");}
        ;

Exp : AddExp {
        printf("r Exp\n");
        AST *temp = new AST(_Exp);
        temp->son.push_back($1);
        $$ = temp;
    }
    ;

Cond    : LOrExp {printf("r Cond\n");}
        ;

LVal    : IDENT {printf("r LVal\n");}
        | LVal '[' Exp ']' {printf("r LVal\n");}
        ;

PrimaryExp  : '(' Exp ')' {printf("r PrimaryExp\n");}
            | LVal {printf("r PrimaryExp\n");}
            | INT_CONST {
                printf("r PrimaryExp\n");
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

UnaryExp    : PrimaryExp {
                printf("r UnaryExp\n");
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | IDENT '(' FuncRParams ')' {printf("r UnaryExp\n");}
            | IDENT '(' ')' {printf("r UnaryExp\n");}
            | UnaryOp UnaryExp {printf("r UnaryExp\n");}
            ;

UnaryOp : '+' {printf("r UnaryOp\n");}
        | '-' {printf("r UnaryOp\n");}
        | '!' {printf("r UnaryOp\n");}
        ;

FuncRParams : Exp {printf("r FuncRParams\n");}
            | FuncRParams ',' Exp {printf("r FuncRParams\n");}
            ;

MulExp  : UnaryExp {
            printf("r MulExp\n");
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | MulExp '*' UnaryExp {printf("r MulExp\n");}
        | MulExp '/' UnaryExp {printf("r MulExp\n");}
        | MulExp '%' UnaryExp {printf("r MulExp\n");}
        ;

AddExp  : MulExp {
            printf("r AddExp\n");
            AST *temp = new AST(_AddExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | AddExp '+' MulExp {printf("r AddExp\n");}
        | AddExp '-' MulExp {printf("r AddExp\n");}
        ;

RelExp  : AddExp {printf("r RelExp\n");}
        | RelExp '<' AddExp {printf("r RelExp\n");}
        | RelExp '>' AddExp {printf("r RelExp\n");}
        | RelExp LE AddExp {printf("r RelExp\n");}
        | RelExp GE AddExp {printf("r RelExp\n");}
        ;

EqExp   : RelExp {printf("r EqExp\n");}
        | EqExp EQ RelExp {printf("r EqExp\n");}
        | EqExp NE RelExp {printf("r EqExp\n");}
        ;

LAndExp : EqExp {printf("r LAndExp\n");}
        | LAndExp AND EqExp {printf("r LAndExp\n");}
        ;

LOrExp  : LAndExp {printf("r LOrExp\n");}
        | LOrExp OR LAndExp {printf("r LOrExp\n");}
        ;

ConstExp    : AddExp {printf("r ConstExp\n");}
            ;

%%