/*
 * 02-operators-flow.c — 运算符与控制流
 *
 * C 是"靠近硬件"的语言，运算符直接映射 CPU 指令。
 * 理解运算符优先级和控制流是写出正确 C 代码的基础。
 */

#include <stdbool.h>
#include <stdio.h>
#include "../common.h"

int main(void) {
  setup_console();
  /* ---- 算术运算符 ---- */
  // 注意：整数除法会截断小数部分，取模 % 只能用于整型
  printf("=== 算术运算符 ===\n");
  int a = 10, b = 3;
  printf("加: %d + %d = %d\n", a, b, a + b);
  printf("减: %d - %d = %d\n", a, b, a - b);
  printf("乘: %d * %d = %d\n", a, b, a * b);
  printf("除: %d / %d = %d（整数除法，截断小数）\n", a, b, a / b);
  printf("模: %d %% %d = %d（取余数，仅用于整数）\n", a, b, a % b);

  /* ---- 关系与逻辑运算符 ---- */
  // 关系运算符返回 0（假）或 1（真）
  // 逻辑运算符 && 和 || 有短路求值：左边能确定结果时右边不执行
  printf("\n=== 关系与逻辑运算符 ===\n");
  bool t = true, f = false;
  printf("true  && true  = %d\n", t && true);
  printf("true  || false = %d\n", t || f);
  printf("!true          = %d\n", !t);

  // 短路求值演示：右边不会被计算
  int x = 0;
  printf("短路求值 (false && ++x): x = %d（x 未变，因为 ++x 被短路跳过）\n", x);
  printf("短路求值 (true  || ++x): x = %d（x 也未变，因为 || 左边为真已确定）\n", x);

  /* ---- 位运算符 ---- */
  // C 的核心特色之一，直接操作二进制，常用于嵌入式/驱动/协议解析
  printf("\n=== 位运算符 ===\n");
  unsigned char flags = 0b00001111;  // 15（C23 支持 0b 二进制字面量）
  printf("原始值:   0x%02X (%d)\n", flags, flags);
  printf("左移 <<2: 0x%02X (%d) —— 每左移一位相当于乘 2\n", flags << 2, flags << 2);
  printf("右移 >>2: 0x%02X (%d) —— 每右移一位相当于除 2\n", flags >> 2, flags >> 2);
  printf("按位与 &0xF0: 0x%02X —— 提取高 4 位\n", flags & 0xF0);
  printf("按位或 |0xF0: 0x%02X —— 设置高 4 位\n", flags | 0xF0);
  printf("按位异或 ^0xFF: 0x%02X —— 翻转所有位\n", flags ^ 0xFF);
  printf("按位取反 ~flags: 0x%02X —— 0 变 1，1 变 0\n", (unsigned char)~flags);

  /* ---- 赋值与复合赋值 ---- */
  printf("\n=== 赋值与复合赋值 ===\n");
  int n = 10;
  n += 5;   // 等价于 n = n + 5
  printf("n += 5 → %d\n", n);
  n >>= 2;  // 等价于 n = n >> 2
  printf("n >>= 2 → %d\n", n);

  /* ---- if / else if / else ---- */
  printf("\n=== if / else if / else ===\n");
  int score = 85;
  if (score >= 90) {
    printf("成绩 %d: 优秀\n", score);
  } else if (score >= 75) {
    printf("成绩 %d: 良好\n", score);
  } else if (score >= 60) {
    printf("成绩 %d: 及格\n", score);
  } else {
    printf("成绩 %d: 不及格\n", score);
  }

  /* ---- switch / case ---- */
  // 注意：case 后必须有 break，否则会「穿透」执行下一个 case
  printf("\n=== switch / case ===\n");
  int day = 3;
  switch (day) {
    case 1:  printf("星期一\n"); break;
    case 2:  printf("星期二\n"); break;
    case 3:  printf("星期三\n"); break;
    case 4:
    case 5:  // 注意：多个 case 共享同一段代码（有意的不写 break）
      printf("工作日后期\n");
      break;
    default: printf("周末或无效\n"); break;
  }

  /* ---- for 循环 ---- */
  printf("\n=== for 循环 ===\n");
  printf("1 到 5：");
  for (int i = 1; i <= 5; i++) {
    printf("%d ", i);
  }
  printf("\n");

  // 逗号运算符：在 for 中同时更新多个变量
  printf("双变量循环：");
  for (int i = 0, j = 10; i < 5; i++, j--) {
    printf("(%d,%d) ", i, j);
  }
  printf("\n");

  /* ---- while / do-while ---- */
  // while：先判断再执行（可能一次都不执行）
  // do-while：先执行一次再判断（至少执行一次）
  printf("\n=== while 循环 ===\n");
  int count = 3;
  while (count > 0) {
    printf("while: 还剩 %d 次\n", count);
    count--;
  }

  printf("\n=== do-while 循环 ===\n");
  count = 0;
  do {
    printf("do-while: count = %d（至少执行一次）\n", count);
  } while (count > 0);

  /* ---- break / continue ---- */
  printf("\n=== break / continue ===\n");
  printf("1~10 偶数：");
  for (int i = 1; i <= 10; i++) {
    if (i % 2 != 0) continue;  // 跳过奇数
    if (i > 8) break;           // 超过 8 就停止
    printf("%d ", i);
  }
  // 预期输出：2 4 6 8
  printf("\n");

  /* ---- goto 跳出多层循环 ---- */
  // goto 在现代 C 中主要用途是跳出深层嵌套和统一错误处理
  printf("\n=== goto 跳出多层循环 ===\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i == 1 && j == 1) {
        goto found;  // 直接从内层跳出所有循环
      }
      printf("(%d,%d) ", i, j);
    }
  }
found:
  // 预期输出：(0,0) (0,1) (0,2) (1,0)
  printf("<-- 在此处跳出\n");

  return 0;
}
