#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<vector>
extern void yyerror(char *str);

class ENTRY;
class ENTRY_VAL;
class ENTRY_FUNC;
class TABLE;

class ENTRY{
public:
    ENTRY() = default;
    ENTRY(char *i, TABLE *t): id(i), table(t) {};

    char *id;
    TABLE *table;
};

class TABLE{
public:
    TABLE() = default;
    TABLE(char *s): space(s){};
    TABLE(char *s, TABLE *f): space(s), father(f) {
        this->father->son.push_back(this);
    };

    bool isSame(bool isVal, char *id, bool recursive);
    ENTRY *FindAndReturn(bool isVal, char *id);

    char *space;
    std::vector<ENTRY_VAL *> val;
    std::vector<ENTRY_FUNC *> func;
    TABLE *father;
    std::vector<TABLE *> son;
};

class ENTRY_VAL: public ENTRY{
public:
    ENTRY_VAL(char *i, TABLE *t):ENTRY(i,t) {
        if(table->isSame(true,id,false)){
            yyerror("ConstVar was decleared before\n");
        } else{
            table->val.push_back(this);
            isConst = false;
            isArray = false;
        }
    };

    bool isConst;
    bool isArray;
    int t_n;
    int size;
    std::vector<int> shape;
    int val;
    int *arr;
};

class ENTRY_FUNC: public ENTRY{
public:
    ENTRY_FUNC(char *i, TABLE *t):ENTRY(i,t) {
        table->func.push_back(this);
    };

    int label;
    TABLE *symtable;
};

#endif