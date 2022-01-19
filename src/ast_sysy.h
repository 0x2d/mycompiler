#ifndef AST_SYSY_H
#define AST_SYSY_H

#include<vector>
#include<string>

class ENTRY;
class ENTRY_VAL;
class ENTRY_FUNC;
class TABLE;

enum TYPE {
    _INT, _VOID, _CONST, _IF, _ELSE, _WHILE, _BREAK, _CONTINUE, _RETURN, _LE, 
    _GE, _EQ, _NE, _AND, _OR, _IDENT, _INT_CONST, _OP, _CompUnit, 
    _Decl, _ConstDecl, _ConstDef_temp, _BType, _ConstDef, _ConstExp_temp, _ConstInitVal, _ConstInitVal_temp, _VarDecl, _VarDef_temp, 
    _VarDef, _InitVal, _InitVal_temp, _FuncDef, _FuncFParams, _FuncFParam, _Block, _BlockItem_temp, _BlockItem, _Stmt, 
    _Exp, _Cond, _LVal, _PrimaryExp, _Number, _UnaryExp, _UnaryOp, _FuncRParams, _MulExp, _AddExp, _RelExp, 
    _EqExp, _LAndExp, _LOrExp, _ConstExp
};

class AST{
public:
    AST() = default;
    AST(TYPE t):type(t){}
    AST(TYPE t, char o):type(t), op(o) {}
    AST(TYPE t, int v):type(t), val(v) {}

    std::vector<AST *> son;
    TYPE type;
    char op;
    int val;
    std::string id;
    ENTRY *entry;
    int lineno;
    bool isint = false; //尚未实现
    int label_in;
    int label_in2;
    int label_out;
};

class ENTRY{
public:
    ENTRY() = default;
    ENTRY(std::string i, TABLE *t): id(i), table(t) {};

    std::string id;
    TABLE *table;
};

class TABLE{
public:
    TABLE() = default;
    TABLE(std::string s): space(s){};
    TABLE(std::string s, TABLE *f): space(s), father(f) {
        this->father->son.push_back(this);
    };

    bool Find(bool isVal, std::string id, bool recursive);
    ENTRY *FindAndReturn(bool isVal, std::string id);

    std::string space;
    std::vector<ENTRY_VAL *> val;
    std::vector<ENTRY_FUNC *> func;
    TABLE *father;
    std::vector<TABLE *> son;
};

class ENTRY_VAL: public ENTRY{
public:
    ENTRY_VAL(std::string i, TABLE *t, int s):ENTRY(i,t),size(s) {
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
    //int *arr; 实现const数组编译时确定值的路线之一，不太靠谱
};

class ENTRY_FUNC: public ENTRY{
public:
    ENTRY_FUNC(std::string i, TABLE *t, bool isr,TABLE *s, int nt, int np):ENTRY(i,t),isreturn(isr),symtable(s),NumberOfTemp(nt),NumberOfParam(np) {
        table->func.push_back(this);
    };
    
    TABLE *symtable;
    bool isreturn;
    int NumberOfParam;
    int NumberOfTemp;
};

#endif
