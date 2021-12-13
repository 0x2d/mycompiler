#ifndef AST_H
#define AST_H

#include<vector>
#include"symtable.h"
extern TABLE *symtable_ptr;

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
    AST(TYPE t, char *i):type(t) {
        this->entry = new ENTRY(i);
    }
    AST(TYPE t, int v):type(t), val(v) {}
    
    void irgen();
    void irgen_Decl();
    void irgen_FuncDef();

    std::vector<AST *> son;
    TYPE type;
    char op;
    int val;
    ENTRY *entry;
};

#endif