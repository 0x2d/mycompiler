#include"ast_sysy.h"
#include<stdio.h>
#include<string>
#include<string.h>
#include"parser.tab.hpp"

extern FILE *sysyin;
extern FILE *sysyout;

AST *root_sysy;
TABLE *root_symtable;
std::vector<TABLE *> symtable_vector;
TABLE * symtable_ptr;
int T_i = 0;    //var
int t_i = 0;    //temp var
int p_i = 0;    //func var
int indent = 0; //global indent
int label = 0;  //global label
int symtable_i = 1; //下一个要打开的符号表编号
int label_in_global;   //最内层代码块的进入标号
int label_out_global;  
bool wait_for_pointer = false;  //用于判断对于数组的引用是否生成指针

static void irgen(AST *th);
static void irgen_Decl(AST *th);
static void irgen_FuncDef(AST *th);
static void irgen_Block(AST *th);
static void irgen_Stmt(AST *th);
static void irgen_ConstInitVal(AST *th, int addr, int layer, ENTRY_VAL *e);
static void irgen_InitVal(AST *th, int addr, int layer, ENTRY_VAL *e);
static std::string irgen_AddExp(AST *th);
static std::string irgen_MulExp(AST *th);
static std::string irgen_UnaryExp(AST *th);
static std::string irgen_LVal(AST *th, bool isleft);
static void irgen_LOrExp(AST *th, int label_true, int label_false);
static void irgen_LAndExp(AST *th, int label_false);
static std::string irgen_EqExp(AST *th);
static std::string irgen_RelExp(AST *th);

bool TABLE::Find(bool isVal, std::string id, bool recursive){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(id == this->val[i]->id){
                return true;
            }
        }
        if(recursive){
            if(this != root_symtable){
                return this->father->Find(isVal,id,recursive);
            }
        }
    } else{
        for(int i=0;i<this->func.size();i++){
            if(id == this->func[i]->id){
                return true;
            }
        }
    }
    return false;
}

ENTRY * TABLE::FindAndReturn(bool isVal, std::string id){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(id == this->val[i]->id){
                return this->val[i];
            }
        }
        if(this != root_symtable){
            return this->father->FindAndReturn(isVal,id);
        }
    } else{
        for(int i=0;i<this->func.size();i++){
            if(id == this->func[i]->id){
                return this->func[i];
            }
        }
    }
}

static void print_indent(){
    for(int indent_temp=0;indent_temp<indent;indent_temp++){
        fprintf(sysyout,"  ");
    }
}

static void print_decl(TABLE *table, int numberoftemp){
    for(int i=0;i<table->val.size();i++){
        if(table->val[i]->isParam){
            table->val[i]->eeyore_id = "p"+std::to_string(p_i);
            p_i++;
        } else{
            table->val[i]->eeyore_id = "T"+std::to_string(T_i);
            T_i++;
            if(table->val[i]->isArray){
                print_indent();
                fprintf(sysyout,"var %d %s\n", table->val[i]->size, table->val[i]->eeyore_id.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"var %s\n", table->val[i]->eeyore_id.c_str());
            }
        }
    }
    if(table != root_symtable){
        for(int i=0;i<table->son.size();i++){
            print_decl(table->son[i],0);
        }
    }
    int t_i_temp = t_i;
    for(int i=0;i<numberoftemp;i++){
        print_indent();
        fprintf(sysyout,"var t%d\n",t_i);
        t_i++;
    }
    t_i = t_i_temp;
}

static std::string irgen_LVal(AST *th, bool isleft){
    if(th->son.size() == 1){
        return ((ENTRY_VAL *)th->son[0]->entry)->eeyore_id;
    } else{
        std::string val1, val2, val3;
        ENTRY_VAL *entry_temp = (ENTRY_VAL *)th->son[0]->entry;
        int size_temp = entry_temp->size;
        val1 = "t"+std::to_string(t_i);
        t_i++;
        if(th->son.size() > 2){
            val3 = "t"+std::to_string(t_i);
            t_i++;
        }
        for(int i=1;i<th->son.size();i++){
            size_temp /= entry_temp->shape[i-1];
            val2 = irgen_AddExp(th->son[i]->son[0]);
            if(i==1){
                print_indent();
                fprintf(sysyout,"%s = %s * %d\n",val1.c_str(),val2.c_str(),size_temp);
            } else{
                print_indent();
                fprintf(sysyout,"%s = %s * %d\n",val3.c_str(),val2.c_str(),size_temp);
                print_indent();
                fprintf(sysyout,"%s = %s + %s\n",val1.c_str(),val1.c_str(),val3.c_str());
            }
        }
        print_indent();
        fprintf(sysyout,"%s = %s + %s\n",val1.c_str(),entry_temp->eeyore_id.c_str(),val1.c_str());
        if(wait_for_pointer){
            return val1;
        }
        if(isleft){
            return val1+"[0]";
        } else{
            print_indent();
            fprintf(sysyout,"%s = %s[0]\n",val1.c_str(),val1.c_str());
            return val1;
        }
    }
}

static std::string irgen_UnaryExp(AST *th){
    std::string val1, val2;
    if(th->son[0]->type == _PrimaryExp){
        AST *ptr = th->son[0]; //PrimaryExp
        if(ptr->son[0]->type == _INT_CONST){
            val1 = std::to_string(ptr->son[0]->val);
        } else if(ptr->son[0]->type == _LVal){
            val1 = irgen_LVal(ptr->son[0],false);
        } else{
            val1 = irgen_AddExp(ptr->son[0]->son[0]);
        }
    } else if(th->son[0]->type == _UnaryOp){
        if(th->son[0]->son[0]->op != '+'){
            val1 = "t"+std::to_string(t_i);
            t_i++;
            val2 = irgen_UnaryExp(th->son[1]);
            print_indent();
            fprintf(sysyout,"%s = %c %s\n",val1.c_str(),th->son[0]->son[0]->op,val2.c_str());
        } else{
            val1 = irgen_UnaryExp(th->son[1]);
        }
    } else if(th->son[0]->type == _IDENT){
        if(root_symtable->Find(false,th->son[0]->id,false)){
            th->son[0]->entry = root_symtable->FindAndReturn(false,th->son[0]->id);
        }
        ENTRY_FUNC *func_temp = (ENTRY_FUNC *)th->son[0]->entry;
        if(th->son.size() == 2){
            int param_num = th->son[1]->son.size();
            std::string params[param_num];
            for(int i=0;i<param_num;i++){
                if(func_temp->symtable){
                    std::string p_temp = "p"+std::to_string(i);
                    for(int j=0;j<func_temp->symtable->val.size();j++){
                        if(func_temp->symtable->val[j]->isParam && p_temp == func_temp->symtable->val[j]->eeyore_id){
                            wait_for_pointer = func_temp->symtable->val[j]->isArray;
                        }
                    }
                } else{
                    if((func_temp->id == "getarray" && i == 0)
                        || (func_temp->id == "putarray" == 0 && i == 1)){
                            wait_for_pointer = true;
                    }
                }
                val1 = irgen_AddExp(th->son[1]->son[i]->son[0]);
                wait_for_pointer = false;
                params[i] = val1;
            }
            for(int i=0;i<param_num;i++){
                fprintf(sysyout,"  param %s\n", params[i].c_str());
            }
        }
        if(func_temp->isreturn){
            val1 = "t"+std::to_string(t_i);
            t_i++;
            fprintf(sysyout,"  %s = call f_%s\n",val1.c_str(),func_temp->id.c_str());
        } else{
            t_i++;
            if(func_temp->id == "starttime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call f__sysy_starttime\n");
            } else if(func_temp->id == "stoptime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call f__sysy_stoptime\n");
            } else{
                fprintf(sysyout,"  call f_%s\n",func_temp->id.c_str());
            }
        }
    }
    return val1;
}

static std::string irgen_MulExp(AST *th){
    std::string val1, val2, val3;
    val1 = irgen_UnaryExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1;i<th->son.size();i+=2){
            val2 = irgen_UnaryExp(th->son[i+1]);
            if(i == 1){
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),th->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),th->son[i]->op,val2.c_str());
            }
        }
        return val3;
    }
}

static std::string irgen_AddExp(AST *th){
    std::string val1, val2, val3;
    val1 = irgen_MulExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            val2 = irgen_MulExp(th->son[i+1]);
            if(i == 1){
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),th->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),th->son[i]->op,val2.c_str());
            }
        }
        return val3;
    }
}

static void irgen_InitVal(AST *th, int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son.size() == 0){
            irgen_InitVal(th->son[i], addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(th->son[i]->son[0]->type == _Exp){
            if(symtable_ptr == root_symtable){
                print_indent();
                fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, th->son[i]->son[0]->val);
                addr += 4;
                nval_temp++;
            } else{
                std::string init_temp = irgen_AddExp(th->son[i]->son[0]->son[0]);
                print_indent();
                fprintf(sysyout,"%s[%d] = %s\n", e->eeyore_id.c_str(), addr, init_temp.c_str());
                addr += 4;
                nval_temp++;
            }
        } else{
            irgen_InitVal(th->son[i],addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        print_indent();
        fprintf(sysyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
        addr += 4;
    }
}

static void irgen_ConstInitVal(AST *th, int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son.size() == 0){
            irgen_ConstInitVal(th->son[i],addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(th->son[i]->son[0]->type == _ConstExp){
            int init_temp = th->son[i]->son[0]->val;
            //e->arr[nval_temp] = init_temp;
            print_indent();
            fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, init_temp);
            addr += 4;
            nval_temp++;
        } else{
            irgen_ConstInitVal(th->son[i], addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        //e->arr[nval_temp] = 0;
        print_indent();
        fprintf(sysyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
        addr += 4;
    }
}

static std::string irgen_RelExp(AST *th){
    std::string val1, val2, val3, op;
    val1 = irgen_AddExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            if(th->son[i]->type == _LE){
                op = "<=";
            } else if(th->son[i]->type == _GE){
                op = ">=";
            } else{
                op = th->son[i]->op;
            }
            val2 = irgen_AddExp(th->son[i+1]);
            if(i == 1){
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

static std::string irgen_EqExp(AST *th){
    std::string val1, val2, val3, op;
    val1 = irgen_RelExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            if(th->son[i]->type == _EQ){
                op = "==";
            } else{
                op = "!=";
            }
            val2 = irgen_RelExp(th->son[i+1]);
            if(i == 1){
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

static void irgen_LAndExp(AST *th, int label_false){
    std::string val1;
    for(int i=0;i< th->son.size();i+=2){
        val1 = irgen_EqExp(th->son[i]);
        fprintf(sysyout,"  if %s == 0 goto l%d\n",val1.c_str(),label_false);
    }
}

static void irgen_LOrExp(AST *th, int label_true, int label_false){
    int size_temp = th->son.size();
    for(int i=0;i< size_temp;i+=2){
        if(i+2 < size_temp){
            irgen_LAndExp(th->son[i], label);
            fprintf(sysyout,"  goto l%d\n",label_true);
            fprintf(sysyout,"l%d:\n",label);
            label++;
        } else{
            irgen_LAndExp(th->son[i], label_false);
        }
    }
}

static void irgen_Stmt(AST *th){
    if(th->son.size() == 0){
        //';'
        return;
    }
    if(th->son[0]->type == _RETURN){
        if(th->son.size() == 1){
            //RETURN ';'
            fprintf(sysyout,"  return\n");
        } else{
            //RETURN Exp ';'
            std::string return_temp = irgen_AddExp(th->son[1]->son[0]);
            fprintf(sysyout,"  return %s\n",return_temp.c_str());
        }
    } else if(th->son[0]->type == _LVal){
        //LVal '=' Exp ';'
        std::string left_temp = irgen_LVal(th->son[0],true);
        std::string right_temp = irgen_AddExp(th->son[1]->son[0]);
        fprintf(sysyout,"  %s = %s\n",left_temp.c_str(),right_temp.c_str());
    } else if(th->son[0]->type == _Exp){
        //Exp ';'
        irgen_AddExp(th->son[0]->son[0]);
    } else if(th->son[0]->type == _Block){
        //Block
        irgen_Block(th->son[0]);
    } else if(th->son[0]->type == _WHILE){
        //WHILE '(' Cond ')' Stmt
        int label_in_temp = label_in_global;
        int label_out_temp = label_out_global;
        th->label_in = label;
        th->label_in2 = label+1;
        th->label_out = label+2;
        label += 3;
        label_in_global = th->label_in;
        label_out_global = th->label_out;
        fprintf(sysyout,"l%d:\n",th->label_in);
        irgen_LOrExp(th->son[1]->son[0], th->label_in2, th->label_out);
        fprintf(sysyout,"l%d:\n",th->label_in2);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,"  goto l%d\n",th->label_in);
        fprintf(sysyout,"l%d:\n",th->label_out);
        label_in_global = label_in_temp;
        label_out_global = label_out_temp;
    } else if(th->son[0]->type == _IF && th->son.size() == 5){
        //IF '(' Cond ')' Stmt ELSE Stmt
        th->label_in = label;
        th->label_in2 = label+1;
        th->label_out = label+2;
        label += 3;
        irgen_LOrExp(th->son[1]->son[0],th->label_in,th->label_in2);
        fprintf(sysyout,"l%d:\n",th->label_in);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,"  goto l%d\n",th->label_out);
        fprintf(sysyout,"l%d:\n",th->label_in2);
        irgen_Stmt(th->son[4]);
        fprintf(sysyout,"l%d:\n",th->label_out);
    } else if(th->son[0]->type == _IF && th->son.size() == 3){
        //IF '(' Cond ')' Stmt
        th->label_in = label;
        th->label_out = label+1;
        label += 2;
        irgen_LOrExp(th->son[1]->son[0], th->label_in,th->label_out);
        fprintf(sysyout,"l%d:\n",th->label_in);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,"l%d:\n",th->label_out);
    } else if(th->son[0]->type == _BREAK){
        //BREAK ';'
        fprintf(sysyout,"  goto l%d\n",label_out_global);
    } else if(th->son[0]->type == _CONTINUE){
        //CONTINUE ';'
        fprintf(sysyout,"  goto l%d\n",label_in_global);
    }
}

static void irgen_Block(AST *th){
    symtable_ptr = symtable_vector[symtable_i];
    symtable_i++;
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son[0]->type == _Decl){
            irgen_Decl(th->son[i]->son[0]);
        } else{
            irgen_Stmt(th->son[i]->son[0]);
        }
    }
    symtable_ptr = symtable_ptr->father;
}

static void irgen_FuncDef(AST *th){
    ENTRY_FUNC *func_ptr = (ENTRY_FUNC *)th->son[1]->entry;
    fprintf(sysyout,"f_%s [%d]\n",func_ptr->id.c_str(), func_ptr->NumberOfParam);
    indent++;
    p_i = 0;
    print_decl(func_ptr->symtable,func_ptr->NumberOfTemp);
    irgen_Block(th->son[th->son.size()-1]);
    if(func_ptr->isreturn){
        fprintf(sysyout,"  return 0\n");
    } else{
        fprintf(sysyout,"  return\n");
    }
    indent--;
    fprintf(sysyout,"end f_%s\n",th->son[1]->id.c_str());
}

static void irgen_Decl(AST *th){
    AST *ptr = th->son[0];
    if(ptr->type == _VarDecl){
        ptr = ptr->son[1];  //VarDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //VarDef
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            if(ptr_temp->son[1]->son.size() == 0){
                if(ptr_temp->son.size() > 2){
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = ptr_temp->son[2]->son[0]->val;
                        print_indent();
                        fprintf(sysyout,"%s = %d\n", entry_temp->eeyore_id.c_str(), entry_temp->val);
                    } else{
                        std::string val_temp = irgen_AddExp(ptr_temp->son[2]->son[0]->son[0]);
                        print_indent();
                        fprintf(sysyout,"%s = %s\n", entry_temp->eeyore_id.c_str(), val_temp.c_str());
                    }
                } else{
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = 0;
                    }
                }
            } else {
                if(ptr_temp->son.size() > 2){
                    //entry_temp->arr = new int [entry_temp->size/4];
                    irgen_InitVal(ptr_temp->son[2], 0, 0, entry_temp);
                }
            }
        }
    } else if(ptr->type == _ConstDecl){
        ptr = ptr->son[2];  //ConstDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //ConstDef
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            if(ptr_temp->son[1]->son.size() == 0){
                entry_temp->val = ptr_temp->son[2]->son[0]->val;
                print_indent();
                fprintf(sysyout,"%s = %d\n", entry_temp->eeyore_id.c_str(), entry_temp->val);
            } else {
                if(ptr_temp->son.size() > 2){
                    //entry_temp->arr = new int [entry_temp->size/4];
                    irgen_ConstInitVal(ptr_temp->son[2], 0, 0, entry_temp);
                }
            }
        }
    }
}

static void irgen(AST *th){
    print_decl(root_symtable, 0);
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->type==_Decl){
            irgen_Decl(th->son[i]);
        } else if(th->son[i]->type==_FuncDef){
            irgen_FuncDef(th->son[i]);
        }
    }
}

void codegen_eeyore(char *input_file_path, char *output_file_path){
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file = fopen(output_file_path,"w");
    sysyin = input_file;
    sysyout = output_file;

    root_symtable = new TABLE("root");
    symtable_vector.push_back(root_symtable);
    symtable_ptr = root_symtable;
    new ENTRY_FUNC("getint",root_symtable,true,nullptr,0,0);
    new ENTRY_FUNC("getch",root_symtable,true,nullptr,0,0);
    new ENTRY_FUNC("getarray",root_symtable,true,nullptr,0,1);
    new ENTRY_FUNC("putint",root_symtable,false,nullptr,0,1);
    new ENTRY_FUNC("putch",root_symtable,false,nullptr,0,1);
    new ENTRY_FUNC("putarray",root_symtable,false,nullptr,0,2);
    new ENTRY_FUNC("starttime",root_symtable,false,nullptr,0,0);
    new ENTRY_FUNC("stoptime",root_symtable,false,nullptr,0,0);
    sysyparse();
    irgen(root_sysy);

    fclose(input_file);
    fclose(output_file);
    sysyin = stdin;
    sysyout = stdout;
}
