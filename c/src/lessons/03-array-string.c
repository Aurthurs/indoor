/*
 * 03-array-string.c — 数组与字符串
 *
 * C 的数组是连续内存块，字符串是 '\0' 结尾的 char 数组。
 * 理解数组的内存布局和字符串的终止符是避免缓冲区溢出的关键。
 */

#include <stdio.h>
#include <string.h> // strlen strncpy strncat strcmp strchr
#include "../common.h"

// 注意：数组作为函数参数时退化为指针，sizeof 无法获取真实大小
void print_array_info(int arr[], size_t len) {
  // arr 在这里已退化为 int*，sizeof(arr) 返回指针大小（通常 8）
  // 注意：sizeof(arr) 在函数参数上返回的是指针大小，不是数组大小
  (void)arr;  // arr 仅用于演示参数退化
  printf("实际数组内容: ");
  for (size_t i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  setup_console();
  /* ---- 一维数组 ---- */
  // 数组在栈上分配，大小在编译时确定
  printf("=== 一维数组 ===\n");
  int nums[5] = {10, 20, 30, 40, 50};  // 初始化列表
  printf("数组占用总字节数: sizeof(nums) = %zu\n", sizeof(nums));
  printf("元素个数: sizeof(nums) / sizeof(nums[0]) = %zu\n",
         sizeof(nums) / sizeof(nums[0]));

  // 注意：数组越界不会报错，C 不做边界检查
  printf("遍历数组: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", nums[i]);
  }
  printf("\n");

  /* ---- 数组退化为指针 ---- */
  // 将数组传给函数时退化为指针，必须额外传递长度
  printf("\n=== 数组作为参数：退化为指针 ===\n");
  printf("main 中 sizeof(nums) = %zu（真实数组大小）\n", sizeof(nums));
  print_array_info(nums, 5);

  /* ---- 多维数组 ---- */
  // C 采用行优先存储：matrix[0][0], matrix[0][1], matrix[1][0], ...
  printf("\n=== 多维数组（行优先） ===\n");
  int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
  };
  printf("2×3 矩阵：\n");
  for (int i = 0; i < 2; i++) {
    printf("  第 %d 行: ", i);
    for (int j = 0; j < 3; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  /* ---- C 字符串：以 '\0' 结尾的 char 数组 ---- */
  // 关键：字符串长度 = 有效字符数 + 1（'\0'），'\0' 占用 1 字节
  printf("\n=== C 字符串 ===\n");
  char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 手动加 '\0'
  char str2[6] = "Hello";   // 编译器自动加 '\0'，效果同上
  // 注意：str3 指向只读数据段，修改会段错误
  const char *str3 = "Hello";  // 指针指向字面量（只读！）
  printf("str1 = %s, 长度 = %zu\n", str1, strlen(str1));
  printf("str2 = %s, 长度 = %zu\n", str2, strlen(str2));
  printf("str3 = %s（指向只读内存，不能修改）\n", str3);
  // 注意：strlen 不算 '\0'，sizeof 算 '\0'
  printf("sizeof(str1) = %zu（包含 '\\0'）\n", sizeof(str1));
  printf("strlen(str1) = %zu（不包含 '\\0'）\n", strlen(str1));

  /* ---- <string.h> 常用函数 ---- */
  printf("\n=== string.h 常用函数 ===\n");

  // strncpy + 手动补 '\0'：现代 C 中安全复制字符串的正确方式
  char dest[20];
  strncpy(dest, "Hello", sizeof(dest) - 1);
  dest[sizeof(dest) - 1] = '\0';
  printf("strncpy: dest = \"%s\"\n", dest);

  // strncpy 限制复制长度防止溢出，但不会自动补 '\0'
  char safe_dest[6];
  strncpy(safe_dest, "Hello World", sizeof(safe_dest) - 1);
  safe_dest[sizeof(safe_dest) - 1] = '\0';  // 确保以 '\0' 结尾
  printf("strncpy 截断: safe_dest = \"%s\"\n", safe_dest);

  // strncat：安全拼接，限制最多追加的字符数
  char buffer[30] = "Hello";
  strncat(buffer, " World", sizeof(buffer) - strlen(buffer) - 1);
  printf("strncat: buffer = \"%s\"\n", buffer);

  // strcmp：比较字符串（返回 0 表示相等）
  printf("strcmp(\"abc\", \"abc\") = %d（相等返回 0）\n", strcmp("abc", "abc"));
  printf("strcmp(\"abc\", \"abd\") = %d（不等返回非零）\n", strcmp("abc", "abd"));

  // strchr：查找字符
  const char *found = strchr("Hello World", 'W');
  printf("strchr: 'W' 在 \"%s\" 的位置: %td\n",
         "Hello World", found ? found - "Hello World" : -1);

  /* ---- 字符串数组 ---- */
  printf("\n=== 字符串数组 ===\n");
  // 方式一：指针数组（每个指针指向只读字面量）
  const char *fruits[] = {"apple", "banana", "cherry"};
  // 方式二：二维 char 数组（可修改，但浪费空间）
  char names[][10] = {"Alice", "Bob", "Charlie"};

  printf("const char*[]: ");
  for (int i = 0; i < 3; i++) {
    printf("%s ", fruits[i]);
  }
  printf("（指向只读字面量，不可修改字符）\n");

  printf("char[][10]: ");
  for (int i = 0; i < 3; i++) {
    printf("%s ", names[i]);
  }
  printf("（可修改，但每行固定 10 字节）\n");

  /* ---- 命令行参数 ---- */
  // argc: 参数个数（含程序名自身）
  // argv: 参数字符串数组，argv[0] 是程序名
  printf("\n=== 命令行参数 ===\n");
  printf("参数个数: %d\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("  argv[%d] = \"%s\"\n", i, argv[i]);
  }

  /* ---- 缓冲区溢出风险 ---- */
  // C 不检查数组越界，写越界会覆盖相邻内存，是安全漏洞的主要来源
  printf("\n=== 缓冲区溢出风险 ===\n");
  char buf[5] = "safe";  // 只有 5 字节：'s','a','f','e','\0'
  // strncpy(buf, "very long string", sizeof(buf));  // 会自动截断但不会补'\0'
  printf("buf = \"%s\"（如果溢出会覆盖相邻内存，导致程序崩溃或安全漏洞）\n", buf);

  return 0;
}
