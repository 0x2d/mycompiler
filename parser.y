%{
    #include<stdio.h>
    #include"ast.h"
    #include"symtable.h"
    #define debug_parser_y 0
    extern FILE *yyin;
    extern FILE *yyout;
    extern int yylex();
    extern int yylineno;
    extern char *yytext;
    extern class AST *root;
    extern class TABLE *root_symtable;
    extern class TABLE *symtable_ptr;
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
                #if debug_parser_y
                    printf("r CompUnit\n");
                #endif
                $1->son.push_back($2);
                $$ = $1;
            }
            | CompUnit FuncDef {
                #if debug_parser_y
                    printf("r CompUnit\n");
                #endif
                $1->son.push_back($2);
                $$ = $1;
            }
            | Decl {
                #if debug_parser_y
                    printf("r CompUnit\n");
                #endif
                root = new AST(_CompUnit);
                root->son.push_back($1);
                $$ = root;
            }
            | FuncDef {
                #if debug_parser_y
                    printf("r CompUnit\n");
                #endif
                root = new AST(_CompUnit);
                root->son.push_back($1);
                $$ = root;
            }
            ;

Decl    : ConstDecl {
            #if debug_parser_y
                printf("r Decl\n");
            #endif
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VarDecl {
            #if debug_parser_y
                printf("r Decl\n");
            #endif
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDecl   : CONST BType ConstDef_temp ';' {
                #if debug_parser_y
                    printf("r ConstDecl\n");
                #endif
                AST *temp = new AST(_ConstDecl);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

ConstDef_temp   : ConstDef {
                    #if debug_parser_y
                        printf("r ConstDef_temp\n");
                    #endif
                    AST *temp = new AST(_ConstDef_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | ConstDef_temp ',' ConstDef {
                    #if debug_parser_y
                        printf("r ConstDef_temp\n");
                    #endif
                    $1->son.push_back($3);
                    $$ = $1;
                }
                ;

BType   : INT {
            #if debug_parser_y
                printf("r BType\n");
            #endif
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VOID {
            #if debug_parser_y
                printf("r BType\n");
            #endif
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDef    : IDENT ConstExp_temp '=' ConstInitVal {
                #if debug_parser_y
                    printf("r ConstDef\n");
                #endif
                $1->entry = new ENTRY_VAL($1->id, symtable_ptr);
                ((ENTRY_VAL *)$1->entry)->isConst = true;
                AST *temp = new AST(_ConstDef);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                temp->son.push_back($4);
                $$ = temp;
            }
            ;

ConstExp_temp   : ConstExp_temp '[' ConstExp ']' {
                    #if debug_parser_y
                        printf("r ConstExp_temp\n");
                    #endif
                    $1->son.push_back($3);
                    $$ = $1;
                }
                | {
                    #if debug_parser_y
                        printf("r ConstExp_temp\n");
                    #endif
                    AST *temp = new AST(_ConstExp_temp);
                    $$ = temp;
                }
                ;

ConstInitVal    : ConstExp {
                    #if debug_parser_y
                        printf("r ConstInitVal\n");
                    #endif
                    AST *temp = new AST(_ConstInitVal);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | '{' '}' {
                    #if debug_parser_y
                        printf("r ConstInitVal\n");
                    #endif
                    AST *temp = new AST(_ConstInitVal);
                    $$ = temp;
                }
                | '{' ConstInitVal_temp '}' {
                    #if debug_parser_y
                        printf("r ConstInitVal\n");
                    #endif
                    AST *temp = new AST(_ConstInitVal);
                    temp->son = $2->son;    //copy vector
                    delete $2;
                    $$ = temp;
                }
                ;

ConstInitVal_temp   : ConstInitVal {
                        #if debug_parser_y
                            printf("r ConstInitVal_temp\n");
                        #endif
                        AST *temp = new AST(_ConstInitVal_temp);
                        temp->son.push_back($1);
                        $$ = temp;
                    }
                    | ConstInitVal_temp ',' ConstInitVal {
                        #if debug_parser_y
                            printf("r ConstInitVal_temp\n");
                        #endif
                        $1->son.push_back($3);
                        $$ = $1;
                    }
                    ;

VarDecl : BType VarDef_temp ';' {
            #if debug_parser_y
                printf("r VarDecl\n");
            #endif
            AST *temp = new AST(_VarDecl);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        ;

VarDef_temp : VarDef {
                #if debug_parser_y
                    printf("r VarDef_temp\n");
                #endif
                AST *temp = new AST(_VarDef_temp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | VarDef_temp ',' VarDef {
                #if debug_parser_y
                    printf("r VarDef_temp\n");
                #endif
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

VarDef  : IDENT ConstExp_temp {
            #if debug_parser_y
                printf("r VarDef\n");
            #endif
            $1->entry = new ENTRY_VAL($1->id, symtable_ptr);
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        | IDENT ConstExp_temp '=' InitVal {
            #if debug_parser_y
                printf("r VarDef\n");
            #endif
            $1->entry = new ENTRY_VAL($1->id, symtable_ptr);
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            temp->son.push_back($4);
            $$ = temp;
        }
        ;

InitVal : Exp {
            #if debug_parser_y
                printf("r InitVal\n");
            #endif
            AST *temp = new AST(_InitVal);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '{' '}' {
            #if debug_parser_y
                printf("r InitVal\n");
            #endif
            AST *temp = new AST(_InitVal);
            $$ = temp;
        }
        | '{' InitVal_temp '}' {
            #if debug_parser_y
                printf("r InitVal\n");
            #endif
            AST *temp = new AST(_InitVal);
            temp->son = $2->son;
            delete $2;
            $$ = temp;
        }
        ;

InitVal_temp    : InitVal {
                    #if debug_parser_y
                        printf("r InitVal_temp\n");
                    #endif
                    AST *temp = new AST(_InitVal_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | InitVal_temp ',' InitVal {
                    #if debug_parser_y
                        printf("r InitVal_temp\n");
                    #endif
                    $1->son.push_back($3);
                    $$ = $1;
                }
                ;

FuncDef : BType IDENT '(' FuncFParams ')' {
            symtable_ptr = new TABLE("func", symtable_ptr);
        }
        Block {
            #if debug_parser_y
                printf("r FuncDef\n");
            #endif
            //
            TABLE *table_temp = symtable_ptr;
            symtable_ptr = symtable_ptr->father;
            $2->entry = new ENTRY_FUNC($2->id, symtable_ptr);
            table_temp->space = $2->id;
            ((ENTRY_FUNC *)$2->entry)->symtable = table_temp;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($5);
            temp->son.push_back($7);
            $$ = temp;
        }
        | BType IDENT '(' ')' {
            symtable_ptr = new TABLE("func", symtable_ptr);
        } 
        Block {
            #if debug_parser_y
                printf("r FuncDef\n");
            #endif
            TABLE *table_temp = symtable_ptr;
            symtable_ptr = symtable_ptr->father;
            $2->entry = new ENTRY_FUNC($2->id, symtable_ptr);
            table_temp->space = $2->id;
            ((ENTRY_FUNC *)$2->entry)->symtable = table_temp;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($6);
            $$ = temp;
        }
        ;

FuncFParams : FuncFParam {
                #if debug_parser_y
                    printf("r FuncFParams\n");
                #endif
                AST *temp = new AST(_FuncFParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncFParams ',' FuncFParam {
                #if debug_parser_y
                    printf("r FuncFParams\n");
                #endif
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

FuncFParam  : BType IDENT '[' ']' ConstExp_temp {
                #if debug_parser_y
                    printf("r FuncFParam\n");
                #endif
                $2->entry = new ENTRY_VAL($2->id, symtable_ptr);
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($5);
                $$ = temp;
            }
            | BType IDENT {
                #if debug_parser_y
                    printf("r FuncFParam\n");
                #endif
                $2->entry = new ENTRY_VAL($2->id, symtable_ptr);
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

Block   : '{' BlockItem_temp '}' {
            #if debug_parser_y
                printf("r Block\n");
            #endif
            AST *temp = new AST(_Block);
            temp->son = $2->son;
            delete $2;
            $$ = temp;
        }
        ;

BlockItem_temp  : BlockItem_temp BlockItem {
                    #if debug_parser_y
                        printf("r BlockItem_temp\n");
                    #endif
                    $1->son.push_back($2);
                    $$ = $1;
                }
                | {
                    #if debug_parser_y
                        printf("r BlockItem_temp\n");
                    #endif
                    AST *temp = new AST(_BlockItem_temp);
                    $$ = temp;
                }
                ;

BlockItem   : Decl {
                #if debug_parser_y
                    printf("r BlockItem\n");
                #endif
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            | Stmt {
                #if debug_parser_y
                    printf("r BlockItem\n");
                #endif
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

Stmt    : LVal '=' Exp ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            $$ = temp;
        }
        | Exp ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            $$ = temp;
        }
        | {
            symtable_ptr = new TABLE("block", symtable_ptr);
        }
        Block {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            symtable_ptr = symtable_ptr->father;
            AST *temp = new AST(_Stmt);
            temp->son.push_back($2);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt ELSE Stmt {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            temp->son.push_back($6);
            temp->son.push_back($7);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | WHILE '(' Cond ')' Stmt {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | BREAK ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | CONTINUE ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | RETURN Exp ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        | RETURN ';' {
            #if debug_parser_y
                printf("r Stmt\n");
            #endif
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

Exp : AddExp {
        #if debug_parser_y
            printf("r Exp\n");
        #endif
        AST *temp = new AST(_Exp);
        temp->son.push_back($1);
        $$ = temp;
    }
    ;

Cond    : LOrExp {
            #if debug_parser_y
                printf("r Cond\n");
            #endif
            AST *temp = new AST(_Cond);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

LVal    : IDENT {
            #if debug_parser_y
                printf("r LVal\n");
            #endif
            if(symtable_ptr->isSame(true,$1->id,true)){
                $1->entry = symtable_ptr->FindAndReturn(true,$1->id);
            } else{
                yyerror("cite non-decleared variable\n");
            }
            AST *temp = new AST(_LVal);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LVal '[' Exp ']' {
            #if debug_parser_y
                printf("r LVal\n");
            #endif
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

PrimaryExp  : '(' Exp ')' {
                #if debug_parser_y
                    printf("r PrimaryExp\n");
                #endif
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($2);
                $$ = temp;
            }
            | LVal {
                #if debug_parser_y
                    printf("r PrimaryExp\n");
                #endif
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | INT_CONST {
                #if debug_parser_y
                    printf("r PrimaryExp\n");
                #endif
                AST *temp = new AST(_PrimaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

UnaryExp    : PrimaryExp {
                #if debug_parser_y
                    printf("r UnaryExp\n");
                #endif
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | IDENT '(' FuncRParams ')' {
                #if debug_parser_y
                    printf("r UnaryExp\n");
                #endif
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | IDENT '(' ')' {
                #if debug_parser_y
                    printf("r UnaryExp\n");
                #endif
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | UnaryOp UnaryExp {
                #if debug_parser_y
                    printf("r UnaryExp\n");
                #endif
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

UnaryOp : '+' {
            #if debug_parser_y
                printf("r UnaryOp\n");
            #endif
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '-' {
            #if debug_parser_y
                printf("r UnaryOp\n");
            #endif
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '!' {
            #if debug_parser_y
                printf("r UnaryOp\n");
            #endif
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

FuncRParams : Exp {
                #if debug_parser_y
                    printf("r FuncRParams\n");
                #endif
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncRParams ',' Exp {
                #if debug_parser_y
                    printf("r FuncRParams\n");
                #endif
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

MulExp  : UnaryExp {
            #if debug_parser_y
                printf("r MulExp\n");
            #endif
            AST *temp = new AST(_MulExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | MulExp '*' UnaryExp {
            #if debug_parser_y
                printf("r MulExp\n");
            #endif
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | MulExp '/' UnaryExp {
            #if debug_parser_y
                printf("r MulExp\n");
            #endif
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | MulExp '%' UnaryExp {
            #if debug_parser_y
                printf("r MulExp\n");
            #endif
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

AddExp  : MulExp {
            #if debug_parser_y
                printf("r AddExp\n");
            #endif
            AST *temp = new AST(_AddExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | AddExp '+' MulExp {
            #if debug_parser_y
                printf("r AddExp\n");
            #endif
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | AddExp '-' MulExp {
            #if debug_parser_y
                printf("r AddExp\n");
            #endif
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

RelExp  : AddExp {
            #if debug_parser_y
                printf("r RelExp\n");
            #endif
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | RelExp '<' AddExp {
            #if debug_parser_y
                printf("r RelExp\n");
            #endif
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp '>' AddExp {
            #if debug_parser_y
                printf("r RelExp\n");
            #endif
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp LE AddExp {
            #if debug_parser_y
                printf("r RelExp\n");
            #endif
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | RelExp GE AddExp {
            #if debug_parser_y
                printf("r RelExp\n");
            #endif
            AST *temp = new AST(_RelExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

EqExp   : RelExp {
            #if debug_parser_y
                printf("r EqExp\n");
            #endif
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | EqExp EQ RelExp {
            #if debug_parser_y
                printf("r EqExp\n");
            #endif
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        | EqExp NE RelExp {
            #if debug_parser_y
                printf("r EqExp\n");
            #endif
            AST *temp = new AST(_EqExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

LAndExp : EqExp {
            #if debug_parser_y
                printf("r LAndExp\n");
            #endif
            AST *temp = new AST(_LAndExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LAndExp AND EqExp {
            #if debug_parser_y
                printf("r LAndExp\n");
            #endif
            AST *temp = new AST(_LAndExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

LOrExp  : LAndExp {
            #if debug_parser_y
                printf("r LOrExp\n");
            #endif
            AST *temp = new AST(_LOrExp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | LOrExp OR LAndExp {
            #if debug_parser_y
                printf("r LOrExp\n");
            #endif
            AST *temp = new AST(_LOrExp);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($3);
            $$ = temp;
        }
        ;

ConstExp    : AddExp {
                #if debug_parser_y
                    printf("r ConstExp\n");
                #endif
                AST *temp = new AST(_ConstExp);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

%%