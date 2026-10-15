/*
 * scanf-vs-scanf_s.c — scanf 与 scanf_s 对照
 *
 * scanf 是传统 C89 标准函数，不检查缓冲区边界。
 * scanf_s 是 C11 Annex K 安全版本，%s/%c/%[ 需额外传入缓冲区大小。
 * 对于 %d/%f 等数值格式，两者用法完全相同。
 */

// _CRT_SECURE_NO_WARNINGS 已在 Makefile 中通过 -D 编译选项定义
#include "../common.h"
#include <stdio.h>

int main(void) {
  setup_console();

  /* === 数值读取：scanf 与 scanf_s 用法一致 === */
  printf("=== 数值读取（两者相同） ===\n");
  int num;
  printf("输入整数: ");
  scanf("%d", &num);
  scanf_s("%d", &num); // %d 无需缓冲区大小参数
  printf("你输入了: %d\n\n", num);

  /* === 字符串读取：关键区别 === */
  printf("=== 字符串读取（关键区别） ===\n");
  char buf[5]; // 只有 5 字节

  // scanf 读取字符串——不检查边界，输入过长会溢出
  // scanf("%s", buf);        // 危险！输入超过 4 字符就会覆盖相邻内存

  // scanf_s 读取字符串——必须传入 sizeof(buf)，超出部分截断
  printf("输入字符串（最多 %zu 字符）: ", sizeof(buf) - 1);
  scanf_s("%s", buf, (unsigned)sizeof(buf));
  printf("你输入了: %s\n", buf);
  // 注意：输入过长时，scanf_s 不会截断而是报错并清空缓冲区

  /* === 字符读取 === */
  printf("\n=== 字符读取 ===\n");
  char ch;
  printf("输入一个字符: ");
  scanf_s(" %c", &ch, (unsigned)sizeof(ch)); // %c 也需要大小参数
  printf("你输入了: '%c'\n", ch);

  return 0;
}
