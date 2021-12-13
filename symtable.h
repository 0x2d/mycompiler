#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<vector>

class ENTRY;
class TABLE;

class ENTRY{
public:
    ENTRY() = default;
    ENTRY(char *i): id(i) {
        T_num = -1;
        isFunc = false;
        isConst = false;
        val = 0;
        size = 0;
    };

    void add_entry(TABLE *t);

    char *id;
    TABLE *table;

    int T_num;
    bool isConst;
    int val;
    int size;
    std::vector<int> shape;
    int *arr;

    bool isFunc;
};

class TABLE{
public:
    TABLE() = default;
    TABLE(char *s): space(s) {};

    char *space;
    std::vector<ENTRY *> name;
};

#endif