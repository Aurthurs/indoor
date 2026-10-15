/*
 * 01-basics.c — 基本类型与格式化 I/O
 *
 * 本课学习 C 语言的核心数据类型、sizeof 运算符、
 * printf/scanf 格式化输入输出，以及 C23 新增的内建类型。
 */

#include "../common.h"
#include <stdbool.h> // C23 起 bool/true/false 为关键词，此头文件保持兼容
#include <stddef.h>  // NULL 空指针宏
#include <stdio.h>

int main(void) {
  setup_console();
  /* ---- 整型家族 ---- */
  // 整型是 C 最基本的类型，signed/unsigned 决定是否有符号位
  char c = 'A';                         // 1 字节，实际存的是 ASCII 码 65
  short s = 32767;                      // 通常 2 字节
  int i = 42;                           // 通常 4 字节，最常用的整型
  long l = 2147483647L;                 // 至少 4 字节
  long long ll = 9223372036854775807LL; // 至少 8 字节

  // unsigned 变体：无符号位，正数范围翻倍
  unsigned int ui = 4294967295U;

  // 不同整型的大小因平台而异，sizeof 返回字节数（类型用 %zu）
  printf("=== 整型 sizeof ===\n");
  printf("char:      %zu 字节\n", sizeof(char));
  printf("short:     %zu 字节\n", sizeof(s));  // 用 s 演示 short 大小
  printf("int:       %zu 字节\n", sizeof(i));  // 用 i 演示 int 大小
  printf("long:      %zu 字节\n", sizeof(l));  // 用 l 演示 long 大小
  printf("long long: %zu 字节\n", sizeof(ll)); // 用 ll 演示 long long 大小

  /* ---- 浮点型 ---- */
  // 注意：浮点数不能精确表示所有实数，比较时不能用 ==
  float f = 3.1415926f;         // 单精度，后缀 f
  double d = 3.141592653589793; // 双精度，默认
  long double ld = 3.14159265358979323846L;

  printf("\n=== 浮点型 sizeof ===\n");
  printf("float:       %zu 字节\n", sizeof(f));
  printf("double:      %zu 字节\n", sizeof(d));
  printf("long double: %zu 字节\n", sizeof(ld));

  /* ---- printf 格式说明符 ---- */
  // 格式说明符必须与参数类型严格匹配，否则行为未定义
  printf("\n=== 格式化输出 ===\n");
  printf("字符: %c\n", c);
  printf("有符号十进制: %d\n", i);
  printf("无符号十进制: %u\n", ui);
  printf("十六进制:     0x%x\n", 255);   // 输出 ff
  printf("大写的十六进制: 0x%X\n", 255); // 输出 FF
  printf("浮点数(默认):   %f\n", d);     // 默认 6 位小数
  printf("浮点数(2位):    %.2f\n", d);   // 保留 2 位
  printf("科学计数法:     %e\n", d);
  printf("字符串:     %s\n", "Hello, 世界");
  printf("指针地址:   %p\n", (void *)&i); // %p 需要 void* 类型

  /* ---- const 限定符 ---- */
  // const 让编译器帮你在编译期发现意外的修改
  const double pi = 3.14159;
  // pi = 3.0;  // 编译错误：不能修改 const 变量
  printf("\n=== const 限定符 ===\n");
  printf("pi = %.5f（不可修改）\n", pi);

  /* ---- C23 内建 bool 类型 ---- */
  // C23 之前需要用 <stdbool.h>，C23 起 bool/true/false 是关键词
  bool is_valid = true;
  printf("\n=== C23 bool 类型 ===\n");
  printf("is_valid = %s\n", is_valid ? "true" : "false");
  // printf 没有 %b，布尔值仍以 0/1 存储，用三元运算符打印

  /* ---- 空指针 ---- */
  // NULL 是空指针宏（通常是 ((void*)0)），表示指针不指向任何有效内存
  int *np = NULL;
  printf("\n=== 空指针 ===\n");
  printf("NULL 指向: %p\n", (void *)np);

  /* ---- 类型转换：整数除法截断 ---- */
  // C 中 int/int 结果仍是 int，小数直接丢弃（不是四舍五入）
  // 这是 C 新手最高频的陷阱之一：把整数除法结果赋给 double 变量
  int a = 5, b = 2;
  int int_div = a / b;         // 第一步：整数除法 → 2（小数已丢弃）
  double bad = int_div;        // 第二步：int 隐式转 double → 2.0（为时已晚）
  double good = (double)a / b; // 正确：先转换操作数，触发浮点除法 → 2.5
  // 常见错误写法（一行版）：
  //   double x = a / b;  ← 看似浮点运算，实则先整除得 2 再转 double = 2.0

  printf("\n=== 类型转换 ===\n");
  printf("常见错误 int/int → double: %.1f（小数在第一步就丢了）\n", bad);
  printf("正确做法 (double)int / int: %.1f\n", good);

  /* ---- scanf_s 读取输入 ---- */
  // scanf_s 是 scanf 的安全版本（C11 Annex K），此处演示读取整型
  int user_input = 0;
  printf("\n=== scanf_s 输入示例 ===\n");
  printf("请输入一个整数: ");
  // %d 格式下 scanf_s 用法与 scanf 一致
  if (scanf_s("%d", &user_input) == 1) {
    printf("你输入了: %d\n", user_input);
  } else {
    printf("输入格式不正确\n");
  }

  return 0;
}
