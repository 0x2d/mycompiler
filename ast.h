#ifndef AST_H
#define AST_H

#include<vector>
#include<string>
#include"symtable.h"

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
    AST(TYPE t, char *i):type(t), id(i) {}
    AST(TYPE t, int v):type(t), val(v) {}
    
    void irgen();
    void irgen_Decl();
    void irgen_FuncDef();
    void irgen_Block();
    void irgen_Stmt();
    void irgen_ConstInitVal(int addr, int layer, ENTRY_VAL *e);
    void irgen_InitVal(int addr, int layer, ENTRY_VAL *e);
    std::string irgen_AddExp();
    std::string irgen_MulExp();
    std::string irgen_UnaryExp();
    std::string irgen_LVal(bool isleft);
    std::string irgen_LOrExp();
    std::string irgen_LAndExp();
    std::string irgen_EqExp();
    std::string irgen_RelExp();

    std::vector<AST *> son;
    TYPE type;
    char op;
    int val;
    char *id;
    ENTRY *entry;

    bool isint = false;

    int label_in;
    int label_out;
};

#endif