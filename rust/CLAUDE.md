# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在此代码仓库中工作时提供指导，输出语言为中文

## 项目概述

Rust 学习项目，使用 Cargo workspace 按主题组织多个子 crate，涵盖基础语法、进阶特性、API 应用和综合练习。

## 构建和开发命令

```bash
# 构建整个 workspace
cargo build

# 以发布模式构建
cargo build --release

# 构建/运行/测试/检查指定 crate（推荐）
cargo build -p <crate-name>
cargo run -p <crate-name>            # 仅 bin crate
cargo test -p <crate-name>
cargo check -p <crate-name>

# 运行特定测试（支持按名称过滤）
cargo test -p exercise variable::var_one

# 全 workspace
cargo test
cargo check
cargo fmt
cargo clippy
```

### 工作流程
1. 频繁 `cargo check` 捕获编译错误
2. `cargo test` 验证功能正确性
3. 提交前 `cargo fmt && cargo clippy` 保持代码质量

## 项目结构

```
rust-indoor/
├── Cargo.toml                    # workspace 根配置
├── crates/
│   ├── base/                     # 基础语法：变量、函数、控制流、格式化、trait 等
│   │   ├── Cargo.toml
│   │   └── src/
│   │       ├── lib.rs
│   │       ├── controll_stream.rs
│   │       ├── format.rs
│   │       ├── function.rs
│   │       ├── self_def_type.rs
│   │       ├── str_and_ope.rs
│   │       ├── traits.rs
│   │       └── variable.rs
│   │
│   ├── advance/                  # 进阶特性（lib）
│   │   ├── Cargo.toml
│   │   └── src/lib.rs
│   │
│   ├── api/                      # API 应用（bin）
│   │   ├── Cargo.toml
│   │   └── src/main.rs
│   │
│   ├── core/                     # 核心概念（lib）
│   │   ├── Cargo.toml
│   │   └── src/lib.rs
│   │
│   ├── utils/                    # 工具函数（lib）
│   │   ├── Cargo.toml
│   │   └── src/lib.rs
│   │
│   └── exercise/                 # 综合练习（lib）
│       ├── Cargo.toml
│       ├── .zed/
│       │   ├── tasks.json        # Zed 任务：运行模块/方法级别测试
│       │   └── debug.json        # Zed 调试配置（CodeLLDB）
│       └── src/
│           ├── lib.rs            # 模块入口，含 prelude 重导出
│           └── variable/
│               ├── mod.rs        # 声明 var_one 子模块
│               └── var_one.rs    # hello() + 内联测试
```

## 代码架构

### workspace 配置（根 Cargo.toml）
- `resolver = "2"`：新版依赖解析器
- `members = ["crates/*"]`：通配包含所有子 crate，新增无需修改
- `[workspace.package]`：共享 version(0.1.0)、edition(2021)、license(MIT)
- `[workspace.dependencies]`：共享依赖，子 crate 通过 `dep.workspace = true` 引用

### 各 crate 说明

| Crate | 类型 | 说明 |
|-------|------|------|
| `base` | lib | 变量、函数、控制流、格式化、trait、自定义类型等基础语法 |
| `advance` | lib | 进阶特性练习 |
| `api` | bin | API 应用入口 |
| `core` | lib | 核心概念练习 |
| `utils` | lib | 工具函数 |
| `exercise` | lib | 综合练习，模块化组织，测试写在源码文件中（`#[cfg(test)]`） |

### 关键依赖

| 依赖 | 版本 | 用途 | 使用方 |
|------|------|------|--------|
| `ferris-says` | 0.3.1 | ASCII 艺术文本输出 | base, exercise |
| `calamine` | 0.26 | Excel 文件读取 | — |
| `rust_xlsxwriter` | 0.79 | Excel 文件写入 | — |

### 测试约定

- 测试**写在源码文件中**，与功能代码紧邻（`#[cfg(test)] mod tests`），不另建 `tests/` 目录
- 使用 `crate::prelude::*`（内部测试）或直接 `use super::*` 导入被测函数
- 过滤测试：`cargo test -p <crate> <filter>`，如 `cargo test -p exercise variable::var_one`

### Zed 配置

`crates/<name>/.zed/` 下的配置仅在打开对应 crate 子目录时生效：
- **tasks.json**：常用运行任务（测试模块/方法）
- **debug.json**：CodeLLDB 调试配置，`program` 指向稳定的 bin 路径（`target/debug/<name>.exe`）

## 重要说明

1. **新增 crate**：在 `crates/` 下新建目录，添加 `Cargo.toml`（继承 workspace 配置）和 `src/lib.rs`（或 `src/main.rs`）即可，无需修改根 `Cargo.toml`。

2. **库 vs 二进制**：lib crate 无 `main.rs`，只能 `cargo check/test` 不能 `cargo run`。需要可运行入口时追加 `src/main.rs`（保持 lib.rs 中的功能代码不变）。

3. **编译状态**：所有 crate 均可正常编译。
