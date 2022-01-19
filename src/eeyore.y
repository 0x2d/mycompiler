%{
    #include<stdio.h>
    #include<string.h>
    #include"ast_eeyore.h"

    extern int eeyorelex();
    extern char *eeyoretext;
    extern ENTRY *findvar(FUNC *func, std::string id);
    extern AST *root_eeyore;
    extern std::vector<ENTRY *>global_table;
    extern std::vector<FUNC *>functions;
    extern FUNC *func_ptr;
    
    void yyerror(char *str){
        printf("In %s : %s\n", eeyoretext, str);
    };
    
    int v_i = 0;
%}

%define api.prefix {eeyore}

%union{
    class AST *ast;
}

%token <ast>  IF RETURN VAR NUM SYMBOL END FUNCTION LOGICOP OP GOTO LABEL PARAM CALL
%type <ast> Program Declaration Initialization FunctionDef FunctionHeader Statements FunctionEnd
%type <ast> Statement Expression RightValue BinOp

%%

Program : Declaration {
            root_eeyore = new AST(_Program);
            root_eeyore->son.push_back($1);
            $$ = root_eeyore;
        }
        | Initialization {
            root_eeyore = new AST(_Program);
            root_eeyore->son.push_back($1);
            $$ = root_eeyore;
        }
        | FunctionDef {
            root_eeyore = new AST(_Program);
            root_eeyore->son.push_back($1);
            $$ = root_eeyore;
        }
        | Program Declaration {
            $1->son.push_back($2);
            $$ = $1;
        }
        | Program Initialization {
            $1->son.push_back($2);
            $$ = $1;
        }
        | Program FunctionDef{
            $1->son.push_back($2);
            $$ = $1;
        };

Declaration : VAR NUM SYMBOL {
                if(!func_ptr){
                    ENTRY *entry = new ENTRY($3->id);
                    entry->global = true;
                    entry->array = true;
                    entry->stack = v_i;
                    v_i++;
                    entry->size = $2->val;
                    entry->init = new int[entry->size/4];
                    memset(entry->init,0,entry->size);
                    global_table.push_back(entry);
                    $3->entry = entry;
                } else{
                    ENTRY *entry = new ENTRY($3->id);
                    entry->array = true;
                    entry->size = $2->val;
                    entry->stack = func_ptr->stack_size;
                    func_ptr->table.push_back(entry);
                    func_ptr->stack_size += entry->size/4;
                }
                AST *temp = new AST(_Declaration);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            }
            | VAR SYMBOL{
                if(!func_ptr){
                    ENTRY *entry = new ENTRY($2->id);
                    entry->global = true;
                    entry->stack = v_i;
                    v_i++;
                    entry->val = 0;
                    global_table.push_back(entry);
                    $2->entry = entry;
                } else{
                    ENTRY *entry = new ENTRY($2->id);
                    entry->stack = func_ptr->stack_size;
                    func_ptr->table.push_back(entry);
                    func_ptr->stack_size++;
                }
                AST *temp = new AST(_Declaration);
                temp->son.push_back($2);
                $$ = temp;
            };

Initialization  : SYMBOL '=' NUM {
                    ENTRY *entry = findvar(nullptr,$1->id);
                    entry->val = $3->val;
                    AST *temp = new AST(_Initialization);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    $$ = temp;
                }
                | SYMBOL '[' NUM ']' '=' NUM{
                    ENTRY *entry = findvar(nullptr,$1->id);
                    entry->init[$3->val/4] = $6->val;
                    entry->isinit = true;
                    AST *temp = new AST(_Initialization);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    temp->son.push_back($6);
                    $$ = temp;
                };

FunctionDef : FunctionHeader Statements FunctionEnd{
                AST *temp = new AST(_FunctionDef);
                temp->son.push_back($1);
                temp->son.push_back($2);
                temp->son.push_back($3);
                $$ = temp;
            };

FunctionHeader  : FUNCTION '[' NUM ']'{
                    func_ptr = new FUNC($1->id, $3->val);
                    functions.push_back(func_ptr);
                    for(int i=0;i<func_ptr->pnum;i++){
                        ENTRY *entry = new ENTRY("p"+std::to_string(i));
                        entry->stack = func_ptr->stack_size;
                        func_ptr->table.push_back(entry);
                        func_ptr->stack_size++;
                    }
                    AST *temp = new AST(_FunctionHeader);
                    temp->son.push_back($1);
                    temp->son.push_back($3);
                    $$ = temp;
                };

Statements  : Statements Statement {
                $1->son.push_back($2);
                $$ = $1;
            }
            | {
                AST *temp = new AST(_Statements);
                $$ = temp;
            };

FunctionEnd : END FUNCTION {
                AST *temp = new AST(_FunctionEnd);
                $$ = temp;
            };

Statement   : Expression {
                AST *temp = new AST(_Statement);
                temp->son.push_back($1);
                $$ = temp;
            }
            | Declaration {
                AST *temp = new AST(_Statement);
                temp->son.push_back($1);
                $$ = temp;
            };

Expression  : SYMBOL '=' RightValue BinOp RightValue {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                temp->son.push_back($5);
                $$ = temp;
            }
            | SYMBOL '=' OP RightValue {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                $$ = temp;
            }
            | SYMBOL '=' RightValue {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                $$ = temp;
            }
            | SYMBOL '[' RightValue ']' '=' RightValue {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($6);
                $$ = temp;
            }
            | SYMBOL '=' SYMBOL '[' RightValue ']' {
                $1->entry = findvar(func_ptr,$1->id);
                $3->entry = findvar(func_ptr,$3->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($5);
                $$ = temp;
            }
            | IF RightValue LOGICOP RightValue GOTO LABEL {
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
            | PARAM RightValue {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            | CALL FUNCTION {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            | SYMBOL '=' CALL FUNCTION {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($3);
                temp->son.push_back($4);
                $$ = temp;
            }
            | RETURN RightValue {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                temp->son.push_back($2);
                $$ = temp;
            }
            | RETURN {
                AST *temp = new AST(_Expression);
                temp->son.push_back($1);
                $$ = temp;
            };

RightValue  : SYMBOL {
                $1->entry = findvar(func_ptr,$1->id);
                AST *temp = new AST(_RightValue);
                temp->son.push_back($1);
                $$ = temp;
            }
            | NUM {
                AST *temp = new AST(_RightValue);
                temp->son.push_back($1);
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
