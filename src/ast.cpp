#include"ast.h"
#include"symtable.h"
#include<stdio.h>
#include<stack>
#include<string>
extern FILE *yyout;
extern TABLE *root_symtable;
extern std::vector<TABLE *>symtable_vector;
extern TABLE * symtable_ptr;
extern int NumberOfTemp_global;

AST *root;
int T_i = 0;    //var
int t_i = 0;    //temp var
int p_i = 0;    //func var
int indent = 0; //global indent
int label = 0;  //global label
int symtable_i = 1; //下一个要打开的符号表编号
int label_in_global;   //最内层代码块的进入标号
int label_out_global;  
bool returned = false;  //是否已经打印return
bool wait_for_pointer = false;  //用于判断对于数组的引用是否生成指针

void print_indent(){
    for(int indent_temp=0;indent_temp<indent;indent_temp++){
        fprintf(yyout,"  ");
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
                fprintf(yyout,"var %d %s\n", table->val[i]->size, table->val[i]->eeyore_id.c_str());
            } else{
                print_indent();
                fprintf(yyout,"var %s\n", table->val[i]->eeyore_id.c_str());
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
        fprintf(yyout,"var t%d\n",t_i);
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
        val3 = "t"+std::to_string(t_i);
        t_i++;
        print_indent();
        fprintf(yyout,"%s = 0\n",val1.c_str());
        for(int i=1;i<this->son.size();i++){
            size_temp /= entry_temp->shape[i-1];
            val2 = this->son[i]->son[0]->irgen_AddExp();
            print_indent();
            fprintf(yyout,"%s = %s * %d\n",val3.c_str(),val2.c_str(),size_temp);
            print_indent();
            fprintf(yyout,"%s = %s + %s\n",val1.c_str(),val1.c_str(),val3.c_str());
        }
        if(wait_for_pointer){
            print_indent();
            fprintf(yyout,"%s = %s + %s\n",val1.c_str(),entry_temp->eeyore_id.c_str(),val1.c_str());
            return val1;
        }
        if(isleft){
            return entry_temp->eeyore_id+"["+val1+"]";
        } else{
            print_indent();
            fprintf(yyout,"%s = %s[%s]\n",val1.c_str(),entry_temp->eeyore_id.c_str(),val1.c_str());
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
            fprintf(yyout,"%s = %c %s\n",val1.c_str(),this->son[0]->son[0]->op,val2.c_str());
        } else{
            val1 = this->son[1]->irgen_UnaryExp();
        }
    } else if(this->son[0]->type == _IDENT){
        if(root_symtable->Find(false,this->son[0]->id,false)){
            this->son[0]->entry = root_symtable->FindAndReturn(false,this->son[0]->id);
        }
        ENTRY_FUNC *func_temp = (ENTRY_FUNC *)this->son[0]->entry;
        if(this->son.size() == 2){
            for(int i=0;i<this->son[1]->son.size();i++){
                if(func_temp->symtable){
                    std::string p_temp = "p"+std::to_string(i);
                    for(int j=0;j<func_temp->symtable->val.size();j++){
                        if(func_temp->symtable->val[j]->isParam && p_temp == func_temp->symtable->val[j]->eeyore_id){
                            wait_for_pointer = func_temp->symtable->val[j]->isArray;
                        }
                    }
                }
                val1 = this->son[1]->son[i]->son[0]->irgen_AddExp();
                wait_for_pointer = false;
                print_indent();
                fprintf(yyout,"param %s\n", val1.c_str());
            }
        }
        if(func_temp->isreturn){
            val1 = "t"+std::to_string(t_i);
            t_i++;
            print_indent();
            fprintf(yyout,"%s = call f_%s\n",val1.c_str(),func_temp->id);
        } else{
            t_i++;
            print_indent();
            fprintf(yyout,"call f_%s\n",func_temp->id);
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
                fprintf(yyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),this->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),this->son[i]->op,val2.c_str());
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
                fprintf(yyout,"%s = %s %c %s\n",val3.c_str(), val1.c_str(),this->son[i]->op,val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s %c %s\n",val3.c_str(), val3.c_str(),this->son[i]->op,val2.c_str());
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
            std::string init_temp = this->son[i]->son[0]->son[0]->irgen_AddExp();
            print_indent();
            fprintf(yyout,"%s[%d] = %s\n", e->eeyore_id.c_str(), addr, init_temp.c_str());
            addr += 4;
            nval_temp++;
        } else{
            this->son[i]->irgen_InitVal(addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        print_indent();
        fprintf(yyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
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
            e->arr[nval_temp] = init_temp;
            print_indent();
            fprintf(yyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, init_temp);
            addr += 4;
            nval_temp++;
        } else{
            this->son[i]->irgen_ConstInitVal(addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        e->arr[nval_temp] = 0;
        print_indent();
        fprintf(yyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
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
                print_indent();
                fprintf(yyout,"%s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
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
                print_indent();
                fprintf(yyout,"%s = %s %s %s\n",val3.c_str(), val1.c_str(),op.c_str(),val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s %s %s\n",val3.c_str(), val3.c_str(),op.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

std::string AST::irgen_LAndExp(){
    std::string val1, val2, val3;
    val1 = this->son[0]->irgen_EqExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < this->son.size(); i+=2){
            val2 = this->son[i+1]->irgen_EqExp();
            if(i == 1){
                print_indent();
                fprintf(yyout,"%s = %s && %s\n",val3.c_str(), val1.c_str(),val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s && %s\n",val3.c_str(), val3.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

std::string AST::irgen_LOrExp(){
    std::string val1, val2, val3;
    val1 = this->son[0]->irgen_LAndExp();
    if(this->son.size() == 1){
        return val1;
    } else{
        val3 = "t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < this->son.size(); i+=2){
            val2 = this->son[i+1]->irgen_LAndExp();
            if(i == 1){
                print_indent();
                fprintf(yyout,"%s = %s || %s\n",val3.c_str(), val1.c_str(),val2.c_str());
            } else{
                print_indent();
                fprintf(yyout,"%s = %s || %s\n",val3.c_str(), val3.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

void AST::irgen_Stmt(){
    if(this->son.size() == 0){
        return;
    }
    if(this->son[0]->type == _RETURN){
        returned = true;
        if(this->son.size() == 1){
            print_indent();
            fprintf(yyout,"return\n");
        } else{
            std::string return_temp = this->son[1]->son[0]->irgen_AddExp();
            print_indent();
            fprintf(yyout,"return %s\n",return_temp.c_str());
        }
    } else if(this->son[0]->type == _LVal){
        std::string left_temp = this->son[0]->irgen_LVal(true);
        std::string right_temp = this->son[1]->son[0]->irgen_AddExp();
        print_indent();
        fprintf(yyout,"%s = %s\n",left_temp.c_str(),right_temp.c_str());
    } else if(this->son[0]->type == _Exp){
        this->son[0]->son[0]->irgen_AddExp();
    } else if(this->son[0]->type == _Block){
        this->son[0]->irgen_Block();
    } else if(this->son[0]->type == _WHILE){
        this->label_in = label;
        this->label_out = label+1;
        label += 2;
        label_in_global = this->label_in;
        label_out_global = this->label_out;
        fprintf(yyout,"l%d:\n",this->label_in);

        std::string cond_temp = this->son[1]->son[0]->irgen_LOrExp();
        print_indent();
        fprintf(yyout,"if %s == 0 goto l%d\n",cond_temp.c_str(),this->label_out);

        this->son[2]->irgen_Stmt();

        print_indent();
        fprintf(yyout,"goto l%d\n",this->label_in);
        fprintf(yyout,"l%d:\n",this->label_out);
    } else if(this->son[0]->type == _IF && this->son.size() == 5){
        this->label_in = label;
        this->label_out = label+1;
        label += 2;

        std::string cond_temp = this->son[1]->son[0]->irgen_LOrExp();
        print_indent();
        fprintf(yyout,"if %s == 0 goto l%d\n",cond_temp.c_str(),this->label_in);

        this->son[2]->irgen_Stmt();

        print_indent();
        fprintf(yyout,"goto l%d\n",this->label_out);

        fprintf(yyout,"l%d:\n",this->label_in);
        this->son[4]->irgen_Stmt();

        fprintf(yyout,"l%d:\n",this->label_out);
    } else if(this->son[0]->type == _IF && this->son.size() == 3){
        this->label_out = label;
        label++;

        std::string cond_temp = this->son[1]->son[0]->irgen_LOrExp();
        print_indent();
        fprintf(yyout,"if %s == 0 goto l%d\n",cond_temp.c_str(),this->label_out);

        this->son[2]->irgen_Stmt();

        fprintf(yyout,"l%d:\n",this->label_out);
    } else if(this->son[0]->type == _BREAK){
        print_indent();
        fprintf(yyout,"goto l%d\n",label_out_global);
    } else if(this->son[0]->type == _CONTINUE){
        print_indent();
        fprintf(yyout,"goto l%d\n",label_in_global);
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

//需要在函数开头打印所有声明变量语句，包括T变量和t变量
void AST::irgen_FuncDef(){
    ENTRY_FUNC *func_ptr = (ENTRY_FUNC *)this->son[1]->entry;

    print_indent();
    fprintf(yyout,"f_%s [%d]\n",func_ptr->id, func_ptr->NumberOfParam);

    indent++;
    p_i = 0;
    returned = false;
    print_decl(func_ptr->symtable,func_ptr->NumberOfTemp);
    this->son[this->son.size()-1]->irgen_Block();
    if(!returned){
        print_indent();
        fprintf(yyout,"return\n");
    }
    indent--;
    
    print_indent();
    fprintf(yyout,"end f_%s\n",this->son[1]->id);
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
                    std::string val_temp = ptr_temp->son[2]->son[0]->son[0]->irgen_AddExp();
                    print_indent();
                    fprintf(yyout,"%s = %s\n", entry_temp->eeyore_id.c_str(), val_temp.c_str());
                } else{
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = 0;
                    }
                }
            } else {
                if(ptr_temp->son.size() > 2){
                    entry_temp->arr = new int [entry_temp->size/4];
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
                fprintf(yyout,"%s = %d\n", entry_temp->eeyore_id.c_str(), entry_temp->val);
            } else {
                if(ptr_temp->son.size() > 2){
                    entry_temp->arr = new int [entry_temp->size/4];
                    ptr_temp->son[2]->irgen_ConstInitVal(0, 0, entry_temp);
                }
            }
        }
    }
}

void AST::irgen(){
    print_decl(root_symtable, NumberOfTemp_global);
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->type==_Decl){
            this->son[i]->irgen_Decl();
        } else if(this->son[i]->type==_FuncDef){
            this->son[i]->irgen_FuncDef();
        }
    }
}