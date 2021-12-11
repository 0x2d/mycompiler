#include"ast.h"
#include<stdio.h>
extern FILE *yyout;

AST *root;
int T_i = 0;
int t_i = 0;

void AST::irgen_FuncDef(){
    ;
}

void AST::irgen_Decl(){
    AST *ptr = this->son[0];
    if(ptr->type == _VarDecl){
        ptr = ptr->son[1];  //VarDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //VarDef
            fprintf(yyout,"Var ");
            int size_temp = ptr_temp->son[1]->son.size() * 4;
            if(size_temp != 0){
                fprintf(yyout,"%d T", size_temp);
            } else{
                fprintf(yyout, "T");
            }
            ENTRY *entry_temp = ptr_temp->son[0]->entry;
            if (entry_temp->T_num == -1){
                entry_temp->T_num = T_i;
                T_i++;
                fprintf(yyout, "%d\n", entry_temp->T_num);
            }
        }
    } else if(ptr->type == _ConstDecl){
        ;
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