/*
 * 变量与可变性
 *
 * 1. 用 let 声明一个不可变变量 x，赋值为 5，然后打印它
 *
 * 2. 用 let mut 声明一个可变变量 y，赋值为 10，修改为 20，打印两次
 *
 * 3. 声明一个常量 MAX_COUNT，类型 u32，值 100，打印它
 *    思考：常量与 let 声明的不可变变量有什么区别？
 *
 * 4. 演示变量遮蔽（shadowing）：声明一个变量 name 为 "hello"，
 *    然后再次声明同名变量覆盖为 42（不同类型），打印两次
 *
 * 5. 一次 let 声明多个变量（解构）：
 *    声明元组 (a, b, c) = (1, 2.0, "three")，分别打印三个值
 *
 * 6. 思考题（不写代码，在注释中回答）：
 *    以下代码能否编译？为什么？
 *    let a = 1;
 *    a = 2;
 */
pub fn hello() {
    let x = 5;
    println!("x：{}", x);
    let mut y = 10;
    println!("y: {}", y);
    y = 20;
    println!("y: {}", y);
    const MAX_COUNT: u32 = 100;
    println!("MAX_COUNT: {}", MAX_COUNT);

    let name = "hello";
    println!("name: {}", name);
    let name = 42;
    println!("name: {}", name);

    let (a, b, c) = (1, 2.0, "three");
    println!("a: {}, b: {}, c: {}", a, b, c);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hello() {
        hello();
    }
}
