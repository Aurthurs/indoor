/*
 * 闭包 = 函数 + 捕获上下文的能力 的一个匿名函数
 * 闭包优先通过引用捕获变量，在两个||之间为外部的变量，可以为空
 * move关键字可以强制闭包获取变量的所有权 move || {}
 *
 * 赋值 / 传参 / 返回值，默认是 move，如果类型实现了 Copy，那 move 会退化成 copy
 * i32、u32、bool、char、浮点数、以及只由这些组成的元组，全部是 Copy。
 */
pub fn closure() {
    let add_one = |x| x + 1;
    let result = add_one(5);
    println!("Result: {}", result);
}
