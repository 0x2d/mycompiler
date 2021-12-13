#include"ast.h"
#include<stdio.h>
extern FILE *yyout;
extern std::vector<TABLE *> symtable_list;
extern TABLE *symtable_ptr;

AST *root;
int T_i = 0;
int t_i = 0;

int valgen_UnaryExp(AST *p){
    //UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
    AST *ptr;
    if(p->son[0]->type == _PrimaryExp){
        ptr = p->son[0];
        if(ptr->son[0]->type == _INT_CONST){
            return ptr->son[0]->val;
        }
    }
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

void AST::irgen_FuncDef(){
    //
}

void AST::irgen_Decl(){
    AST *ptr = this->son[0];
    if(ptr->type == _VarDecl){
        //
    } else if(ptr->type == _ConstDecl){
        ptr = ptr->son[2];  //ConstDef_temp

        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //ConstDef
            ENTRY *entry_temp = ptr_temp->son[0]->entry;
            entry_temp->add_entry(symtable_ptr);
            entry_temp->isConst = true;
            if (entry_temp->T_num == -1){
                entry_temp->T_num = T_i;
                T_i++;
            }
            if(ptr_temp->son[1]->son.size() == 0){
                entry_temp->size = 4;
            } else {
                int size_temp = 1;
                int j_temp;
                for(int j=0;j<ptr_temp->son[1]->son.size();j++){
                    j_temp = valgen_AddExp(ptr_temp->son[1]->son[j]);
                    entry_temp->shape.push_back(j_temp);
                    size_temp *= j_temp;
                }
                entry_temp->size = size_temp * 4;
                entry_temp->arr = new int [size_temp];
            }

            if(entry_temp->shape.size() == 0){
                fprintf(yyout,"var T%d\n", entry_temp->T_num);
            } else{
                fprintf(yyout,"var %d T%d\n", entry_temp->size, entry_temp->T_num);
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