# MyCompiler
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
- 无法识别八进制和十六进制数字，不确定对于0和负数应该怎么处理，暂时加入了正则表达式。
- 表达式的中间代码生成只得到一个临时变量，而不能生成一个表达式。
- 中间代码生成未完成
- 常量折叠