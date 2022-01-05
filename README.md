# MyCompiler

## 20220105 提交
- 合并了mycompiler_e2t和mycompiler_t2r的部分
- 修改了mycompiler_e2t部分param指令不区分整型和指针的BUG
- 修改了sysy2eeyore部分数组初始化时使用临时变量的bug，但是还是有一些漏洞
- 评测系统100分，性能测试524.92s

## 20211224 提交
- 修改对于运行时函数的指针传参bug
- 评测系统100分

## 20211224 提交
- 修改break和continue的bug
- 修改全局变量的初始化bug
- 评测系统98分

## 20211223 提交
- 完成逻辑运算的短路机制
- 修改负数的bug
- 修改计算字符串长度的bug
- 修改函数调用传参顺序的bug
- 评测系统96分

## 20211222 提交
- 完成函数调用翻译
- 解决递归问题
- 每个函数的形参编号应单独计算
- 必须return
- 解决除0错误
- 支持八进制和十六进制
- 区分指针调用和值调用
- 评测系统85分

## 20211221 提交
- 完成控制语句的翻译
- 完善了对数组操作语句的翻译
- 修复了一些BUG
- 通过测试023

## 20211218 提交
- 根据助教给的最简单的方法，完成了Cond语句的翻译。
- 在语法分析时刻完成对常量整数的赋值，但还没想好常量数组怎么处理。
- 通过测试021

## 待解决的问题
- 表达式的中间代码生成只得到一个临时变量，而不能生成一个表达式。
- 常量数组赋值编译时处理
- 常量折叠