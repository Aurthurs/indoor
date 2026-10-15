/*
* 自定义类型
* Rust 的自定义数据类型主要通过以下两个关键字来创建：
  struct：定义结构体
  enum：定义枚举
* 常量也可以通过 const 和 static 关键字来创建
*/

/*
* 结构体
*
* 使用 struct 关键字可以创建三种类型的结构体（"structs"）：
   元组结构体：本质上是具名元组。
   普通结构体：经典的 C 语言风格结构体
   单元结构体：没有字段，在泛型中很有用。
*/

// 这个属性用于隐藏未使用代码的警告。
#![allow(dead_code)]

// 单元结构体
struct Unit;

impl Unit {
    fn message(&self, msg: &str) {
        println!("{}", msg);
    }
}

// 元组结构体
struct Pair(i32, f32);

// 普通结构体
struct Point {
    x: f32,
    y: f32,
}

pub fn structs() {
    // 实例化一个单元结构体
    let _unit = Unit;
    _unit.message("这是一个单元结构体");

    // 实例化一个元组结构体
    let pair = Pair(1, 0.1);

    // 解构一个元组结构体
    let Pair(integer, decimal) = pair;
    println!("pair 包含 {:?} 和 {:?}", integer, decimal);
}

/* =================================================================
 * 枚举
 */
enum WeekDay {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
}

// 相当于重写toString方法
impl std::fmt::Display for WeekDay {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            WeekDay::Monday => write!(f, "Monday"),
            WeekDay::Tuesday => write!(f, "Tuesday"),
            WeekDay::Wednesday => write!(f, "Wednesday"),
            WeekDay::Thursday => write!(f, "Thursday"),
            WeekDay::Friday => write!(f, "Friday"),
            WeekDay::Saturday => write!(f, "Saturday"),
            WeekDay::Sunday => write!(f, "Sunday"),
        }
    }
}

impl WeekDay {
    fn message(&self, msg: &str) {
        println!("{} is a {}", self, msg);
    }
}

pub fn enums() {
    let today = WeekDay::Monday;
    today.message("今天是工作日");
}
