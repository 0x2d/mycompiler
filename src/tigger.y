%{
    #include<stdio.h>
    #include<string.h>
    #include"ast_tigger.h"
    
    extern int tiggerlex();
    extern char *tiggertext;
    extern AST *root_tigger;
    
    void yyerror(char *str){
        printf("In %s : %s\n",tiggertext, str);
    };
%}

%define api.prefix {tigger}

%union{
    class AST *ast;
}

%token <ast>  IF RETURN VARIABLE NUM MALLOC END FUNCTION LOGICOP OP GOTO LABEL CALL STORE LOAD LOADADDR Reg
%type <ast> Program GlobalVarDecl FunctionDef FunctionHeader FunctionEnd
%type <ast> Expressions Expression BinOp

%%

Program : GlobalVarDecl {
            root_tigger = new AST(_Program);
            root_tigger->son.push_back($1);
            $$ = root_tigger;
        }
        | FunctionDef {
            root_tigger = new AST(_Program);
            root_tigger->son.push_back($1);
            $$ = root_tigger;
        }
        | Program GlobalVarDecl {
            $1->son.push_back($2);
            $$ = $1;
        }
        | Program FunctionDef {
            $1->son.push_back($2);
            $$ = $1;
        };

GlobalVarDecl   : VARIABLE '=' NUM {
                    AST *temp = new AST(_GlobalVarDecl);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    $$ = temp;
                }
                | VARIABLE '=' MALLOC NUM {
                    AST *temp = new AST(_GlobalVarDecl);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    temp->son.push_back($4);
                    $$ = temp;
                };

FunctionDef : FunctionHeader Expressions FunctionEnd {
                AST *temp = new AST(_FunctionDef);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            };

FunctionHeader  : FUNCTION '[' NUM ']' '[' NUM ']' {
                AST *temp = new AST(_FunctionHeader);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($6);
                $$ = temp;
            };

Expressions : Expressions Expression {
                $1->son.push_back($2);
                $$ = $1;
            }
            | {
                AST *temp = new AST(_Expressions);
                $$ = temp;
            };

FunctionEnd : END FUNCTION {
                AST *temp = new AST(_FunctionEnd);
                $$ = temp;
            };

Expression  : Reg '=' Reg BinOp Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                temp->son.push_back($5);
                $$ = temp;
            }
            | Reg '=' Reg BinOp NUM {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                temp->son.push_back($5);
                $$ = temp;
            }
            | Reg '=' OP Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                $$ = temp;
            }
            | Reg '=' Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | Reg '=' NUM {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | Reg '[' NUM ']' '=' Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($6);
                $$ = temp;
            }
            | Reg '=' Reg '[' NUM ']' {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($5);
                $$ = temp;
            }
            | IF Reg LOGICOP Reg GOTO LABEL {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                temp->son.push_back($4);
                temp->son.push_back($5);
                temp->son.push_back($6);
                $$ = temp;
            }
            | GOTO LABEL {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            | LABEL ':' {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                $$ = temp;
            }
            | CALL FUNCTION {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            | RETURN {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                $$ = temp;
            }
            | STORE Reg NUM {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            | LOAD NUM Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            | LOAD VARIABLE Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            | LOADADDR NUM Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            | LOADADDR VARIABLE Reg {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            };
BinOp   : OP {
            AST *temp = new AST(_BinOp);
            temp->op = $1->op;
            temp->son.push_back($1);
            $$ = temp;
        }
        | LOGICOP {
            AST *temp = new AST(_BinOp);
            temp->op = $1->op;
            temp->son.push_back($1);
            $$ = temp;
        };

%%
