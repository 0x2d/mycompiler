%{
    #include<stdio.h>
    #include<string.h>
    #include"ast_sysy.h"
    using namespace sysy;
    extern int sysylex();
    extern int lineno;
    extern char *sysytext;
    extern AST *root_sysy;
    extern TABLE *root_symtable;
    extern std::vector<TABLE *>symtable_vector;
    extern TABLE *symtable_ptr;
    
    void yyerror(char *str){
        printf("LINE %d in %s : %s\n",lineno, sysytext, str);
    };
    int NumberOfTemp;   //记录一个函数需要多少临时变量
%}

%define api.prefix {sysy}

%union{
    class sysy::AST *ast; //class关键字必需添加
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
//确保正确构建AST，创建所有符号表及条目，记录每个函数需要多少变量，记录每个变量的大小和形状，但不分配eeyore变量名

CompUnit    : CompUnit Decl {
                $1->son.push_back($2);
                $$ = $1;
            }
            | CompUnit FuncDef {
                $1->son.push_back($2);
                $$ = $1;
            }
            | Decl {
                root_sysy = new AST(_CompUnit);
                root_sysy->son.push_back($1);
                $$ = root_sysy;
            }
            | FuncDef {
                root_sysy = new AST(_CompUnit);
                root_sysy->son.push_back($1);
                $$ = root_sysy;
            }
            ;

Decl    : ConstDecl {
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VarDecl {
            AST *temp = new AST(_Decl);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDecl   : CONST BType ConstDef_temp ';' {
                AST *temp = new AST(_ConstDecl);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            ;

ConstDef_temp   : ConstDef {
                    AST *temp = new AST(_ConstDef_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | ConstDef_temp ',' ConstDef {
                    $1->son.push_back($3);
                    $$ = $1;
                }
                ;

BType   : INT {
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        | VOID {
            AST *temp = new AST(_BType);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

ConstDef    : IDENT ConstExp_temp '=' ConstInitVal {
                $1->entry = new ENTRY_VAL($1->id, symtable_ptr,$2->val*4);
                ((ENTRY_VAL *)$1->entry)->isConst = true;
                if($2->son.size() != 0){
                    ((ENTRY_VAL *)$1->entry)->isArray = true;
                    for(int i=0;i<$2->son.size();i++){
                        ((ENTRY_VAL *)$1->entry)->shape.push_back($2->son[i]->val);
                    }
                }
                //还没想好怎么处理常量数组的赋值
                if($4->son.size() == 1 && $4->son[0]->type == _ConstExp){
                    ((ENTRY_VAL *)$1->entry)->val = $4->son[0]->val;
                }
                AST *temp = new AST(_ConstDef);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($4);
                $$ = temp;
            }
            ;

ConstExp_temp   : ConstExp_temp '[' ConstExp ']' {
                    $1->son.push_back($3);
                    $1->val *= $3->val;
                    $$ = $1;
                }
                | {
                    AST *temp = new AST(_ConstExp_temp);
                    temp->val = 1;
                    $$ = temp;
                }
                ;

ConstInitVal    : ConstExp {
                    AST *temp = new AST(_ConstInitVal);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | '{' '}' {
                    AST *temp = new AST(_ConstInitVal);
                    $$ = temp;
                }
                | '{' ConstInitVal_temp '}' {
                    AST *temp = new AST(_ConstInitVal);
                    temp->son = $2->son;
                    delete $2;
                    $$ = temp;
                }
                ;

ConstInitVal_temp   : ConstInitVal {
                        AST *temp = new AST(_ConstInitVal_temp);
                        temp->son.push_back($1);
                        $$ = temp;
                    }
                    | ConstInitVal_temp ',' ConstInitVal {
                        $1->son.push_back($3);
                        $$ = $1;
                    }
                    ;

VarDecl : BType VarDef_temp ';' {
            AST *temp = new AST(_VarDecl);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        ;

VarDef_temp : VarDef {
                AST *temp = new AST(_VarDef_temp);
                temp->son.push_back($1);
                $$ = temp;
            }
            | VarDef_temp ',' VarDef {
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

VarDef  : IDENT ConstExp_temp {
            $1->entry = new ENTRY_VAL($1->id, symtable_ptr,$2->val*4);
            if($2->son.size() != 0){
                ((ENTRY_VAL *)$1->entry)->isArray = true;
                for(int i=0;i<$2->son.size();i++){
                    ((ENTRY_VAL *)$1->entry)->shape.push_back($2->son[i]->val);
                }
            }
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        | IDENT ConstExp_temp '=' InitVal {
            $1->entry = new ENTRY_VAL($1->id, symtable_ptr,$2->val*4);
            if($2->son.size() != 0){
                ((ENTRY_VAL *)$1->entry)->isArray = true;
                for(int i=0;i<$2->son.size();i++){
                    ((ENTRY_VAL *)$1->entry)->shape.push_back($2->son[i]->val);
                }
            }
            AST *temp = new AST(_VarDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($4);
            $$ = temp;
        }
        ;

InitVal : Exp {
            AST *temp = new AST(_InitVal);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '{' '}' {
            AST *temp = new AST(_InitVal);
            $$ = temp;
        }
        | '{' InitVal_temp '}' {
            AST *temp = new AST(_InitVal);
            temp->son = $2->son;
            delete $2;
            $$ = temp;
        }
        ;

InitVal_temp    : InitVal {
                    AST *temp = new AST(_InitVal_temp);
                    temp->son.push_back($1);
                    $$ = temp;
                }
                | InitVal_temp ',' InitVal {
                    $1->son.push_back($3);
                    $$ = $1;
                }
                ;

FuncDef : BType IDENT '(' {
            symtable_ptr = new TABLE("func", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
            NumberOfTemp = 0;
        } FuncFParams ')'  Block {
            symtable_ptr->space = $2->id;
            bool isreturn = ($1->son[0]->type == _INT);
            $2->entry = new ENTRY_FUNC($2->id, symtable_ptr->father,isreturn, symtable_ptr,NumberOfTemp,$5->son.size());
            NumberOfTemp = 0;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($5);
            temp->son.push_back($7);
            $$ = temp;
            symtable_ptr = symtable_ptr->father;
        }
        | BType IDENT '(' {
            symtable_ptr = new TABLE("func", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
            NumberOfTemp = 0;
        } ')'  Block {
            symtable_ptr->space = $2->id;
            bool isreturn = ($1->son[0]->type == _INT);
            $2->entry = new ENTRY_FUNC($2->id, symtable_ptr->father, isreturn, symtable_ptr,NumberOfTemp,0);
            NumberOfTemp = 0;
            AST *temp = new AST(_FuncDef);
            temp->son.push_back($1);
            temp->son.push_back($2);
            temp->son.push_back($6);
            $$ = temp;
            symtable_ptr = symtable_ptr->father;
        }
        ;

FuncFParams : FuncFParam {
                AST *temp = new AST(_FuncFParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncFParams ',' FuncFParam {
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

FuncFParam  : BType IDENT '[' ']' ConstExp_temp {
                $2->entry = new ENTRY_VAL($2->id, symtable_ptr,$5->val*4);
                ((ENTRY_VAL *)$2->entry)->shape.push_back(1);
                if($5->son.size() != 0){
                    for(int i=0;i<$5->son.size();i++){
                        ((ENTRY_VAL *)$2->entry)->shape.push_back($5->son[i]->val);
                    }
                }
                ((ENTRY_VAL *)$2->entry)->isArray = true;
                ((ENTRY_VAL *)$2->entry)->isParam = true;
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($5);
                $$ = temp;
            }
            | BType IDENT {
                $2->entry = new ENTRY_VAL($2->id, symtable_ptr,4);
                ((ENTRY_VAL *)$2->entry)->isParam = true;
                AST *temp = new AST(_FuncFParam);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

Block   : '{' BlockItem_temp '}' {
            AST *temp = new AST(_Block);
            temp->son = $2->son;
            delete $2;
            $$ = temp;
        }
        ;

BlockItem_temp  : BlockItem_temp BlockItem {
                    $1->son.push_back($2);
                    $$ = $1;
                }
                | {
                    AST *temp = new AST(_BlockItem_temp);
                    $$ = temp;
                }
                ;

BlockItem   : Decl {
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            | Stmt {
                AST *temp = new AST(_BlockItem);
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

Stmt    : LVal '=' Exp ';' {
            if($1->son.size() == 2){
                NumberOfTemp++;
            } else if($1->son.size() > 2){
                NumberOfTemp += 2;
            }
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            $$ = temp;
        }
        | Exp ';' {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | ';' {
            AST *temp = new AST(_Stmt);
            $$ = temp;
        }
        | {
            symtable_ptr = new TABLE("block", symtable_ptr);
            symtable_vector.push_back(symtable_ptr);
        } Block {
            symtable_ptr = symtable_ptr->father;
            AST *temp = new AST(_Stmt);
            temp->son.push_back($2);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt ELSE Stmt {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            temp->son.push_back($6);
            temp->son.push_back($7);
            $$ = temp;
        }
        | IF '(' Cond ')' Stmt {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | WHILE '(' Cond ')' Stmt {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($3);
            temp->son.push_back($5);
            $$ = temp;
        }
        | BREAK ';' {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | CONTINUE ';' {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        | RETURN Exp ';' {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            temp->son.push_back($2);
            $$ = temp;
        }
        | RETURN ';' {
            AST *temp = new AST(_Stmt);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

Exp : AddExp {
        AST *temp = new AST(_Exp);
        if($1->son.size() > 1){
            NumberOfTemp++;
        }
        temp->val = $1->val;
        temp->isint = $1->isint;
        temp->son.push_back($1);
        $$ = temp;
    }
    ;

Cond    : LOrExp {
            AST *temp = new AST(_Cond);
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

LVal    : IDENT {
            if(symtable_ptr->Find(true,$1->id,true)){
                $1->entry = symtable_ptr->FindAndReturn(true,$1->id);
            } else{
                yyerror("cite non-decleared variable\n");
            }
            AST *temp = new AST(_LVal);
            temp->val = ((ENTRY_VAL *)$1->entry)->val;
            temp->son.push_back($1);
            $$ = temp;
        }
        | LVal '[' Exp ']' {
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

PrimaryExp  : '(' Exp ')' {
                AST *temp = new AST(_PrimaryExp);
                temp->val = $2->val;
                temp->isint = $2->isint;
                temp->son.push_back($2);
                $$ = temp;
            }
            | LVal {
                AST *temp = new AST(_PrimaryExp);
                if($1->son.size() == 2){
                    NumberOfTemp++;
                } else if($1->son.size() > 2){
                    NumberOfTemp += 2;
                }
                temp->val = $1->val;
                temp->son.push_back($1);
                $$ = temp;
            }
            | INT_CONST {
                AST *temp = new AST(_PrimaryExp);
                temp->val = $1->val;
                temp->isint = true;
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

UnaryExp    : PrimaryExp {
                AST *temp = new AST(_UnaryExp);
                temp->val = $1->val;
                temp->isint = $1->isint;
                temp->son.push_back($1);
                $$ = temp;
            }
            | IDENT '(' FuncRParams ')' {
                NumberOfTemp++;
                AST *temp = new AST(_UnaryExp);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | IDENT '(' ')' {
                NumberOfTemp++;
                AST *temp = new AST(_UnaryExp);
                temp->lineno = lineno;
                temp->son.push_back($1);
                $$ = temp;
            }
            | UnaryOp UnaryExp {
                AST *temp = new AST(_UnaryExp);
                if($1->son[0]->op == '-'){
                    temp->val = 0-($2->val);
                    temp->isint = $2->isint;
                } else if($1->son[0]->op == '!'){
                    if($2->val != 0){
                        temp->val = 0;
                    } else{
                        temp->val = 1;
                    }
                }
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            ;

UnaryOp : '+' {
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '-' {
            NumberOfTemp++;
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        | '!' {
            NumberOfTemp++;
            AST *temp = new AST(_UnaryOp);
            temp->son.push_back($1);
            $$ = temp;
        }
        ;

FuncRParams : Exp {
                AST *temp = new AST(_FuncRParams);
                temp->son.push_back($1);
                $$ = temp;
            }
            | FuncRParams ',' Exp {
                $1->son.push_back($3);
                $$ = $1;
            }
            ;

MulExp  : UnaryExp {
            AST *temp = new AST(_MulExp);
            temp->val = $1->val;
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | MulExp '*' UnaryExp {
            $1->val = $1->val * $3->val;
            $1->isint = $1->isint && $3->isint;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | MulExp '/' UnaryExp {
            if($3->val != 0){
                $1->val = $1->val / $3->val;
                $1->isint = $1->isint && $3->isint;
            }
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | MulExp '%' UnaryExp {
            if($3->val != 0){
                $1->val = $1->val % $3->val;
                $1->isint = $1->isint && $3->isint;
            }
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

AddExp  : MulExp {
            if($1->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_AddExp);
            temp->val = $1->val;
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | AddExp '+' MulExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->val = $1->val + $3->val;
            $1->isint = $1->isint && $3->isint;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | AddExp '-' MulExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->val = $1->val - $3->val;
            $1->isint = $1->isint && $3->isint;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

RelExp  : AddExp {
            AST *temp = new AST(_RelExp);
            if($1->son.size() > 1){
                NumberOfTemp++;
            }
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | RelExp '<' AddExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | RelExp '>' AddExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | RelExp LE AddExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | RelExp GE AddExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

EqExp   : RelExp {
            if($1->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_EqExp);
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | EqExp EQ RelExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        | EqExp NE RelExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

LAndExp : EqExp {
            if($1->son.size() > 1){
                NumberOfTemp++;
            }
            AST *temp = new AST(_LAndExp);
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | LAndExp AND EqExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

LOrExp  : LAndExp {
            AST *temp = new AST(_LOrExp);
            temp->isint = $1->isint;
            temp->son.push_back($1);
            $$ = temp;
        }
        | LOrExp OR LAndExp {
            if($3->son.size() > 1){
                NumberOfTemp++;
            }
            $1->isint = false;
            $1->son.push_back($2);
            $1->son.push_back($3);
            $$ = $1;
        }
        ;

ConstExp    : AddExp {
                AST *temp = new AST(_ConstExp);
                if($1->son.size() > 1){
                    NumberOfTemp++;
                }
                temp->val = $1->val;
                temp->isint = $1->isint;
                temp->son.push_back($1);
                $$ = temp;
            }
            ;

%%