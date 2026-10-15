# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

TypeScript 入门学习项目，包含 7 个循序渐进的 TypeScript 示例文件。

## 常用命令

```bash
# 编译 TypeScript
npx tsc

# 监听模式编译
npx tsc --watch
```

## 项目结构

```
src/          # TypeScript 源文件 (01-basics.ts ~ 07-async.ts)
dist/         # 编译输出的 JavaScript 文件
```

## 编译配置

- 目标: ES2020, CommonJS 模块
- 严格模式已启用 (strict: true)
- skipLibCheck: true
- 源文件: src/, 输出: dist/

## 源文件说明

- 01-basics.ts: 基础类型
- 02-union-type.ts: 联合类型
- 03-literal.ts: 字面量类型
- 04-generic.ts: 泛型
- 05-advance-util.ts: 高级工具类型
- 06-enums.ts: 枚举
- 07-async.ts: 异步编程
