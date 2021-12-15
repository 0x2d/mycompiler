#include"ast.h"
#include"symtable.h"
#include<stdio.h>
#include<string>
extern FILE *yyout;
extern TABLE *root_symtable;
extern TABLE *symtable_ptr;

AST *root;
int T_i = 0;
int t_i = 0;
int indent = 0;

void print_indent(){
    for(int indent_temp=0;indent_temp<indent;indent_temp++){
        fprintf(yyout,"  ");
    }
}

int valgen_UnaryExp(AST *p){
    //UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
    AST *ptr;
    if(p->son[0]->type == _PrimaryExp){
        ptr = p->son[0]; //PrimaryExp
        if(ptr->son[0]->type == _INT_CONST){
            return ptr->son[0]->val;
        } else if(ptr->son[0]->type == _LVal){
            if(ptr->son[0]->son.size() == 1){
                return ((ENTRY_VAL *)ptr->son[0]->son[0]->entry)->val;
            } else{
                //
            }
        }
        //
    }
    //
}

int valgen_MulExp(AST *p){
    int result;
    result = valgen_UnaryExp(p->son[0]);
    for(int i=1;i<p->son.size();i+=2){
        if(p->son[i]->op == '*'){
            result *= valgen_UnaryExp(p->son[i+1]);
        } else if(p->son[i]->op == '/'){
            result /= valgen_UnaryExp(p->son[i+1]);
        } else if(p->son[i]->op == '%'){
            result %= valgen_UnaryExp(p->son[i+1]);
        }
    }
    return result;
}

int valgen_AddExp(AST *p){
    int result;
    result = valgen_MulExp(p->son[0]);
    for(int i=1;i<p->son.size();i+=2){
        if(p->son[i]->op == '+'){
            result += valgen_MulExp(p->son[i+1]);
        } else if(p->son[i]->op == '-'){
            result -= valgen_MulExp(p->son[i+1]);
        }
    }
    return result;
}

int AST::irgen_UnaryExp(){
    //UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
    int val1;
    AST *ptr;
    if(this->son[0]->type == _PrimaryExp){
        ptr = this->son[0]; //PrimaryExp
        if(ptr->son[0]->type == _INT_CONST){
            print_indent();
            fprintf(yyout,"var t%d\n",t_i);
            print_indent();
            fprintf(yyout,"t%d = %d\n",t_i,ptr->son[0]->val);
            val1 = t_i;
            t_i++;
        } else if(ptr->son[0]->type == _LVal){
            if(ptr->son[0]->son.size() == 1){
                print_indent();
                fprintf(yyout,"var t%d\n",t_i);
                print_indent();
                fprintf(yyout,"t%d = T%d\n",t_i,((ENTRY_VAL *)ptr->son[0]->son[0]->entry)->t_n);
                val1 = t_i;
                t_i++;
            } else{
                //
            }
        }
        //
    }
    //
    return val1;
}

int AST::irgen_MulExp(){
    int val1, val2;
    val1 = this->son[0]->irgen_UnaryExp();
    for(int i=1;i<this->son.size();i+=2){
        val2 = this->son[i+1]->irgen_UnaryExp();
        print_indent();
        fprintf(yyout,"var t%d\n",t_i);
        if(this->son[i]->op == '*'){
            print_indent();
            fprintf(yyout,"t%d = t%d * t%d\n",t_i,val1,val2);
        } else if(this->son[i]->op == '/'){
            print_indent();
            fprintf(yyout,"t%d = t%d / t%d\n",t_i,val1,val2);
        } else if(this->son[i]->op == '%'){
            print_indent();
            fprintf(yyout,"t%d = t%d % t%d\n",t_i,val1,val2);
        }
        val1 = t_i;
        t_i++;
    }
    return val1;
}

int AST::irgen_AddExp(){
    int val1, val2;
    val1 = this->son[0]->irgen_MulExp();
    for(int i=1;i<this->son.size();i+=2){
        val2 = this->son[i+1]->irgen_MulExp();
        print_indent();
        fprintf(yyout,"var t%d\n",t_i);
        if(this->son[i]->op == '+'){
            print_indent();
            fprintf(yyout,"t%d = t%d + t%d\n",t_i,val1,val2);
        } else if(this->son[i]->op == '-'){
            print_indent();
            fprintf(yyout,"t%d = t%d - t%d\n",t_i,val1,val2);
        }
        val1 = t_i;
        t_i++;
    }
    return val1;
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
            int init_temp = this->son[i]->son[0]->son[0]->irgen_AddExp();
            print_indent();
            fprintf(yyout,"T%d[%d] = t%d\n", e->t_n, addr, init_temp);
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
        fprintf(yyout,"T%d[%d] = 0\n", e->t_n, addr);
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
            int init_temp = valgen_AddExp(this->son[i]->son[0]->son[0]);
            e->arr[nval_temp] = init_temp;
            print_indent();
            fprintf(yyout,"T%d[%d] = %d\n", e->t_n, addr, init_temp);
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
        fprintf(yyout,"T%d[%d] = 0\n", e->t_n, addr);
        addr += 4;
    }
}

void AST::irgen_BlockItem(){
    if(this->son[0]->type == _Decl){
        this->son[0]->irgen_Decl();
    } else{
        AST *ptr = this->son[0]; //Stmt
        if(ptr->son[0]->type == _RETURN){
            if(ptr->son.size() == 1){
                print_indent();
                fprintf(yyout,"return\n");
            } else{
                int return_temp = ptr->son[1]->son[0]->irgen_AddExp();
                print_indent();
                fprintf(yyout,"return t%d\n",return_temp);
            }
        }
    }
}

void AST::irgen_Block(){
    for(int i=0;i<this->son.size();i++){
        indent++;
        this->son[i]->irgen_BlockItem();
        indent--;
    }
}

void AST::irgen_FuncDef(){
    symtable_ptr = ((ENTRY_FUNC *)this->son[1]->entry)->symtable;
    if(this->son.size() == 3){
        print_indent();
        fprintf(yyout,"f_%s [0]\n",this->son[1]->id);
        this->son[2]->irgen_Block();
    } else{
        //
    }
    symtable_ptr = symtable_ptr->father;
}

void AST::irgen_Decl(){
    AST *ptr = this->son[0];
    if(ptr->type == _VarDecl){
        ptr = ptr->son[1];  //VarDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //VarDef
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            entry_temp->t_n = T_i;
            T_i++;
            if(ptr_temp->son[1]->son.size() == 0){
                entry_temp->size = 4;
                print_indent();
                fprintf(yyout,"var T%d\n", entry_temp->t_n);
                if(ptr_temp->son.size() > 2){
                    int val_temp = ptr_temp->son[3]->son[0]->son[0]->irgen_AddExp();
                    print_indent();
                    fprintf(yyout,"T%d = t%d\n", entry_temp->t_n, val_temp);
                } else{
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = 0;
                        print_indent();
                        fprintf(yyout,"T%d = %d\n", entry_temp->t_n, entry_temp->val);
                    }
                }
            } else {
                int size_temp = 1;
                int j_temp;
                for(int j=0;j<ptr_temp->son[1]->son.size();j++){
                    j_temp = valgen_AddExp(ptr_temp->son[1]->son[j]->son[0]);
                    entry_temp->shape.push_back(j_temp);
                    size_temp *= j_temp;
                }
                entry_temp->size = size_temp * 4;
                entry_temp->isArray = true;
                entry_temp->arr = new int [size_temp];
                print_indent();
                fprintf(yyout,"var %d T%d\n", entry_temp->size, entry_temp->t_n);
                ptr_temp->son[3]->irgen_InitVal(0, 0, entry_temp);
            }
        }
    } else if(ptr->type == _ConstDecl){
        ptr = ptr->son[2];  //ConstDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //ConstDef
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            entry_temp->t_n = T_i;
            T_i++;
            if(ptr_temp->son[1]->son.size() == 0){
                entry_temp->size = 4;
                print_indent();
                fprintf(yyout,"var T%d\n", entry_temp->t_n);
                entry_temp->val = valgen_AddExp(ptr_temp->son[3]->son[0]->son[0]);
                print_indent();
                fprintf(yyout,"T%d = %d\n", entry_temp->t_n, entry_temp->val);
            } else {
                int size_temp = 1;
                int j_temp;
                for(int j=0;j<ptr_temp->son[1]->son.size();j++){
                    j_temp = valgen_AddExp(ptr_temp->son[1]->son[j]->son[0]);
                    entry_temp->shape.push_back(j_temp);
                    size_temp *= j_temp;
                }
                entry_temp->size = size_temp * 4;
                entry_temp->isArray = true;
                entry_temp->arr = new int [size_temp];
                print_indent();
                fprintf(yyout,"var %d T%d\n", entry_temp->size, entry_temp->t_n);
                ptr_temp->son[3]->irgen_ConstInitVal(0, 0, entry_temp);
            }
        }
    }
}

void AST::irgen(){
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->type==_Decl){
            this->son[i]->irgen_Decl();
        } else if(this->son[i]->type==_FuncDef){
            this->son[i]->irgen_FuncDef();
        }
    }
}