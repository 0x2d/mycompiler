#ifndef SYMTABLE_H
#define SYMTABLE_H

#include<vector>
#include<string>
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

    bool Find(bool isVal, char *id, bool recursive);
    ENTRY *FindAndReturn(bool isVal, char *id);

    char *space;
    std::vector<ENTRY_VAL *> val;
    std::vector<ENTRY_FUNC *> func;
    TABLE *father;
    std::vector<TABLE *> son;
};

class ENTRY_VAL: public ENTRY{
public:
    ENTRY_VAL(char *i, TABLE *t, int s):ENTRY(i,t),size(s) {
        table->val.push_back(this);
        isConst = false;
        isArray = false;
        isParam = false;
    };

    bool isConst;
    bool isArray;
    bool isParam;
    std::string eeyore_id;
    int size;
    std::vector<int> shape;
    int val;
    int *arr;
};

class ENTRY_FUNC: public ENTRY{
public:
    ENTRY_FUNC(char *i, TABLE *t, bool isr,TABLE *s, int nt, int np):ENTRY(i,t),isreturn(isr),symtable(s),NumberOfTemp(nt),NumberOfParam(np) {
        table->func.push_back(this);
    };

    TABLE *symtable;
    bool isreturn;
    int NumberOfParam;
    int NumberOfTemp;
};

#endif