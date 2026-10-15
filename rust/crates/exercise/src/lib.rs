//! exercise crate

// 模块声明
pub mod variable;

/**
 * prelude：集中重导出常用项
 * 外部可通过 `use exercise::prelude::*;` 一键导入
 */
pub mod prelude {
    pub use crate::variable::var_one::hello;
}
