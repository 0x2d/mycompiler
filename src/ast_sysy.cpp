#include"ast_sysy.h"
#include<stdio.h>
#include<string>
#include<string.h>
#include"parser.tab.hpp"
using namespace sysy;
extern FILE *sysyin;
extern FILE *sysyout;

AST *root_sysy;
int T_i = 0;    //var
int t_i = 0;    //temp var
int p_i = 0;    //func var
int indent = 0; //global indent
int label = 0;  //global label
int symtable_i = 1; //下一个要打开的符号表编号
int label_in_global;   //最内层代码块的进入标号
int label_out_global;  
bool wait_for_pointer = false;  //用于判断对于数组的引用是否生成指针

TABLE *root_symtable;
std::vector<TABLE *> symtable_vector;
TABLE * symtable_ptr;

bool TABLE::Find(bool isVal, char *id, bool recursive){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(strcmp(id,this->val[i]->id) == 0){
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
            if(strcmp(id,this->func[i]->id) == 0){
                return true;
            }
        }
    }
    return false;
}

ENTRY * TABLE::FindAndReturn(bool isVal, char *id){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(strcmp(id,this->val[i]->id) == 0){
                return this->val[i];
            }
        }
        if(this != root_symtable){
            return this->father->FindAndReturn(isVal,id);
        }
    } else{
        for(int i=0;i<this->func.size();i++){
            if(strcmp(id,this->func[i]->id) == 0){
                return this->func[i];
            }
        }
    }
}

void print_indent(){
    for(int indent_temp=0;indent_temp<indent;indent_temp++){
        fprintf(sysyout,"  ");
    }
}

void print_decl(TABLE *table, int numberoftemp){
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

std::string AST::irgen_LVal(bool isleft){
    if(this->son.size() == 1){
        return ((ENTRY_VAL *)this->son[0]->entry)->eeyore_id;
    } else{
        std::string val1, val2, val3;
        ENTRY_VAL *entry_temp = (ENTRY_VAL *)this->son[0]->entry;
        int size_temp = entry_temp->size;
        val1 = "t"+std::to_string(t_i);
        t_i++;
        if(this->son.size() > 2){
            val3 = "t"+std::to_string(t_i);
            t_i++;
        }
        for(int i=1;i<this->son.size();i++){
            size_temp /= entry_temp->shape[i-1];
            val2 = this->son[i]->son[0]->irgen_AddExp();
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

std::string AST::irgen_UnaryExp(){
    std::string val1, val2;
    if(this->son[0]->type == _PrimaryExp){
        AST *ptr = this->son[0]; //PrimaryExp
        if(ptr->son[0]->type == _INT_CONST){
            val1 = std::to_string(ptr->son[0]->val);
        } else if(ptr->son[0]->type == _LVal){
            val1 = ptr->son[0]->irgen_LVal(false);
        } else{
            val1 = ptr->son[0]->son[0]->irgen_AddExp();
        }
    } else if(this->son[0]->type == _UnaryOp){
        if(this->son[0]->son[0]->op != '+'){
            val1 = "t"+std::to_string(t_i);
            t_i++;
            val2 = this->son[1]->irgen_UnaryExp();
            print_indent();
            fprintf(sysyout,"%s = %c %s\n",val1.c_str(),this->son[0]->son[0]->op,val2.c_str());
        } else{
            val1 = this->son[1]->irgen_UnaryExp();
        }
    } else if(this->son[0]->type == _IDENT){
        if(root_symtable->Find(false,this->son[0]->id,false)){
            this->son[0]->entry = root_symtable->FindAndReturn(false,this->son[0]->id);
        }
        ENTRY_FUNC *func_temp = (ENTRY_FUNC *)this->son[0]->entry;
        if(this->son.size() == 2){
            int param_num = this->son[1]->son.size();
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
                    if(strcmp(func_temp->id,"getarray") == 0 && i == 0
                        || strcmp(func_temp->id,"putarray") == 0 && i == 1){
                            wait_for_pointer = true;
                    }
                }
                val1 = this->son[1]->son[i]->son[0]->irgen_AddExp();
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
            fprintf(sysyout,"  %s = call f_%s\n",val1.c_str(),func_temp->id);
        } else{
            t_i++;
            if(strcmp(func_temp->id,"starttime") == 0){
                fprintf(sysyout,"  param %d\n", this->lineno);
                fprintf(sysyout,"  call f__sysy_starttime\n");
            } else if(strcmp(func_temp->id,"stoptime") == 0){
                fprintf(sysyout,"  param %d\n", this->lineno);
                fprintf(sysyout,"  call f__sysy_stoptime\n");
            } else{
                fprintf(sysyout,"  call f_%s\n",func_temp->id);
            }
        }
    }
    return val1;
}

std::string AST::irgen_MulExp(){
    std::string val1, val2, val3;
    val1 = this->son[0]->irgen_UnaryExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1;i<this->son.size();i+=2){
            val2 = this->son[i+1]->irgen_UnaryExp();
            if(i == 1){
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),this->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),this->son[i]->op,val2.c_str());
            }
        }
        return val3;
    }
}

std::string AST::irgen_AddExp(){
    std::string val1, val2, val3;
    val1 = this->son[0]->irgen_MulExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < this->son.size(); i+=2){
            val2 = this->son[i+1]->irgen_MulExp();
            if(i == 1){
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),this->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),this->son[i]->op,val2.c_str());
            }
        }
        return val3;
    }
}

void AST::irgen_InitVal(int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->son.size() == 0){
            this->son[i]->irgen_InitVal(addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(this->son[i]->son[0]->type == _Exp){
            if(symtable_ptr == root_symtable){
                print_indent();
                fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, this->son[i]->son[0]->val);
                addr += 4;
                nval_temp++;
            } else{
                std::string init_temp = this->son[i]->son[0]->son[0]->irgen_AddExp();
                print_indent();
                fprintf(sysyout,"%s[%d] = %s\n", e->eeyore_id.c_str(), addr, init_temp.c_str());
                addr += 4;
                nval_temp++;
            }
        } else{
            this->son[i]->irgen_InitVal(addr,layer+1,e);
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

void AST::irgen_ConstInitVal(int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->son.size() == 0){
            this->son[i]->irgen_ConstInitVal(addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(this->son[i]->son[0]->type == _ConstExp){
            int init_temp = this->son[i]->son[0]->val;
            //e->arr[nval_temp] = init_temp;
            print_indent();
            fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, init_temp);
            addr += 4;
            nval_temp++;
        } else{
            this->son[i]->irgen_ConstInitVal(addr,layer+1,e);
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

std::string AST::irgen_RelExp(){
    std::string val1, val2, val3, op;
    val1 = this->son[0]->irgen_AddExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < this->son.size(); i+=2){
            if(this->son[i]->type == _LE){
                op = "<=";
            } else if(this->son[i]->type == _GE){
                op = ">=";
            } else{
                op = this->son[i]->op;
            }
            val2 = this->son[i+1]->irgen_AddExp();
            if(i == 1){
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

std::string AST::irgen_EqExp(){
    std::string val1, val2, val3, op;
    val1 = this->son[0]->irgen_RelExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < this->son.size(); i+=2){
            if(this->son[i]->type == _EQ){
                op = "==";
            } else{
                op = "!=";
            }
            val2 = this->son[i+1]->irgen_RelExp();
            if(i == 1){
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

void AST::irgen_LAndExp(int label_false){
    std::string val1;
    for(int i=0;i< this->son.size();i+=2){
        val1 = this->son[i]->irgen_EqExp();
        fprintf(sysyout,"  if %s == 0 goto l%d\n",val1.c_str(),label_false);
    }
}

void AST::irgen_LOrExp(int label_true, int label_false){
    int size_temp = this->son.size();
    for(int i=0;i< size_temp;i+=2){
        if(i+2 < size_temp){
            this->son[i]->irgen_LAndExp(label);
            fprintf(sysyout,"  goto l%d\n",label_true);
            fprintf(sysyout,"l%d:\n",label);
            label++;
        } else{
            this->son[i]->irgen_LAndExp(label_false);
        }
    }
}

void AST::irgen_Stmt(){
    if(this->son.size() == 0){
        //';'
        return;
    }
    if(this->son[0]->type == _RETURN){
        if(this->son.size() == 1){
            //RETURN ';'
            fprintf(sysyout,"  return\n");
        } else{
            //RETURN Exp ';'
            std::string return_temp = this->son[1]->son[0]->irgen_AddExp();
            fprintf(sysyout,"  return %s\n",return_temp.c_str());
        }
    } else if(this->son[0]->type == _LVal){
        //LVal '=' Exp ';'
        std::string left_temp = this->son[0]->irgen_LVal(true);
        std::string right_temp = this->son[1]->son[0]->irgen_AddExp();
        fprintf(sysyout,"  %s = %s\n",left_temp.c_str(),right_temp.c_str());
    } else if(this->son[0]->type == _Exp){
        //Exp ';'
        this->son[0]->son[0]->irgen_AddExp();
    } else if(this->son[0]->type == _Block){
        //Block
        this->son[0]->irgen_Block();
    } else if(this->son[0]->type == _WHILE){
        //WHILE '(' Cond ')' Stmt
        int label_in_temp = label_in_global;
        int label_out_temp = label_out_global;
        this->label_in = label;
        this->label_in2 = label+1;
        this->label_out = label+2;
        label += 3;
        label_in_global = this->label_in;
        label_out_global = this->label_out;
        fprintf(sysyout,"l%d:\n",this->label_in);
        this->son[1]->son[0]->irgen_LOrExp(this->label_in2, this->label_out);
        fprintf(sysyout,"l%d:\n",this->label_in2);
        this->son[2]->irgen_Stmt();
        fprintf(sysyout,"  goto l%d\n",this->label_in);
        fprintf(sysyout,"l%d:\n",this->label_out);
        label_in_global = label_in_temp;
        label_out_global = label_out_temp;
    } else if(this->son[0]->type == _IF && this->son.size() == 5){
        //IF '(' Cond ')' Stmt ELSE Stmt
        this->label_in = label;
        this->label_in2 = label+1;
        this->label_out = label+2;
        label += 3;
        this->son[1]->son[0]->irgen_LOrExp(this->label_in,this->label_in2);
        fprintf(sysyout,"l%d:\n",this->label_in);
        this->son[2]->irgen_Stmt();
        fprintf(sysyout,"  goto l%d\n",this->label_out);
        fprintf(sysyout,"l%d:\n",this->label_in2);
        this->son[4]->irgen_Stmt();
        fprintf(sysyout,"l%d:\n",this->label_out);
    } else if(this->son[0]->type == _IF && this->son.size() == 3){
        //IF '(' Cond ')' Stmt
        this->label_in = label;
        this->label_out = label+1;
        label += 2;
        this->son[1]->son[0]->irgen_LOrExp(this->label_in,this->label_out);
        fprintf(sysyout,"l%d:\n",this->label_in);
        this->son[2]->irgen_Stmt();
        fprintf(sysyout,"l%d:\n",this->label_out);
    } else if(this->son[0]->type == _BREAK){
        //BREAK ';'
        fprintf(sysyout,"  goto l%d\n",label_out_global);
    } else if(this->son[0]->type == _CONTINUE){
        //CONTINUE ';'
        fprintf(sysyout,"  goto l%d\n",label_in_global);
    }
}

void AST::irgen_Block(){
    symtable_ptr = symtable_vector[symtable_i];
    symtable_i++;
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->son[0]->type == _Decl){
            this->son[i]->son[0]->irgen_Decl();
        } else{
            this->son[i]->son[0]->irgen_Stmt();
        }
    }
    symtable_ptr = symtable_ptr->father;
}

void AST::irgen_FuncDef(){
    ENTRY_FUNC *func_ptr = (ENTRY_FUNC *)this->son[1]->entry;
    fprintf(sysyout,"f_%s [%d]\n",func_ptr->id, func_ptr->NumberOfParam);
    indent++;
    p_i = 0;
    print_decl(func_ptr->symtable,func_ptr->NumberOfTemp);
    this->son[this->son.size()-1]->irgen_Block();
    if(func_ptr->isreturn){
        fprintf(sysyout,"  return 0\n");
    } else{
        fprintf(sysyout,"  return\n");
    }
    indent--;
    fprintf(sysyout,"end f_%s\n",this->son[1]->id);
}

void AST::irgen_Decl(){
    AST *ptr = this->son[0];
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
                        std::string val_temp = ptr_temp->son[2]->son[0]->son[0]->irgen_AddExp();
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
                    ptr_temp->son[2]->irgen_InitVal(0, 0, entry_temp);
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
                    ptr_temp->son[2]->irgen_ConstInitVal(0, 0, entry_temp);
                }
            }
        }
    }
}

void AST::irgen(){
    print_decl(root_symtable, 0);
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->type==_Decl){
            this->son[i]->irgen_Decl();
        } else if(this->son[i]->type==_FuncDef){
            this->son[i]->irgen_FuncDef();
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
    root_sysy->irgen();

    fclose(input_file);
    fclose(output_file);
    sysyin = stdin;
    sysyout = stdout;
}
