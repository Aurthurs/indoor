// 循环-loop
pub fn stream_loop() {
    let mut counter = 0;

    let loop_value = loop {
        if counter == 0 {
            counter += 2;
            println!("从{}开始循环", counter);
            continue;
        }
        counter += 1;

        if counter == 10 {
            // 可以将循环的值放在break后面进行返回，末尾的分号不变
            break counter * 2;
        }
    };
    println!("loop的返回值{}", loop_value);
}

// for与迭代器
// for循环
pub fn stream_for() {
    let mut counter = 0;

    // 取0-9，可以加上等号0..=10，取0-10
    for i in 0..10 {
        counter += 1;
        println!("当前值为{}", i);
    }
    println!("for循环的返回值{}", counter);
}

/*
 * 迭代器的三种方法区别
 * 1. iter()：元素类型为&T，不可变引用元素地址，不消耗集合，不改变元素
 * 2. into_iter()：元素类型为T，遍历时集合被消耗（迭代完不能在使用），拿到值本身（拿到元素后原来位置就什么都没有了）
 * 3. iter_mut()：元素类型为&Tmut，可变引用元素地址，原地修改元素值，后续所有读取，都会看到前面修改后的值
 *
 * 集合就是一个盒子，里面有很多苹果（元素），不可变引用就是连接这个苹果的线，可以有多根，但可变引用只能有一根，因为可变引用是独占的，不能同时存在多个可变引用。
 * 集合消耗就是每次遍历都会从盒子里将苹果拿走，每次遍历都会消耗集合，所以不能同时存在多个迭代器，后面这个盒子就是不能用的
 */
pub fn stream_iterator() {
    let mut counter = 0;

    // iter(): 只能看，不能动
    let vec0 = vec![1, 2, 3, 4, 5];
    for i in vec0.iter() {
        counter += *i;
        println!("当前值为{}，counter为{}", i, counter);
    }

    // into_iter()：把盒子拆开，把里面的东西一个个拿出来
    let vec1 = vec![1, 2, 3, 4, 5];
    for i in vec1.into_iter() {
        counter += i;
        println!("当前值为{},counter为{}", i, counter);
    }

    // iter_mut()：可以改，但引用必须是唯一的
    let mut vec2 = vec![1, 2, 3, 4, 5];
    for i in vec2.iter_mut() {
        *i += 2;
        counter += *i;
        println!("当前值为{},counter为{}", i, counter);
    }

    for i in vec2.iter_mut() {
        println!("当前值为{}", i);
    }
}

/*
 * match 模式匹配：必须匹配所有情况
 */

pub fn match_deconstruction_tuple() {
    let triple = (0, -2, 3);
    match triple {
        (0, y, z) => println!("第一个是 `0`，`y` 是 {:?}，`z` 是 {:?}", y, z),
        (1, ..) => println!("第一个是 `1`，其余的不重要"),
        (.., 2) => println!("最后一个是 `2`，其余的不重要"),
        (3, .., 4) => println!("第一个是 `3`，最后一个是 `4`，其余的不重要"),
        // `..` 可用于忽略元组中的其余部分
        _ => println!("它们是什么并不重要"),
        // `_` 表示不将值绑定到变量
    }
}

pub fn match_deconstruction_array() {
    let array = [3, -2, 6];
    match array {
        // 将第二个和第三个元素分别绑定到相应的变量
        [0, second, third] => println!("array[0] = 0，array[1] = {}，array[2] = {}", second, third),
        // 单个值可以用 _ 忽略
        [1, _, third] => println!("array[0] = 1，array[2] = {}，array[1] 被忽略了", third),
        // 你也可以绑定一部分值并忽略其余的
        [-1, second, ..] => println!("array[0] = -1，array[1] = {}，其他所有的都被忽略了", second),
        // 或者将它们存储在另一个数组/切片中（类型取决于正在匹配的值的类型）
        [3, second, tail @ ..] => {
            println!("array[0] = 3，array[1] = {}，其他元素是 {:?}", second, tail)
        }
        // 绑定第一个和最后一个值，并将其余的存储在一个单独的数组中
        [first, middle @ .., last] => println!(
            "array[0] = {}，中间部分 = {:?}，array[2] = {}",
            first, middle, last
        ),
    }
}

/*
 * 解构与引用
 * 与C语言有很大的区别，& 只表示你暂时可以看/改别人的东西，* 可以解引用使用这个引用的值
 * 在C语言中，&就是个地址，你想怎么办都行
 */
pub fn reference() {
    // reference: &i32   —— 临时引用，栈里会生成一个临时值 4，r1借用了它
    let r1 = &4;
    println!("r1: &i32 r1= {:?}", r1);
    println!("r1: &i32 *r1= {:?}", *r1);
    // reference: i32    —— 纯值，没有借用、生命周期等，最安全、最朴素的写法
    let r2 = 4;
    println!("r2: i32 = {:?}", r2);
    // reference: &i32   —— 模式绑定成引用，等效于let tmp = 4; let r2 = &tmp;就是解构时将值变为引用，更安全
    let ref r3 = 4;
    println!("r3: &i32 = {:?}", r3);
}
