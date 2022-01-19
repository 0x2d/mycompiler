#ifndef AST_EEYORE_H
#define AST_EEYORE_H

#include<vector>
#include<string>

enum TYPE {
    _IF, _RETURN, _VAR, _NUM, _SYMBOL, _END, _FUNCTION, _LOGICOP, _OP, _GOTO, _LABEL, _PARAM, _CALL,
    _Program, _Declaration, _Initialization, _FunctionDef, _FunctionHeader, _Statements, _FunctionEnd,
    _Statement, _Expression, _RightValue, _BinOp
};

class ENTRY;
class FUNC;

class AST{
public:
    AST() = default;
    AST(TYPE t):type(t){}

    std::vector<AST *> son;
    TYPE type;
    std::string op;
    int val;
    std::string id;
    ENTRY *entry;
};

class ENTRY{
public:
    ENTRY() = default;
    ENTRY(std::string i):id(i){
        this->reg = -1;
        this->isinit = false;
        this->global = false;
        this->array = false;
    }

    std::string id;
    bool global;
    bool array;
    int reg;
    int stack;
    int size;
    //用于初始化
    int val;
    int *init;
    bool isinit;
};

class FUNC{
public:
    FUNC() = default;
    FUNC(std::string i, int p):id(i),pnum(p){
        this->stack_size = 0;
    }
    
    std::string id;
    int pnum;
    std::vector<ENTRY *>table;
    int stack_size;
};

#endif
