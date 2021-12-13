#include"symtable.h"
#include<vector>

std::vector<TABLE *> symtable_list;
TABLE *symtable_ptr;

void ENTRY::add_entry(TABLE *t){
    this->table = t;
    t->name.push_back(this);
}