/*
 * 变量
 */

// 常量
const _MAX_POINTS: u32 = 100_000;
// 静态变量，全局变量，可以被修改，但需要unsafe
static mut _STATIC_VAR: u32 = 0;

pub fn variable() {
    // 变量绑定，不可变变量
    let x = 5;
    println!("The value of x is: {}", x);

    // 变量绑定可以修改
    let mut y = 10;
    println!("The value of y is: {}", y);
    y = 20; // 这是同一个y
    println!("The value of y is: {}", y);

    // 隐藏变量
    let x = 5;
    let x = x + 1; // 这是一个新的x，就不能访问x=5
    let x = x * 2;
    println!("The value of x is: {}", x);

    // 隐藏变量并修改类型
    let spaces = "   ";
    let spaces = spaces.len();
    println!("The value of spaces is: {}", spaces);

    // 作用域内遮蔽
    let x = 10;
    {
        let x = 20;
        println!("{}", x); // 20
    }
    println!("{}", x); // 10
}

// 代码块赋值
pub fn code_batch() {
    let x = 5u32;
    let y = {
        let x_squared = x * x;
        let x_cube = x_squared * x;

        // 这个表达式将被赋值给 `y`
        x_cube + x_squared + x
    };

    // let z = {
    //     // 分号抑制了这个表达式，`()` 被赋值给 `z`,可以使用占位符 ‘_’ 防止警告
    //     2 * x；
    // };

    println!("x 是 {:?}", x);
    println!("y 是 {:?}", y);
    // println!("z 是 {:?}", z);
}
