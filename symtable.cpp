#include"symtable.h"
#include<vector>
#include<string.h>

TABLE *root_symtable;
TABLE *symtable_ptr;

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
        //
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
        //
    }
}