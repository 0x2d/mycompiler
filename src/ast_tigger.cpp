#include"ast_tigger.h"
#include<stdio.h>
#include<string>
#include<string.h>
#include"tigger.tab.hpp"
using namespace tigger;
extern FILE *tiggerin;
extern FILE *tiggerout;

AST *root_tigger;

//s0为保留寄存器，t0 t1 t2寄存器在eeyore2tigger阶段中使用
void AST::irgen_exp(int STK){
    if(this->son.size() == 4 && this->son[2]->type == _BinOp){
        //Reg '=' Reg BinOp Reg
        //Reg '=' Reg BinOp NUM
        std::string reg1, reg2, reg3, op;
        reg1 = this->son[0]->id;
        reg2 = this->son[1]->id;
        if(this->son[3]->type == _Reg){
            reg3 = this->son[3]->id;
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",this->son[3]->val);
            reg3 = "s0";
        }
        op = this->son[2]->op;
        if(op == "+"){
            fprintf(tiggerout,"  add    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "-"){
            fprintf(tiggerout,"  sub    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "*"){
            fprintf(tiggerout,"  mul    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "/"){
            fprintf(tiggerout,"  div    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "%"){
            fprintf(tiggerout,"  rem    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "<"){
            fprintf(tiggerout,"  slt    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == ">"){
            fprintf(tiggerout,"  sgt    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
        } else if(op == "<="){
            fprintf(tiggerout,"  sgt    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
            fprintf(tiggerout,"  seqz   %s, %s\n",reg1.c_str(),reg1.c_str());
        } else if(op == ">="){
            fprintf(tiggerout,"  slt    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
            fprintf(tiggerout,"  seqz   %s, %s\n",reg1.c_str(),reg1.c_str());
        } else if(op == "&&"){
            fprintf(tiggerout,"  snez   %s, %s\n",reg1.c_str(),reg2.c_str());
            fprintf(tiggerout,"  snez   s0, %s\n",reg3.c_str());
            fprintf(tiggerout,"  and    %s, %s, s0\n",reg1.c_str(),reg1.c_str());
        } else if(op == "||"){
            fprintf(tiggerout,"  or     %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
            fprintf(tiggerout,"  snez   %s, %s\n",reg1.c_str(),reg1.c_str());
        } else if(op == "!="){
            fprintf(tiggerout,"  xor    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
            fprintf(tiggerout,"  snez   %s, %s\n",reg1.c_str(),reg1.c_str());
        } else if(op == "=="){
            fprintf(tiggerout,"  xor    %s, %s, %s\n",reg1.c_str(),reg2.c_str(),reg3.c_str());
            fprintf(tiggerout,"  seqz   %s, %s\n",reg1.c_str(),reg1.c_str());
        }
    } else if(this->son.size() == 3 && this->son[1]->type == _OP){
        //Reg '=' OP Reg
        std::string reg1, reg2, op;
        reg1 = this->son[0]->id;
        reg2 = this->son[2]->id;
        op = this->son[1]->op;
        if(op == "-"){
            fprintf(tiggerout,"  neg    %s, %s\n",reg1.c_str(),reg2.c_str());
        } else if(op == "!"){
            fprintf(tiggerout,"  seqz   %s, %s\n",reg1.c_str(),reg2.c_str());
        }
    } else if(this->son.size() == 2 && this->son[1]->type == _Reg){
        //Reg '=' Reg
        std::string reg1, reg2, op;
        reg1 = this->son[0]->id;
        reg2 = this->son[1]->id;
        fprintf(tiggerout,"  mv     %s, %s\n",reg1.c_str(),reg2.c_str());
    } else if(this->son.size() == 2 && this->son[1]->type == _NUM){
        //Reg '=' NUM
        fprintf(tiggerout,"  li     %s, %d\n",this->son[0]->id.c_str(),this->son[1]->val);
    } else if(this->son.size() == 3 && this->son[0]->type == _Reg && this->son[1]->type == _NUM){
        //Reg '[' NUM ']' '=' Reg
        std::string reg1, reg2;
        reg1 = this->son[0]->id;
        reg2 = this->son[2]->id;
        int val = this->son[1]->val;
        if(val >= -2048 && val <= 2047){
            fprintf(tiggerout,"  sw     %s, %d(%s)\n",reg2.c_str(),val,reg1.c_str());
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",val);
            fprintf(tiggerout,"  add    s0, s0, %s\n",reg1.c_str());
            fprintf(tiggerout,"  sw     %s, (s0)\n",reg2.c_str());
        }
    } else if(this->son.size() == 3 && this->son[0]->type == _Reg && this->son[2]->type == _NUM){
        //Reg '=' Reg '[' NUM ']'
        std::string reg1, reg2;
        reg1 = this->son[0]->id;
        reg2 = this->son[1]->id;
        int val = this->son[2]->val;
        if(val >= -2048 && val <= 2047){
            fprintf(tiggerout,"  lw     %s, %d(%s)\n",reg1.c_str(),val,reg2.c_str());
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",val);
            fprintf(tiggerout,"  add    s0, s0, %s\n",reg2.c_str());
            fprintf(tiggerout,"  lw     %s, (s0)\n",reg1.c_str());
        }
    } else if(this->son[0]->type == _IF){
        //IF Reg LOGICOP Reg GOTO LABEL
        std::string reg1, reg2, op, label;
        reg1 = this->son[1]->id;
        reg2 = this->son[3]->id;
        op = this->son[2]->op;
        label = this->son[5]->id;
        if(op == "<"){
            fprintf(tiggerout,"  blt    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        } else if(op == ">"){
            fprintf(tiggerout,"  bgt    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        } else if(op == "<="){
            fprintf(tiggerout,"  ble    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        } else if(op == ">="){
            fprintf(tiggerout,"  bge    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        } else if(op == "!="){
            fprintf(tiggerout,"  bne    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        } else if(op == "=="){
            fprintf(tiggerout,"  beq    %s, %s, .%s\n",reg1.c_str(),reg2.c_str(),label.c_str());
        }
    } else if(this->son[0]->type == _GOTO){
        //GOTO LABEL
        fprintf(tiggerout,"  j      .%s\n",this->son[1]->id.c_str());
    } else if(this->son[0]->type == _LABEL){
        //LABEL ':'
        fprintf(tiggerout,".%s:\n",this->son[0]->id.c_str());
    } else if(this->son[0]->type == _CALL){
        //CALL FUNCTION
        fprintf(tiggerout,"  call   %s\n",this->son[1]->id.substr(2).c_str());
    } else if(this->son[0]->type == _RETURN){
        //RETURN
        if(STK >= -2044 && STK <= 2047){
            fprintf(tiggerout,"  lw     ra, %d(sp)\n",STK-4);
            fprintf(tiggerout,"  addi   sp, sp, %d\n",STK);
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",STK);
            fprintf(tiggerout,"  add    s0, s0, sp\n");
            fprintf(tiggerout,"  lw     ra, -4(s0)\n");
            fprintf(tiggerout,"  li     s0, %d\n", STK);
            fprintf(tiggerout,"  add    sp, sp, s0\n");
        }
        fprintf(tiggerout,"  ret\n");
    } else if(this->son[0]->type == _STORE){
        //STORE Reg NUM
        std::string reg = this->son[1]->id;
        int val = this->son[2]->val;
        if(val >= -512 && val <= 511){
            fprintf(tiggerout,"  sw     %s, %d(sp)\n",reg.c_str(),val*4);
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",val*4);
            fprintf(tiggerout,"  add    s0, sp, s0\n");
            fprintf(tiggerout,"  sw     %s, (s0)\n",reg.c_str());
        }
    } else if(this->son[0]->type == _LOAD && this->son[1]->type == _NUM){
        //LOAD NUM Reg
        std::string reg = this->son[2]->id;
        int val = this->son[1]->val;
        if(val >= -512 && val <= 511){
            fprintf(tiggerout,"  lw     %s, %d(sp)\n",reg.c_str(),val*4);
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",val*4);
            fprintf(tiggerout,"  add    s0, sp, s0\n");
            fprintf(tiggerout,"  lw     %s, (s0)\n",reg.c_str());
        }
    } else if(this->son[0]->type == _LOAD && this->son[1]->type == _VARIABLE){
        //LOAD VARIABLE Reg
        std::string reg, var;
        reg = this->son[2]->id;
        var = this->son[1]->id;
        fprintf(tiggerout,"  lui    %s, %%hi(%s)\n",reg.c_str(),var.c_str());
        fprintf(tiggerout,"  lw     %s, %%lo(%s)(%s)\n",reg.c_str(),var.c_str(),reg.c_str());
    } else if(this->son[0]->type == _LOADADDR && this->son[1]->type == _NUM){
        //LOADADDR NUM Reg
        std::string reg = this->son[2]->id;
        int val = this->son[1]->val;
        if(val >= -512 && val <= 511){
            fprintf(tiggerout,"  addi   %s, sp, %d\n",reg.c_str(),val*4);
        } else{
            fprintf(tiggerout,"  li     s0, %d\n",val*4);
            fprintf(tiggerout,"  add    %s, sp, s0\n",reg.c_str());
        }
    } else if(this->son[0]->type == _LOADADDR && this->son[1]->type == _VARIABLE){
        //LOADADDR VARIABLE Reg
        std::string reg, var;
        reg = this->son[2]->id;
        var = this->son[1]->id;
        fprintf(tiggerout,"  la     %s, %s\n",reg.c_str(),var.c_str());
    }
}

void AST::irgen_func(){
    int STK = (this->son[0]->son[2]->val / 4 + 1) * 16;
    std::string func_id = this->son[0]->son[0]->id.substr(2);
    fprintf(tiggerout,"  .text\n");
    fprintf(tiggerout,"  .align     2\n");
    fprintf(tiggerout,"  .global    %s\n",func_id.c_str());
    fprintf(tiggerout,"  .type      %s, @function\n",func_id.c_str());
    fprintf(tiggerout,"%s:\n",func_id.c_str());
    if(STK >= -2044 && STK <= 2047){
        fprintf(tiggerout,"  addi   sp, sp, -%d\n",STK);
        fprintf(tiggerout,"  sw     ra, %d(sp)\n",STK-4);
    } else{
        fprintf(tiggerout,"  li     s0, %d\n",STK);
        fprintf(tiggerout,"  sub    sp, sp, s0\n");
        fprintf(tiggerout,"  add    s0, s0, sp\n");
        fprintf(tiggerout,"  sw     ra, -4(s0)\n");
    }
    for(int i=0;i<this->son[1]->son.size();i++){
        this->son[1]->son[i]->irgen_exp(STK);
    }
    fprintf(tiggerout,"  .size      %s, .-%s\n",func_id.c_str(),func_id.c_str());
}

void AST::irgen_decl(){
    std::string var_id = this->son[0]->id;
    if(this->son.size() == 2){
        fprintf(tiggerout,"  .global    %s\n",var_id.c_str());
        fprintf(tiggerout,"  .section   .sdata\n");
        fprintf(tiggerout,"  .align     2\n");
        fprintf(tiggerout,"  .type      %s, @object\n",var_id.c_str());
        fprintf(tiggerout,"  .size      %s, 4\n",var_id.c_str());
        fprintf(tiggerout,"%s:\n",var_id.c_str());
        fprintf(tiggerout,"  .word      %d\n", this->son[1]->val);
    } else{
        fprintf(tiggerout,"  .comm      %s, %d, 4\n",var_id.c_str(),this->son[2]->val);
    }
}

void AST::irgen(){
    for(int i=0;i<this->son.size();i++){
        if(this->son[i]->type == _GlobalVarDecl){
            this->son[i]->irgen_decl();
        } else if(this->son[i]->type == _FunctionDef){
            this->son[i]->irgen_func();
        }
    }
}

void codegen_riscv(char *input_file_path, char *output_file_path){
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file = fopen(output_file_path,"w");
    tiggerin = input_file;
    tiggerout = output_file;

    tiggerparse();
    root_tigger->irgen();

    fclose(input_file);
    fclose(output_file);
    tiggerin = stdin;
    tiggerout = stdout;
}
