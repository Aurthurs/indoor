/*
 * trait = 能力说明书 + 编译期强约束
 * 有点像java中的接口，只要impl，就必须按照trait的定义类型和方法去实现
 * rust中没有继承，完全靠泛型+trait实现编译时多态
 */
pub trait MyTrait {
    fn my_method(&self);
}

struct _Bird {
    name: String,
}

struct _Fish {
    name: String,
}

impl MyTrait for _Bird {
    fn my_method(&self) {
        println!("Bird: {}", self.name);
    }
}

impl MyTrait for _Fish {
    fn my_method(&self) {
        println!("Fish: {}", self.name);
    }
}

/*
* 派生：编译器可以通过 #[derive] 属性为某些 trait 提供基本实现
* 以下是可派生的 trait 列表：
  比较 trait：Eq、PartialEq、Ord、PartialOrd。
  Clone，通过复制 &T 创建 T。
  Copy，使类型具备"复制语义"而不是"移动语义"。
  Hash，从 &T 计算哈希值。
  Default，创建一个数据类型的空实例。
  Debug，使用 {:?} 格式化器来格式化一个值。

  可以理解为lombook的@Data等注解，使当前类自动实现方法
*/
