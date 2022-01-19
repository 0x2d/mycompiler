#include"ast_eeyore.h"
#include<stdio.h>
#include<string>
#include"eeyore.tab.hpp"

extern FILE *eeyorein;
extern FILE *eeyoreout;

std::vector<ENTRY *>global_table;
std::vector<class FUNC *>functions;
FUNC *func_ptr = nullptr;
AST *root_eeyore;
int param_i = 0;

static void irgen(AST *th);
static void irgen_decl(AST *th);
static void irgen_func(AST *th);
static void irgen_exp(AST *th);

ENTRY *findvar(class FUNC *func, std::string id){
    if(func){
        for(int i=0;i<func->table.size();i++){
            if(func->table[i]->id == id){
                return func->table[i];
            }
        }
    }
    for(int i=0;i<global_table.size();i++){
        if(global_table[i]->id == id){
            return global_table[i];
        }
    }
    return nullptr;
}

FUNC *findfunc(std::string id){
    for(int i=0;i<functions.size();i++){
        if(functions[i]->id == id){
            return functions[i];
        }
    }
    return nullptr;
}

static void irgen_exp(AST *th){
    if(th->son[0]->type == _RETURN && th->son.size() == 1){
        //"return";
        fprintf(eeyoreout,"  return\n");
    } else if(th->son[0]->type == _RETURN && th->son.size() == 2){
        //"return" RightValue
        if(th->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  a0 = %d\n", th->son[1]->son[0]->val);
        } else{
            int s = th->son[1]->son[0]->entry->stack;
            if(th->son[1]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d a0\n",s);
            } else{
                fprintf(eeyoreout,"  load %d a0\n",s);
            }
        }
        fprintf(eeyoreout,"  return\n");
    } else if(th->son[0]->type == _SYMBOL && th->son.size() == 2 && th->son[1]->type == _RightValue){
        //SYMBOL "=" RightValue
        if(th->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",th->son[1]->son[0]->val);
        } else{
            ENTRY *temp = th->son[1]->son[0]->entry;
            if(temp->global){
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load v%d t1\n",temp->stack);
                }
            } else{
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load %d t1\n",temp->stack);
                }
            }
        }
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = t1\n");
        } else{
            fprintf(eeyoreout,"  store t1 %d\n",val1->stack);
        }
    } else if(th->son[0]->type == _SYMBOL && th->son.size() == 3 && th->son[1]->type == _OP){
        //SYMBOL "=" OP RightValue
        if(th->son[2]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",th->son[2]->son[0]->val);
        } else{
            ENTRY *temp = th->son[2]->son[0]->entry;
            if(temp->global){
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load v%d t1\n",temp->stack);
                }
            } else{
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load %d t1\n",temp->stack);
                }
            }
        }
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = %s t1\n",th->son[1]->op.c_str());
        } else{
            fprintf(eeyoreout,"  t0 = %s t1\n",th->son[1]->op.c_str());
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(th->son[0]->type == _SYMBOL && th->son.size() == 4 && th->son[2]->type == _BinOp){
        //SYMBOL "=" RightValue BinOp RightValue
        if(th->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",th->son[1]->son[0]->val);
        } else{
            ENTRY *temp = th->son[1]->son[0]->entry;
            if(temp->global){
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load v%d t1\n",temp->stack);
                }
            } else{
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load %d t1\n",temp->stack);
                }
            }
        }
        std::string val3;
        if(th->son[3]->son[0]->type == _NUM){
            val3 = std::to_string(th->son[3]->son[0]->val);
        } else{
            ENTRY *temp = th->son[3]->son[0]->entry;
            if(temp->global){
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr v%d t2\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load v%d t2\n",temp->stack);
                }
            } else{
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr %d t2\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load %d t2\n",temp->stack);
                }
            }
            val3 = "t2";
        }
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t3 = t1 %s %s\n",th->son[2]->op.c_str(),val3.c_str());
            fprintf(eeyoreout,"  t0[0] = t3\n");
        } else{
            fprintf(eeyoreout,"  t0 = t1 %s %s\n",th->son[2]->op.c_str(),val3.c_str());
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(th->son[0]->type == _SYMBOL && th->son.size() == 3 && th->son[1]->type == _RightValue){
        //SYMBOL "[" RightValue "]" "=" RightValue
        int val2 = th->son[1]->son[0]->val;
        if(th->son[2]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",th->son[2]->son[0]->val);
        } else{
            ENTRY *temp = th->son[2]->son[0]->entry;
            if(temp->global){
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load v%d t1\n",temp->stack);
                }
            } else{
                if(temp->array){
                    fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
                }else{
                    fprintf(eeyoreout,"  load %d t1\n",temp->stack);
                }
            }
        }
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[%d] = t1\n",val2);
        } else{
            if(val1->array){
                fprintf(eeyoreout,"  loadaddr %d t0\n",val1->stack);
            } else{
                fprintf(eeyoreout,"  load %d t0\n",val1->stack);
            }
            fprintf(eeyoreout,"  t0[%d] = t1\n",val2);
        }
    } else if(th->son[0]->type == _SYMBOL && th->son.size() == 3 && th->son[1]->type == _SYMBOL){
        //SYMBOL "=" SYMBOL "[" RightValue "]"
        int val3 = th->son[2]->son[0]->val;
        ENTRY *temp = th->son[1]->entry;
        if(temp->global){
            fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
        } else{
            if(temp->array){
                fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
            } else{
                fprintf(eeyoreout,"  load %d t1\n",temp->stack);
            }
        }
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t2 = t1[%d]\n",val3);
            fprintf(eeyoreout,"  t0[0] = t2\n");
        } else{
            fprintf(eeyoreout,"  t0 = t1[%d]\n",val3);
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(th->son[0]->type == _IF){
        //"if" RightValue LOGICOP RightValue "goto" LABEL
        if(th->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t0 = %d\n",th->son[1]->son[0]->val);
        } else{
            int s = th->son[1]->son[0]->entry->stack;
            if(th->son[1]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d t0\n",s);
            } else{
                fprintf(eeyoreout,"  load %d t0\n",s);
            }
        }
        if(th->son[3]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",th->son[3]->son[0]->val);
        } else{
            int s = th->son[3]->son[0]->entry->stack;
            if(th->son[3]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d t1\n",s);
            } else{
                fprintf(eeyoreout,"  load %d t1\n",s);
            }
        }
        fprintf(eeyoreout,"  if t0 %s t1 goto %s\n",th->son[2]->op.c_str(),th->son[5]->id.c_str());
    } else if(th->son[0]->type == _GOTO){
        //"goto" LABEL
        fprintf(eeyoreout,"  goto %s\n",th->son[1]->id.c_str());
    } else if(th->son[0]->type == _LABEL){
        //LABEL ":"
        fprintf(eeyoreout,"%s:\n",th->son[0]->id.c_str());
    } else if(th->son[0]->type == _PARAM){
        //"param" RightValue
        if(th->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  a%d = %d\n", param_i,th->son[1]->son[0]->val);
        } else{
            int s = th->son[1]->son[0]->entry->stack;
            if(th->son[1]->son[0]->entry->global){
                if(th->son[1]->son[0]->entry->array){
                    fprintf(eeyoreout,"  loadaddr v%d a%d\n",s,param_i);
                } else{
                    fprintf(eeyoreout,"  load v%d a%d\n",s,param_i);
                }
            } else{
                if(th->son[1]->son[0]->entry->array){
                    fprintf(eeyoreout,"  loadaddr %d a%d\n",s,param_i);
                } else{
                    fprintf(eeyoreout,"  load %d a%d\n",s,param_i);
                }
            }
        }
        param_i++;
    } else if(th->son[0]->type == _CALL){
        //"call" FUNCTION
        fprintf(eeyoreout,"  call %s\n",th->son[1]->id.c_str());
        param_i = 0;
    } else if(th->son[1]->type == _CALL){
        //SYMBOL "=" "call" FUNCTION
        fprintf(eeyoreout,"  call %s\n",th->son[2]->id.c_str());
        param_i = 0;
        ENTRY *val1 = th->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = a0\n");
        } else{
            fprintf(eeyoreout,"  store a0 %d\n",val1->stack);
        }
    }
}

static void irgen_func(AST *th){
    func_ptr = findfunc(th->son[0]->son[0]->id);
    fprintf(eeyoreout,"%s [%d] [%d]\n",func_ptr->id.c_str(),func_ptr->pnum,func_ptr->stack_size);
    for(int i=0;i<func_ptr->pnum;i++){
        fprintf(eeyoreout,"  store a%d %d\n",i,i);
    }
    if(func_ptr->id == "f_main"){
        for(int i=0;i<global_table.size();i++){
            if(global_table[i]->isinit){
                fprintf(eeyoreout,"  loadaddr v%d t0\n",global_table[i]->stack);
                for(int j=0;j<global_table[i]->size;j+=4){
                    fprintf(eeyoreout,"  t1 = %d\n",global_table[i]->init[j/4]);
                    fprintf(eeyoreout,"  t0[%d] = t1\n", j);
                }
            }
        }
    }
    for(int i=0;i<th->son[1]->son.size();i++){
        if(th->son[1]->son[i]->son[0]->type == _Expression){
            irgen_exp(th->son[1]->son[i]->son[0]);
        } else{
            irgen_decl(th->son[1]->son[i]->son[0]);
        }
    }
    fprintf(eeyoreout,"end %s\n",func_ptr->id.c_str());
}

static void irgen_decl(AST *th){
    if(!func_ptr){
        if(th->son.size() == 1){
            fprintf(eeyoreout,"v%d = %d\n",th->son[0]->entry->stack, th->son[0]->entry->val);
        } else{
            fprintf(eeyoreout,"v%d = malloc %d\n",th->son[1]->entry->stack,th->son[0]->val);
        }
    }
}

static void irgen(AST *th){
    func_ptr = nullptr;
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->type == _Declaration){
            irgen_decl(th->son[i]);
        } else if(th->son[i]->type == _Initialization){
            ;
        } else if(th->son[i]->type == _FunctionDef){
            irgen_func(th->son[i]);
        }
    }
}

void codegen_tigger(char *input_file_path, char *output_file_path){
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file = fopen(output_file_path,"w");
    eeyorein = input_file;
    eeyoreout = output_file;

    eeyoreparse();
    irgen(root_eeyore);

    fclose(input_file);
    fclose(output_file);
    eeyorein = stdin;
    eeyoreout = stdout;
}
