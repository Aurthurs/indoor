/*
* 字面量和运算符
* 字面值表示：
   整数 1
   浮点数 1.2
   字符 'a'
   字符串 "abc"
   布尔值 true
   单元类型 ()
* 整数十六进制、八进制或二进制前缀：0x、0o 或 0b
* 1_000 与 1000 相同，0.000_001 与 0.000001 相同
* 科学计数法 E-notation，例如 1e6、7.6e-4。相关类型是 f64。
* u32 后缀来表示该字面值是一个无符号 32 位整数，使用 i32 后缀来表示它是一个有符号 32 位整数。
*/

// 数字操作
pub fn num_operation() {
    // 整数加法
    println!("1 + 2 = {}", 1u32 + 2);

    // 整数减法
    println!("1 - 2 = {}", 1i32 - 2);
    // TODO ^ 尝试将 `1i32` 改为 `1u32`，看看为什么类型很重要：会报错 attempt to compute `1_u32 - 2_u32`, which would overflow

    // 科学记数法
    println!("1e4 is {}, -2.5e-3 is {}", 1e4, -2.5e-3);

    // 短路布尔逻辑
    println!("true AND false is {}", true && false);
    println!("true OR false is {}", true || false);
    println!("NOT true is {}", !true);

    // 位运算
    println!("0011 AND 0101 is {:04b}", 0b0011u32 & 0b0101);
    println!("0011 OR 0101 is {:04b}", 0b0011u32 | 0b0101);
    println!("0011 XOR 0101 is {:04b}", 0b0011u32 ^ 0b0101);
    println!("1 << 5 is {}", 1u32 << 5);
    println!("0x80 >> 2 is 0x{:x}", 0x80u32 >> 2);

    // 使用下划线来提高可读性！
    println!("One million is written as {}", 1_000_000u32);
}

// 元组
pub fn tuple_operation() {
    // 创建元组
    let tuple = (1, 2, 3);

    // 访问元组元素
    println!("First element: {}", tuple.0);
    println!("Second element: {}", tuple.1);

    // 解构元组
    let (x, y, z) = tuple;
    println!("x: {}, y: {}, z: {}", x, y, z);
}

// 数组和切片 类型签名 [T; length]
pub fn array_and_slice_operation() {
    // 创建数组
    let array = [1, 2, 3];

    // 固定大小的数组（类型签名是多余的）,变量名前加下划线来消除未被使用的变量警告
    let _xs: [i32; 5] = [1, 2, 3, 4, 5];

    // 所有元素可以初始化为相同的值
    let _ys: [i32; 10] = [0; 10];

    // 访问数组元素s
    println!("First element: {}", array[0]);
    println!("Second element: {}", array[1]);

    // 解构数组
    let [x, y, z] = array;
    println!("x: {}, y: {}, z: {}", x, y, z);

    // 创建切片
    let slice = &array[1..3];

    // 访问切片元素
    println!("First element of slice: {}", slice[0]);
    println!("Second element of slice: {}", slice[1]);
}
