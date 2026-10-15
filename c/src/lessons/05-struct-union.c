/*
 * 05-struct-union.c — 结构体 / 联合体 / 枚举 / typedef
 *
 * struct 将多个不同数据组合成一个整体，是构建复杂数据的基础。
 * union 让多个成员共享同一块内存，enum 给整数起有意义的名字。
 * typedef 创建类型别名，提高代码可读性。
 */

#include "../common.h"
#include <stdio.h>
#include <string.h>

/* ---- typedef 类型别名 ---- */
// 为已有类型起新名字，对比 TS 的 type/interface
typedef unsigned int uint;
typedef char *string_t; // 注意：容易误用，建议在指针类型上谨慎使用

/* ---- struct 结构体 ---- */
// 将多个相关数据打包为一个整体
typedef struct {
  char name[32];
  int age;
  double salary;
} Employee;

// 注意：结构体成员之间有填充，sizeof(Employee) 不等于成员大小之和
// 原因: CPU 访问对“对齐地址”更快（甚至必须）
void print_employee(const Employee *e) {
  // 用 -> 通过指针访问结构体成员
  printf("  姓名: %s, 年龄: %d, 薪资: %.2f\n", e->name, e->age, e->salary);
}

/* ---- union 联合体 ---- */
// 所有成员共享同一块内存，任意时刻只有一个是有效的
typedef union {
  int i_val;
  double d_val;
  char str[16];
} Value;

int main(void) {
  setup_console();
  /* ---- struct 使用 ---- */
  printf("=== struct 结构体 ===\n");
  Employee alice = {"Alice", 28, 85000.0}; // 初始化
  Employee bob;
  // 使用 strncpy_s 安全复制，并手动确保 '\0' 结尾
  strncpy_s(bob.name, sizeof(bob.name), "Bob", sizeof(bob.name) - 1);
  bob.name[sizeof(bob.name) - 1] = '\0';
  bob.age = 35;
  bob.salary = 95000.0;

  printf("员工信息:\n");
  print_employee(&alice);
  print_employee(&bob);

  /* ---- 内存对齐 ---- */
  // 结构体成员之间有填充字节以保证对齐(一般为4的倍数)，sizeof 可能比预期大
  printf("\n=== 内存对齐 ===\n");
  typedef struct {
    char c; // 1 字节,起始偏移 0,对齐4,占用字节范围[0..3] 3个字节(垃圾值/未定义)
    int i;  // 4 字节，起始偏移 4,对齐4,4+4=8,占用字节范围[4..7]
    char d; // 1 字节, 起始偏移 8,8+1=9,对齐4,占用字节范围[8..11]
  } Padded; // 这个结构体共占 12字节
  printf("sizeof(char+int+char) = %zu\n",
         sizeof(char) + sizeof(int) + sizeof(char));
  printf("sizeof(Padded) = %zu（通常为 12，因为对齐填充）\n", sizeof(Padded));
  // 注意：合理安排成员顺序可以减少填充,一般把较大的放前面
  // typedef struct {
  //     int i;   // 4字节
  //     char c;  // 1+4=5,偏移 3
  //     char d;  // 偏移 5
  //     // 末尾填充到 4 的倍数 → 8 字节
  // } BetterPadded; // 共占 8字节

  /* ---- 结构体数组 ---- */
  printf("\n=== 结构体数组 ===\n");
  Employee team[2] = {{"Charlie", 30, 72000.0}, {"Diana", 26, 68000.0}};
  for (int i = 0; i < 2; i++) {
    printf("team[%d]: ", i);
    print_employee(&team[i]);
  }

  /* ---- 嵌套结构体 ---- */
  printf("\n=== 嵌套结构体 ===\n");
  typedef struct {
    char city[20];
    char street[40];
  } Address;

  typedef struct {
    char name[32];
    Address addr; // 结构体嵌套
  } Person;

  Person p = {"张三", {"北京", "朝阳路100号"}};
  printf("%s 住在 %s %s\n", p.name, p.addr.city, p.addr.street);

  /* ---- union 联合体 ---- */
  // 所有成员共享同一块内存，同一时间只用一个
  printf("\n=== union 联合体 ===\n");
  Value v;
  printf("sizeof(Value) = %zu（取最大成员的大小）\n", sizeof(Value));

  v.i_val = 42; // 写入 int
  printf("存入 int: v.i_val = %d\n", v.i_val);

  v.d_val = 3.14; // 覆盖为 double
  printf("存入 double: v.d_val = %.2f\n", v.d_val);
  // 注意：此时读 v.i_val 得到的是无意义值（double 的二进制表示被错当 int 解读）
  printf("再读 v.i_val = %d（已损坏，因为内存被 double 覆盖了）\n", v.i_val);

  /* ---- enum 枚举 ---- */
  // 给整数常量起有意义的名字
  printf("\n=== enum 枚举 ===\n");
  typedef enum {
    STATUS_OK = 200,
    STATUS_NOT_FOUND = 404,
    STATUS_ERROR = 500
  } HttpStatus;

  HttpStatus status = STATUS_OK;
  printf("status = %d\n", status);

  // 自动递增：不赋值时从 0 开始递增
  typedef enum {
    MONDAY,    // 0
    TUESDAY,   // 1
    WEDNESDAY, // 2
    THURSDAY,  // 3
    FRIDAY,    // 4
    SATURDAY,  // 5
    SUNDAY     // 6
  } Weekday;
  printf("WEDNESDAY = %d\n", WEDNESDAY);
  Weekday today = FRIDAY;
  printf("today (FRIDAY) = %d\n", today);

  /* ---- C23 复合字面量 (Compound Literals) ---- */
  // 创建临时的无名结构体/数组对象
  printf("\n=== 复合字面量 (C23) ===\n");
  // 直接传递临时结构体
  print_employee(&(Employee){"临时员工", 22, 30000.0});

  return 0;
}
