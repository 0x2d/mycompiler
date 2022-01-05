#ifndef AST_TIGGER_H
#define AST_TIGGER_H

#include<vector>
#include<string>

namespace tigger{

enum TYPE {
    _IF, _RETURN, _VARIABLE, _NUM, _MALLOC, _END, _FUNCTION, _LOGICOP, _OP, _GOTO, _LABEL, _CALL, _STORE, _LOAD, _LOADADDR, _Reg,
    _Program, _GlobalVarDecl, _FunctionDef, _FunctionHeader, _FunctionEnd,
    _Expressions, _Expression, _BinOp
};

class AST{
public:
    AST() = default;
    AST(TYPE t):type(t){}

    void irgen();
    void irgen_decl();
    void irgen_func();
    void irgen_exp(int STK);

    std::vector<AST *> son;
    TYPE type;
    std::string op;
    int val;
    std::string id;
};

}

#endif