#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<vector>

class ENTRY;
class TABLE;

class ENTRY{
public:
    ENTRY() = default;
    ENTRY(char *i, TABLE *t): id(i),table(t) {
        this->T_num = -1;
        isFunc = false;
        isConst = false;
    };

    char *id;
    int T_num;
    bool isFunc;
    bool isConst;
    TABLE *table;
};

class TABLE{
public:
    TABLE() = default;
    TABLE(char *f_i): func_id(f_i) {};

    char *func_id;
    std::vector<ENTRY *> content;
};

#endif