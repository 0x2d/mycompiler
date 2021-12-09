#include"ast.h"
#include<stdio.h>

AST *root;

void AST::print(){
    int size_temp = this->son.size();
    for(int i=0; i<size_temp; i++){
        this->son[i]->print();
    }
    printf("%d\n",this->type);
}