/*
 * 07-preprocess-file.c — 预处理器 / 文件 I/O / 多文件编译
 *
 * 预处理器在编译前处理 # 开头的指令，不是真正的 C 语句。
 * 文件 I/O 让程序持久化数据，fopen/fclose/fprintf/fscanf 是最常用的接口。
 * 多文件编译需要头文件（.h）和 extern 来共享声明。
 */

#include "../common.h"
// #include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- #define 宏定义 ---- */
// 宏是纯文本替换，不是变量，没有类型检查
#define PI 3.14159
#define SQUARE(x) ((x) * (x)) // 注意：每个参数和整体都要加括号

// 宏函数陷阱：不加括号的后果
// #define BAD_SQUARE(x) x * x
// BAD_SQUARE(2+3) → 2+3*2+3 = 2+6+3 = 11（而非预期的 25）

// 多行宏：用 \ 续行
#define LOG_ERROR(msg)                                                         \
  do {                                                                         \
    fprintf(stderr, "[错误] %s (文件:%s, 行:%d)\n", msg, __FILE__, __LINE__);  \
  } while (0)

/* ---- 条件编译 ---- */
// 同一个源文件可根据不同条件编译不同代码
#define DEBUG_LEVEL 2 // 0=无调试, 1=简要, 2=详细

// #undef：取消宏定义
#ifdef PI
#undef PI
#define PI 3.141592653589793 // 重新定义更精确的值
#endif

/* ---- 头文件保护示例 ---- */
// 在 .h 文件中的典型写法（此处仅注释说明）：
// #ifndef MY_HEADER_H
// #define MY_HEADER_H
//   ... 声明 ...
// #endif
// 或 C23 的 #pragma once（更简洁，几乎所有编译器都支持）
// 注意：#pragma once 不是标准 C 的一部分，但被所有现代编译器支持
// #pragma once 放在文件开头，作用与 #ifndef 头文件保护相同，但写法更简洁
// 示例：
// #pragma once
// ... 声明 ...

int main(void) {
  setup_console();
  /* ---- #include 搜索路径 ---- */
  // #include <file>：从系统目录搜索（标准库头文件）
  // #include "file"：先从当前目录搜索，再从系统目录搜索
  printf("=== #include 搜索路径 ===\n");
  printf("<stdio.h>  系统目录（标准库）\n");
  printf("\"my.h\"     当前目录 → 系统目录\n");

  /* ---- 宏的使用 ---- */
  printf("\n=== 宏定义 ===\n");
  printf("PI = %.10f\n", PI);
  printf("SQUARE(5) = %d\n", SQUARE(5));
  // 注意：宏参数有副作用！
  int n = 2;
// SQUARE(++n) 展开为 ((++n) * (++n))，n 被修改两次，行为未定义
// 以下代码故意演示此陷阱，抑制编译警告
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"
  printf("SQUARE(++n) = %d（注意：++n 被展开两次，结果不可预期）\n",
         SQUARE(++n));
#pragma GCC diagnostic pop

  /* ---- 条件编译 ---- */
  printf("\n=== 条件编译 ===\n");
#if DEBUG_LEVEL >= 2
  printf("调试等级 %d：显示详细信息\n", DEBUG_LEVEL);
#elif DEBUG_LEVEL == 1
  printf("调试等级 1：仅显示简要信息\n");
#else
  printf("调试已关闭\n");
#endif

#ifdef __STDC_VERSION__
  printf("C 标准版本: %ld\n", __STDC_VERSION__);
  // C23 输出 202311L
#endif

  /* ---- 预定义宏 ---- */
  printf("\n=== 预定义宏 ===\n");
  printf("文件名: %s\n", __FILE__);
  printf("行号:   %d\n", __LINE__);
  printf("日期:   %s\n", __DATE__);
  printf("时间:   %s\n", __TIME__);

  /* ---- LOG_ERROR 宏使用 ---- */
  printf("\n=== 错误日志宏 ===\n");
  LOG_ERROR("这是一个测试错误信息");

  /* ====================== 文件 I/O ====================== */

  /* ---- fopen / fclose ---- */
  // 文件打开模式：
  //   "r" 只读（文件必须存在）
  //   "w" 只写（清空已有内容，不存在则创建）
  //   "a" 追加（不存在则创建）
  //   "rb"/"wb" 二进制模式（Windows 上必须用，否则换行符会错）
  printf("\n=== 文件 I/O：fopen / fclose ===\n");
  const char *filename = "test_output.txt";

  errno_t err;
  FILE *fw = NULL;
  err = fopen_s(&fw, filename, "w");
  if (err != 0) {
    perror("打开文件写入失败");
    return 1;
  }

  /* ---- fprintf 格式化写入文件 ---- */
  fprintf(fw, "Hello, C 文件 I/O!\n");
  fprintf(fw, "PI = %.10f\n", PI);
  fprintf(fw, "这是一行中文\n");

  /* ---- fputs 写入字符串 ---- */
  fputs("使用 fputs 写入的行\n", fw);

  // 文件用完后必须关闭，否则缓冲区的数据可能丢失
  fclose(fw);
  printf("已写入文件: %s\n", filename);

  /* ---- fscanf / fgets 读取文件 ---- */
  printf("\n=== 读取文件内容 ===\n");
  FILE *fr = NULL;
  err = fopen_s(&fr, filename, "r");
  if (err != 0) {
    perror("打开文件读取失败");
    return 1;
  }

  // fgets 逐行读取（比 fscanf 更安全，可限制读取长度）
  printf("--- 文件内容 ---\n");
  char line[256];
  int line_num = 1;
  while (fgets(line, sizeof(line), fr) != NULL) {
    // fgets 会保留换行符
    printf("%d: %s", line_num++, line);
  }

  /* ---- feof / ferror ---- */
  // feof：检查是否到文件末尾
  // ferror：检查是否发生了读/写错误
  if (feof(fr)) {
    printf("--- 已到达文件末尾 ---\n");
  }
  if (ferror(fr)) {
    fprintf(stderr, "读取文件时发生错误\n");
  }

  fclose(fr);

  /* ---- 二进制读写 ---- */
  printf("\n=== 二进制 I/O ===\n");
  const char *bin_file = "test_data.bin";
  FILE *fb = NULL;
  err = fopen_s(&fb, bin_file, "wb");
  if (err != 0) {
    perror("打开二进制文件失败");
    return 1;
  }

  // fwrite：将内存数据原样写入文件
  int data[] = {100, 200, 300, 400, 500};
  size_t written = fwrite(data, sizeof(int), 5, fb);
  printf("写入 %zu 个整数到 %s\n", written, bin_file);
  fclose(fb);

  // fread：从文件读取二进制数据
  err = fopen_s(&fb, bin_file, "rb");
  if (err != 0) {
    perror("打开二进制文件读取失败");
    return 1;
  }

  int read_data[5] = {0};
  size_t read_count = fread(read_data, sizeof(int), 5, fb);
  printf("读取了 %zu 个整数: ", read_count);
  for (size_t i = 0; i < read_count; i++) {
    printf("%d ", read_data[i]);
  }
  printf("\n");
  fclose(fb);

  /* ---- errno 错误处理 ---- */
  // errno 是全局错误码，标准库函数失败时会设置它
  printf("\n=== errno 错误处理 ===\n");
  FILE *fe = NULL;
  err = fopen_s(&fe, "不存在的文件.xyz", "r");
  if (err != 0) {
    printf("错误码 errno = %d\n", err);
    char err_buf[256];
    strerror_s(err_buf, sizeof(err_buf), err);
    printf("错误描述: %s\n", err_buf);
    perror("fopen");
  } else {
    fclose(fe);
  }

  /* ---- extern 跨文件变量 ---- */
  // extern 声明一个在其他 .c 文件中定义的全局变量
  // 通常放在 .h 头文件中，实现放在恰好一个 .c 文件中
  printf("\n=== extern 与多文件编译 ===\n");
  printf("extern int global_count;  // 声明（在 .h 中）\n");
  printf("int global_count = 0;     // 定义（在恰好一个 .c 中）\n");
  printf("多文件编译命令行示例：\n");
  printf("  gcc -std=c23 main.c helper.c -o program\n");

  return 0;
}
