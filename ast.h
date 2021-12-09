#ifndef AST_H
#define AST_H

#include<vector>

enum TYPE {
    _INT, _VOID, _CONST, _IF, _ELSE, _WHILE, _BREAK, _CONTINUE, _RETURN, _LE, _GE, _EQ, _NE, _AND, _OR, _IDENT, _INT_CONST, _OP,
    _BType, _PROG, _CompUnit, _Decl, _ConstDecl, _ConstDef_temp, _ConstDef, _ConstExp_temp, _ConstInitVal, _ConstInitVal_temp,
    _VarDecl, _VarDef_temp, _VarDef, _InitVal, _InitVal_temp, _FuncDef, _FuncFParams, _FuncFParam, _Block, _BlockItem_temp,
    _BlockItem, _Stmt, _Exp, _Cond, _AddExp, _MulExp, _UnaryExp, _PrimaryExp, _LVal, _UnaryOp, _FuncRParams,_RelExp, 
    _EqExp, _LAndExp, _LOrExp, _ConstExp
};

class AST{
public:
    AST() = default;
    AST(TYPE t):type(t){}
    AST(TYPE t, char o):type(t), op(o) {}
    AST(TYPE t, char *i):type(t), id(i) {}
    AST(TYPE t, int v):type(t), val(v) {}
    
    void print();

    std::vector<AST *> son;
    TYPE type;
    char op;
    int val;
    char *id;
};

#endif