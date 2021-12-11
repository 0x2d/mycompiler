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
%type <ast> CompUnit Decl ConstDecl ConstDef_temp BType ConstDef ConstExp_temp ConstInitVal
%type <ast> ConstInitVal_temp VarDecl VarDef_temp VarDef InitVal InitVal_temp FuncDef FuncFParams FuncFParam
%type <ast> Block BlockItem_temp BlockItem Stmt Exp Cond LVal PrimaryExp UnaryExp UnaryOp FuncRParams
%type <ast> MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp

%%

CompUnit    : CompUnit Decl {
                printf("r CompUnit\n");
                $1->son.push_back($2);
                $$ = $1;
            }
            | CompUnit FuncDef {
                printf("r CompUnit\n");
                $1->son.push_back($2);
                $$ = $1;
            }
            | Decl {
                printf("r CompUnit\n");
                root = new AST(_CompUnit);
                root->son.push_back($1);
                $$ = root;
            }
            | FuncDef {
                printf("r CompUnit\n");
                root = new AST(_CompUnit);
                root->son.push_back($1);
                $$ = root;
            }
            ;

Decl    : ConstDecl {
            printf("r Decl\n");
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VarDecl {
            printf("r Decl\n");
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDecl   : CONST BType ConstDef_temp ';' {
                printf("r ConstDecl\n");
                AST *temp = new AST(_ConstDecl);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

ConstDef_temp   : ConstDef {
                    printf("r ConstDef_temp\n");
                    AST *temp = new AST(_ConstDef_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | ConstDef_temp ',' ConstDef {
                    printf("r ConstDef_temp\n");
                    AST *temp = new AST(_ConstDef_temp);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    $$ = temp;
                }
                ;

BType   : INT {
            printf("r BType\n");
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VOID {
            printf("r BType\n");
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDef    : IDENT ConstExp_temp '=' ConstInitVal {
                printf("r ConstDef\n");
                AST *temp = new AST(_ConstDef);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                temp->son.push_back($4);
                $$ = temp;
            }
            ;

ConstExp_temp   : ConstExp_temp '[' ConstExp ']' {
                    printf("r ConstExp_temp\n");
                    $1->son.push_back($3);
                    $$ = $1;
                }
                | {
                    printf("r ConstExp_temp\n");
                    AST *temp = new AST(_ConstExp_temp);
                    $$ = temp;
                }
                ;

ConstInitVal    : ConstExp {
                    printf("r ConstInitVal\n");
                    AST *temp = new AST(_ConstInitVal);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | '{' '}' {
                    printf("r ConstInitVal\n");
                    AST *temp = new AST(_ConstInitVal);
                    $$ = temp;
                }
                | '{' ConstInitVal_temp '}' {
                    printf("r ConstInitVal\n");
                    AST *temp = new AST(_ConstInitVal);
                    temp->son.push_back($2);
                    $$ = temp;
                }
                ;

ConstInitVal_temp   : ConstInitVal {
                        printf("r ConstInitVal_temp\n");
                        AST *temp = new AST(_ConstInitVal_temp);
                        temp->son.push_back($1);
                        $$ = temp;
                    }
                    | ConstInitVal_temp ',' ConstInitVal {
                        printf("r ConstInitVal_temp\n");
                        AST *temp = new AST(_ConstInitVal_temp);
                        temp->son.push_back($1);
                        temp->son.push_back($3);
                        $$ = temp;
                    }
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
            | VarDef_temp ',' VarDef {
                printf("r VarDef_temp\n");
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

VarDef  : IDENT ConstExp_temp {
            printf("r VarDef\n");
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
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
        | '{' '}' {
            printf("r InitVal\n");
            AST *temp = new AST(_InitVal);
            $$ = temp;
        }
        | '{' InitVal_temp '}' {
            printf("r InitVal\n");
            AST *temp = new AST(_InitVal);
            temp->son.push_back($2);
            $$ = temp;
        }
        ;

InitVal_temp    : InitVal {
                    printf("r InitVal_temp\n");
                    AST *temp = new AST(_InitVal_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | InitVal_temp ',' InitVal {
                    printf("r InitVal_temp\n");
                    AST *temp = new AST(_InitVal_temp);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    $$ = temp;
                }
                ;

FuncDef : BType IDENT '(' FuncFParams ')' Block {
            printf("r FuncDef\n");
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($4);
            temp->son.push_back($6);
            $$ = temp;
        }
        | BType IDENT '(' ')' Block {
            printf("r FuncDef\n");
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($5);
            $$ = temp;
        }
        ;

FuncFParams : FuncFParam {
                printf("r FuncFParams\n");
                AST *temp = new AST(_FuncFParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncFParams ',' FuncFParam {
                printf("r FuncFParams\n");
                AST *temp = new AST(_FuncFParams);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

FuncFParam  : BType IDENT '[' ']' ConstExp_temp {
                printf("r FuncFParam\n");
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($5);
                $$ = temp;
            }
            | BType IDENT {
                printf("r FuncFParam\n");
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

Block   : '{' BlockItem_temp '}' {
            printf("r Block\n");
            AST *temp = new AST(_Block);
            temp->son.push_back($2);
            $$ = temp;
        }
        ;

BlockItem_temp  : BlockItem_temp BlockItem {
                    printf("r BlockItem_temp\n");
                    AST *temp = new AST(_BlockItem_temp);
                    temp->son.push_back($1);
                    temp->son.push_back($2);
                    $$ = temp;
                }
                | {
                    printf("r BlockItem_temp\n");
                    AST *temp = new AST(_BlockItem_temp);
                    $$ = temp;
                }
                ;

BlockItem   : Decl {
                printf("r BlockItem\n");
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            | Stmt {
                printf("r BlockItem\n");
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

Stmt    : LVal '=' Exp ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            $$ = temp;
        }
        | Exp ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            $$ = temp;
        }
        | Block {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt ELSE Stmt {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            temp->son.push_back($6);
            temp->son.push_back($7);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | WHILE '(' Cond ')' Stmt {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | BREAK ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | CONTINUE ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | RETURN Exp ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        | RETURN ';' {
            printf("r Stmt\n");
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

Exp : AddExp {
        printf("r Exp\n");
        AST *temp = new AST(_Exp);
        temp->son.push_back($1);
        $$ = temp;
    }
    ;

Cond    : LOrExp {
            printf("r Cond\n");
            AST *temp = new AST(_Cond);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

LVal    : IDENT {
            printf("r LVal\n");
            AST *temp = new AST(_LVal);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LVal '[' Exp ']' {
            printf("r LVal\n");
            AST *temp = new AST(_LVal);
            temp->son.push_back($1);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

PrimaryExp  : '(' Exp ')' {
                printf("r PrimaryExp\n");
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($2);
                $$ = temp;
            }
            | LVal {
                printf("r PrimaryExp\n");
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
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
            | IDENT '(' FuncRParams ')' {
                printf("r UnaryExp\n");
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | IDENT '(' ')' {
                printf("r UnaryExp\n");
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | UnaryOp UnaryExp 
                {printf("r UnaryExp\n");
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

UnaryOp : '+' {
            printf("r UnaryOp\n");
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '-' {
            printf("r UnaryOp\n");
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '!' {
            printf("r UnaryOp\n");
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

FuncRParams : Exp {
                printf("r FuncRParams\n");
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncRParams ',' Exp {
                printf("r FuncRParams\n");
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

MulExp  : UnaryExp {
            printf("r MulExp\n");
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | MulExp '*' UnaryExp {
            printf("r MulExp\n");
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | MulExp '/' UnaryExp {
            printf("r MulExp\n");
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | MulExp '%' UnaryExp {
            printf("r MulExp\n");
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

AddExp  : MulExp {
            printf("r AddExp\n");
            AST *temp = new AST(_AddExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | AddExp '+' MulExp {
            printf("r AddExp\n");
            AST *temp = new AST(_AddExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | AddExp '-' MulExp {
            printf("r AddExp\n");
            AST *temp = new AST(_AddExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

RelExp  : AddExp {
            printf("r RelExp\n");
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | RelExp '<' AddExp {
            printf("r RelExp\n");
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp '>' AddExp {
            printf("r RelExp\n");
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp LE AddExp {
            printf("r RelExp\n");
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp GE AddExp {
            printf("r RelExp\n");
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

EqExp   : RelExp {
            printf("r EqExp\n");
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | EqExp EQ RelExp {
            printf("r EqExp\n");
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | EqExp NE RelExp {
            printf("r EqExp\n");
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

LAndExp : EqExp {
            printf("r LAndExp\n");
            AST *temp = new AST(_LAndExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LAndExp AND EqExp {
            printf("r LAndExp\n");
            AST *temp = new AST(_LAndExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

LOrExp  : LAndExp {
            printf("r LOrExp\n");
            AST *temp = new AST(_LOrExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LOrExp OR LAndExp {
            printf("r LOrExp\n");
            AST *temp = new AST(_LOrExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

ConstExp    : AddExp {
                printf("r ConstExp\n");
                AST *temp = new AST(_ConstExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

%%