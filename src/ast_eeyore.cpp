#include"ast_eeyore.h"
#include<stdio.h>
#include<string>
#include<string.h>
#include"eeyore.tab.hpp"
using namespace eeyore;
extern FILE *eeyorein;
extern FILE *eeyoreout;

int regs[28] = {0};
std::vector<ENTRY *>global_table;
std::vector<class FUNC *>functions;
class FUNC *func_ptr = nullptr;

AST *root_eeyore;
int param_i = 0;

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

class FUNC *findfunc(std::string id){
    for(int i=0;i<functions.size();i++){
        if(functions[i]->id == id){
            return functions[i];
        }
    }
    return nullptr;
}

std::string regname(int reg){
    if(reg == 0){
        return "x0";
    } else if(reg >=1 && reg <=12){
        return "s"+std::to_string(reg-1);
    } else if(reg >= 13 && reg <= 19){
        return "t"+std::to_string(reg-13);
    } else if(reg >= 20 && reg <= 27){
        return "a"+std::to_string(reg-20);
    }
}

void AST::irgen_exp(){
    if(this->son[0]->type == _RETURN && this->son.size() == 1){
        //"return";
        fprintf(eeyoreout,"  return\n");
    } else if(this->son[0]->type == _RETURN && this->son.size() == 2){
        //"return" RightValue
        if(this->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  a0 = %d\n", this->son[1]->son[0]->val);
        } else{
            int s = this->son[1]->son[0]->entry->stack;
            if(this->son[1]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d a0\n",s);
            } else{
                fprintf(eeyoreout,"  load %d a0\n",s);
            }
        }
        fprintf(eeyoreout,"  return\n");
    } else if(this->son[0]->type == _SYMBOL && this->son.size() == 2 && this->son[1]->type == _RightValue){
        //SYMBOL "=" RightValue
        if(this->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",this->son[1]->son[0]->val);
        } else{
            ENTRY *temp = this->son[1]->son[0]->entry;
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
        ENTRY *val1 = this->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = t1\n");
        } else{
            fprintf(eeyoreout,"  store t1 %d\n",val1->stack);
        }
    } else if(this->son[0]->type == _SYMBOL && this->son.size() == 3 && this->son[1]->type == _OP){
        //SYMBOL "=" OP RightValue
        if(this->son[2]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",this->son[2]->son[0]->val);
        } else{
            ENTRY *temp = this->son[2]->son[0]->entry;
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
        ENTRY *val1 = this->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = %s t1\n",this->son[1]->op.c_str());
        } else{
            fprintf(eeyoreout,"  t0 = %s t1\n",this->son[1]->op.c_str());
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(this->son[0]->type == _SYMBOL && this->son.size() == 4 && this->son[2]->type == _BinOp){
        //SYMBOL "=" RightValue BinOp RightValue
        if(this->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",this->son[1]->son[0]->val);
        } else{
            ENTRY *temp = this->son[1]->son[0]->entry;
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
        if(this->son[3]->son[0]->type == _NUM){
            val3 = std::to_string(this->son[3]->son[0]->val);
        } else{
            ENTRY *temp = this->son[3]->son[0]->entry;
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
        ENTRY *val1 = this->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t3 = t1 %s %s\n",this->son[2]->op.c_str(),val3.c_str());
            fprintf(eeyoreout,"  t0[0] = t3\n");
        } else{
            fprintf(eeyoreout,"  t0 = t1 %s %s\n",this->son[2]->op.c_str(),val3.c_str());
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(this->son[0]->type == _SYMBOL && this->son.size() == 3 && this->son[1]->type == _RightValue){
        //SYMBOL "[" RightValue "]" "=" RightValue
        int val2 = this->son[1]->son[0]->val;
        if(this->son[2]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",this->son[2]->son[0]->val);
        } else{
            ENTRY *temp = this->son[2]->son[0]->entry;
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
        ENTRY *val1 = this->son[0]->entry;
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
    } else if(this->son[0]->type == _SYMBOL && this->son.size() == 3 && this->son[1]->type == _SYMBOL){
        //SYMBOL "=" SYMBOL "[" RightValue "]"
        int val3 = this->son[2]->son[0]->val;
        ENTRY *temp = this->son[1]->entry;
        if(temp->global){
            fprintf(eeyoreout,"  loadaddr v%d t1\n",temp->stack);
        } else{
            if(temp->array){
                fprintf(eeyoreout,"  loadaddr %d t1\n",temp->stack);
            } else{
                fprintf(eeyoreout,"  load %d t1\n",temp->stack);
            }
        }
        ENTRY *val1 = this->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t2 = t1[%d]\n",val3);
            fprintf(eeyoreout,"  t0[0] = t2\n");
        } else{
            fprintf(eeyoreout,"  t0 = t1[%d]\n",val3);
            fprintf(eeyoreout,"  store t0 %d\n",val1->stack);
        }
    } else if(this->son[0]->type == _IF){
        //"if" RightValue LOGICOP RightValue "goto" LABEL
        if(this->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t0 = %d\n",this->son[1]->son[0]->val);
        } else{
            int s = this->son[1]->son[0]->entry->stack;
            if(this->son[1]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d t0\n",s);
            } else{
                fprintf(eeyoreout,"  load %d t0\n",s);
            }
        }
        if(this->son[3]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  t1 = %d\n",this->son[3]->son[0]->val);
        } else{
            int s = this->son[3]->son[0]->entry->stack;
            if(this->son[3]->son[0]->entry->global){
                fprintf(eeyoreout,"  load v%d t1\n",s);
            } else{
                fprintf(eeyoreout,"  load %d t1\n",s);
            }
        }
        fprintf(eeyoreout,"  if t0 %s t1 goto %s\n",this->son[2]->op.c_str(),this->son[5]->id.c_str());
    } else if(this->son[0]->type == _GOTO){
        //"goto" LABEL
        fprintf(eeyoreout,"  goto %s\n",this->son[1]->id.c_str());
    } else if(this->son[0]->type == _LABEL){
        //LABEL ":"
        fprintf(eeyoreout,"%s:\n",this->son[0]->id.c_str());
    } else if(this->son[0]->type == _PARAM){
        //"param" RightValue
        if(this->son[1]->son[0]->type == _NUM){
            fprintf(eeyoreout,"  a%d = %d\n", param_i,this->son[1]->son[0]->val);
        } else{
            int s = this->son[1]->son[0]->entry->stack;
            if(this->son[1]->son[0]->entry->global){
                if(this->son[1]->son[0]->entry->array){
                    fprintf(eeyoreout,"  loadaddr v%d a%d\n",s,param_i);
                } else{
                    fprintf(eeyoreout,"  load v%d a%d\n",s,param_i);
                }
            } else{
                if(this->son[1]->son[0]->entry->array){
                    fprintf(eeyoreout,"  loadaddr %d a%d\n",s,param_i);
                } else{
                    fprintf(eeyoreout,"  load %d a%d\n",s,param_i);
                }
            }
        }
        param_i++;
    } else if(this->son[0]->type == _CALL){
        //"call" FUNCTION
        fprintf(eeyoreout,"  call %s\n",this->son[1]->id.c_str());
        param_i = 0;
    } else if(this->son[1]->type == _CALL){
        //SYMBOL "=" "call" FUNCTION
        fprintf(eeyoreout,"  call %s\n",this->son[2]->id.c_str());
        param_i = 0;
        ENTRY *val1 = this->son[0]->entry;
        if(val1->global){
            fprintf(eeyoreout,"  loadaddr v%d t0\n",val1->stack);
            fprintf(eeyoreout,"  t0[0] = a0\n");
        } else{
            fprintf(eeyoreout,"  store a0 %d\n",val1->stack);
        }
    }
}

void AST::irgen_func(){
    func_ptr = findfunc(this->son[0]->son[0]->id);
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
    for(int i=0;i<this->son[1]->son.size();i++){
        if(this->son[1]->son[i]->son[0]->type == _Expression){
            this->son[1]->son[i]->son[0]->irgen_exp();
        } else{
            this->son[1]->son[i]->son[0]->irgen_decl();
        }
    }
    fprintf(eeyoreout,"end %s\n",func_ptr->id.c_str());
}

void AST::irgen_decl(){
    if(!func_ptr){
        if(this->son.size() == 1){
            fprintf(eeyoreout,"v%d = %d\n",this->son[0]->entry->stack, this->son[0]->entry->val);
        } else{
            fprintf(eeyoreout,"v%d = malloc %d\n",this->son[1]->entry->stack,this->son[0]->val);
        }
    }
}

void AST::irgen(){
    func_ptr = nullptr;
    functions.push_back(new class FUNC("getint",0));
    functions.push_back(new class FUNC("getch",0));
    functions.push_back(new class FUNC("getarray",1));
    functions.push_back(new class FUNC("putint",1));
    functions.push_back(new class FUNC("putch",1));
    functions.push_back(new class FUNC("putarray",2));
    functions.push_back(new class FUNC("starttime",0));
    functions.push_back(new class FUNC("stoptime",0));
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->type == _Declaration){
            this->son[i]->irgen_decl();
        } else if(this->son[i]->type == _Initialization){
            ;
        } else if(this->son[i]->type == _FunctionDef){
            this->son[i]->irgen_func();
        }
    }
}

void codegen_tigger(char *input_file_path, char *output_file_path){
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file = fopen(output_file_path,"w");
    eeyorein = input_file;
    eeyoreout = output_file;

    eeyoreparse();
    root_eeyore->irgen();

    fclose(input_file);
    fclose(output_file);
    eeyorein = stdin;
    eeyoreout = stdout;
}
