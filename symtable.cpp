#include"symtable.h"
#include<vector>

TABLE *root_symtable;
TABLE *symtable_ptr;

void ENTRY::add_entry(TABLE *t){
    this->table = t;
    t->name.push_back(this);
}