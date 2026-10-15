# indoor

多语言学习项目合集，按语言分为 5 个子目录，各自独立组织、互不依赖

| 目录 | 语言 / 技术栈 | 内容 |
|------|--------------|------|
| `bash/` | Shell | 脚本语法练习与课后习题 |
| `c/` | C + Makefile | 基础语法与对比示例 |
| `rust/` | Rust workspace | 按主题组织的多个 crate |
| `ts/` | TypeScript | 7 个渐进示例 + Supabase 练习 |
| `vue/` | Vue 3 + Vite | 前端工程化脚手架 |

## bash

```text
scripts/    # 数组、条件、字符串、变量等语法示例
exercise/   # 课后习题
```

直接用 `bash scripts/variable.sh` 运行

## c

```text
src/lessons/        # 01-basics ~ 07-preprocess-file，基础语法
src/comparison/     # 对比示例
dist/               # 编译输出（已忽略）
```

```bash
make          # 编译全部
make clean    # 清理
```

单模块可用 `make -f Makefile.lessons`、`make -f Makefile.comparison`

## rust

Cargo workspace，成员在 `crates/` 下自动发现：

```text
crates/base/        # 基础语法（变量、函数、trait、流控制等）
crates/advance/     # 进阶特性
crates/api/         # API 应用
crates/core/        # 核心练习
crates/exercise/    # 课后习题
crates/utils/       # 工具
```

```bash
cargo build                # 构建整个 workspace
cargo run -p <crate-name>  # 运行指定 crate
cargo test -p <crate-name> # 测试指定 crate
```

详见 `rust/CLAUDE.md`

## ts

```text
src/lessons/   # 01-basics ~ 07-async，渐进示例
src/supabase/  # Supabase 练习
dist/          # 编译输出（已忽略）
```

```bash
npx tsc         # 编译
npx tsc --watch # 监听模式
```

需要 `ts/.env` 配置 Supabase 连接参数

## vue

Vue 3 + Vite + TypeScript + Tailwind CSS 4 + Element Plus，使用 pnpm 管理

```bash
pnpm install    # 安装依赖
pnpm dev        # 开发服务器
pnpm build      # 类型检查 + 构建
pnpm generate   # plop 代码生成
```
