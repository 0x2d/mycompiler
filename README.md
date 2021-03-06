# mycompiler

## 介绍
mycompiler编译器为北京大学2021秋季编译原理课程大作业的实现。<br><br>
***注意：在这之后，助教重新设计了lab*** <br><br>
编译器将SysY代码通过Eeyore和Tigger两种中间表示，转换为等价的RISC-V代码。虽然通过了自动评测机，但仍然可能有大量BUG。<br>
源语言、目标语言以及中间表示的语法规范和功能参考助教建立的[在线文档](https://pku-minic.github.io/online-doc/#/)。

## 构建
环境：`Ubuntu build-essential flex bison`
```shell
cd ./mycompiler
make
```

## 使用
```shell
cd ./mycompiler
./build/compiler -S <inputfile> -o <outputfile>
```
编译器会在`./mycompiler`目录下生成相应的`.eeyore .tigger .S`文件

## 代码结构
- src
    - main.cpp  #程序入口代码
    - lexer.l
    - parser.y
    - ast_sysy.h
    - ast_sysy.cpp #SysY2Eeyore部分
    - eeyore.l
    - eeyore.y
    - ast_eeyore.h
    - ast_eeyore.cpp #Eeyore2Tigger部分
    - tigger.l
    - tigger.y
    - ast_tigger.h
    - ast_tigger.cpp #Tigger2RISC-V部分
- test.c  #测试样例
- test.sh #测试脚本

## 提交记录

### 20220119 提交
- 完善了README
- 将代码生成函数从AST中独立出来，作为static函数，增强文件代码隔离
- 使用std::string替换char *变量，解决malloc.c:2379: sysmalloc: Assertion错误

### 20220105 提交
- 合并了mycompiler_e2t和mycompiler_t2r的部分
- 修改了mycompiler_e2t部分param指令不区分整型和指针的BUG
- 修改了sysy2eeyore部分数组初始化时使用临时变量的bug，但是还是有一些漏洞
- 评测系统100分，性能测试524.92s

### 20211230 提交
- 修改一些bug
- 需要加入时间函数的处理
- 评测100分

### 20211229 提交
- 假设数组操作括号中均为常数
- 想了一堆都没用，还是按照最简单的写。所有变量存在栈里，寄存器只用作临时存储。

### 20211225 提交
- 修改对于运行时函数的指针传参bug
- 评测系统100分

### 20211224 提交
- 修改break和continue的bug
- 修改全局变量的初始化bug
- 评测系统98分

### 20211223 提交
- 完成逻辑运算的短路机制
- 修改负数的bug
- 修改计算字符串长度的bug
- 修改函数调用传参顺序的bug
- 评测系统96分

### 20211222 提交
- 完成函数调用翻译
- 解决递归问题
- 每个函数的形参编号应单独计算
- 必须return
- 解决除0错误
- 支持八进制和十六进制
- 区分指针调用和值调用
- 评测系统85分

### 20211221 提交
- 完成控制语句的翻译
- 完善了对数组操作语句的翻译
- 修复了一些BUG
- 通过测试023

### 20211218 提交
- 根据助教给的最简单的方法，完成了Cond语句的翻译。
- 在语法分析时刻完成对常量整数的赋值，但还没想好常量数组怎么处理。
- 通过测试021

## 待解决的问题
- 表达式的中间代码生成只得到一个临时变量，而不能生成一个表达式。
- 常量数组赋值编译时处理
- 常量折叠
- 所有局部变量都存在栈里，位置是固定分配的；当需要用到时就读到寄存器里，被修改时就设置dirty位；置换寄存器时选择最旧的，如果没有修改就直接替换，有修改就写回内存。注意，如果采用loadaddr和数组访问的方式修改变量，则无需写回，因为这是直接在内存上修改。
- ……