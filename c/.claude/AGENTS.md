# CLAUDE.md

C 语言入门学习项目，包含 7 个循序渐进的 C 语言示例文件。

## 常用命令

```bash
# 编译全部源文件
make all

# 清理编译产物
make clean
```

## 项目结构

```
src/          # C 源文件 (01-basics.c ~ 07-preprocess-file.c)
dist/         # 编译输出的可执行文件
```

## 编译配置

- 编译器: GCC
- 标准: C23 (-std=c23)
- 警告: -Wall -Wextra -pedantic
- 源文件: src/lessons/, 输出: dist/

## 源文件说明

- 01-basics.c: 基本类型与格式化 I/O
- 02-operators-flow.c: 运算符与控制流
- 03-array-string.c: 数组与字符串
- 04-pointer.c: 指针
- 05-struct-union.c: 结构体 / 联合体 / 枚举 / typedef
- 06-func-memory.c: 函数 / 动态内存 / 错误处理
- 07-preprocess-file.c: 预处理器 / 文件 I/O / 多文件编译
