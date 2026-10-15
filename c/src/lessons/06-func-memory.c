/*
 * 06-func-memory.c — 函数 / 动态内存 / 错误处理
 *
 * C 没有异常机制，错误靠返回值和 errno 传递。
 * 动态内存（malloc/free）由程序员手动管理，是 C 最易出错的领域。
 * 理解"栈 vs 堆"、"谁分配谁释放"是写出安全 C 代码的关键。
 */

#include "../common.h"
#include <stdio.h>
#include <stdlib.h> // malloc free calloc realloc
#include <string.h> // strerror

/* ---- 函数声明（原型）vs 定义 ---- */
// 声明：告诉编译器函数存在（参数类型、返回类型）
// 定义：具体实现函数体
int add(int a, int b);  // 声明（可放在 .h 头文件中）
int add(int a, int b) { // 定义
  return a + b;
}

/* ---- 值传递 vs 指针传递 ---- */
// C 的函数参数是"传值"，函数内修改形参不影响实参
void try_modify_value(int n) {
  n = 999; // 只修改了局部副本
  (void)n; // n 仅用于演示值传递
}

// 要修改外部变量，必须传指针
void modify_by_pointer(int *n) {
  *n = 999; // 通过指针修改原变量
}

/* ---- static 局部变量 ---- */
// static 局部变量只初始化一次，函数返回后值保留
int counter(void) {
  static int count = 0; // 只在第一次调用前初始化
  count++;
  return count; // 返回 1, 2, 3, 4...
}

/* ---- 函数指针 ---- */
// 函数名本身就是函数指针，可赋值给同签名的函数指针变量
int multiply(int a, int b) { return a * b; }

// 回调模式：接受函数指针作为参数
void apply(int x, int y, int (*op)(int, int)) {
  printf("回调结果: %d\n", op(x, y));
}

/* ---- 返回错误码的设计模式 ---- */
// C 没有异常，通常用返回值表示错误，0=成功，非0=失败
int safe_divide(int a, int b, int *result) {
  if (b == 0) {
    return -1; // 错误码：除零
  }
  *result = a / b; // 通过指针参数返回结果
  return 0;        // 成功
}

/* ---- 栈内存 vs 堆内存 ---- */
// 栈：函数返回时自动释放，不要返回指向局部变量的指针
// 堆：手动 malloc/free，生命周期由程序员控制
int *create_on_heap(int value) {
  // 在堆上分配，函数返回后内存仍然有效
  int *p = malloc(sizeof(int));
  if (p == NULL)
    return NULL; // 分配失败检查
  *p = value;
  return p;
  // 注意：调用者负责 free
}

int main(void) {
  setup_console();
  /* ---- 值传递 vs 指针传递 ---- */
  printf("=== 值传递 vs 指针传递 ===\n");
  int x = 10;
  printf("调用前: x = %d\n", x);
  try_modify_value(x);
  printf("值传递后: x = %d（未改变——修改的是副本）\n", x);
  modify_by_pointer(&x);
  printf("指针传递后: x = %d（原变量被修改）\n", x);

  /* ---- static 局部变量 ---- */
  printf("\n=== static 局部变量 ===\n");
  printf("counter(): %d\n", counter()); // 1
  printf("counter(): %d\n", counter()); // 2
  printf("counter(): %d\n", counter()); // 3
  // 注意：每次调用 count 不会重新初始化为 0

  /* ---- 函数指针 ---- */
  printf("\n=== 函数指针 ===\n");
  int (*fp)(int, int) = multiply; // 声明函数指针
  printf("通过函数指针: multiply(6, 7) = %d\n", fp(6, 7));

  // 回调模式演示
  apply(6, 7, multiply); // 传入函数指针
  apply(6, 7, add);

  /* ---- malloc / free 基础使用 ---- */
  printf("\n=== malloc / free ===\n");
  // malloc 返回 void*，需要强转或直接用
  int *heap_num = malloc(sizeof(int));
  if (heap_num == NULL) {
    // 注意：内存分配可能失败，每次都要检查
    perror("malloc 失败");
    return 1;
  }
  *heap_num = 42;
  printf("堆上的整数: %d\n", *heap_num);
  free(heap_num);
  heap_num = NULL; // 释放后立即置空，避免悬空指针

  /* ---- calloc ---- */
  // calloc 比 malloc 多一步：将分配的内存全部初始化为 0
  printf("\n=== calloc（初始化为零） ===\n");
  int *arr = calloc(5, sizeof(int)); // 5 个 int，全部为 0
  if (arr == NULL) {
    perror("calloc 失败");
    return 1;
  }
  printf("calloc 初始值: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]); // 预期全部是 0
  }
  printf("\n");

  /* ---- realloc ---- */
  // realloc：调整已分配内存的大小，可能移动数据到新位置
  printf("\n=== realloc（调整大小） ===\n");
  int *expanded = realloc(arr, 10 * sizeof(int)); // 从 5 个扩容到 10 个
  if (expanded == NULL) {
    // 注意：realloc 失败时原内存仍有效，不要覆盖原指针
    perror("realloc 失败");
    free(arr); // 释放原内存
    return 1;
  }
  arr = expanded; // 成功后更新指针
  printf("扩容后新元素: ");
  for (int i = 5; i < 10; i++) {
    printf("%d ", arr[i]); // 新部分未初始化，是随机值
  }
  printf("（未初始化，是随机值）\n");
  free(arr);
  arr = NULL;

  /* ---- 栈 vs 堆：返回指针的陷阱 ---- */
  printf("\n=== 栈 vs 堆 ===\n");
  int *heap_ptr = create_on_heap(88);
  if (heap_ptr) {
    printf("堆上分配的值: %d（跨函数有效）\n", *heap_ptr);
    free(heap_ptr);
    heap_ptr = NULL;
  }
  // 注意：不要返回局部变量的地址，函数返回后栈空间被回收

  /* ---- errno / perror / strerror ---- */
  // errno 是全局错误码，库函数失败时会设置它
  printf("\n=== 错误处理：errno/perror/strerror ===\n");
  FILE *f = NULL;
  errno_t err = fopen_s(&f, "/nonexistent/file.txt", "r");
  if (err != 0) {
    printf("fopen 失败，错误码: %d\n", err);
    char buffer[1024];
    strerror_s(buffer, 1024, err);
    printf("错误描述: %s\n", buffer);
    // perror 自动拼接前缀和错误描述，输出到 stderr
    fprintf(stderr, "perror 输出: ");
    perror("fopen");
  }

  /* ---- 返回错误码的函数设计 ---- */
  printf("\n=== 返回错误码的设计模式 ===\n");
  int div_result;
  if (safe_divide(10, 2, &div_result) == 0) {
    printf("10 / 2 = %d（成功）\n", div_result);
  }
  if (safe_divide(10, 0, &div_result) != 0) {
    // 注意：除零时 div_result 未定义，不应使用
    printf("10 / 0 = 错误（除数为零）\n");
  }

  /* ---- 内存泄漏 ---- */
  // 内存泄漏：分配后忘记释放，程序长期运行会耗尽内存
  printf("\n=== 内存泄漏 ===\n");
  printf("分配内存后忘记 free → 内存泄漏\n");
  printf("工具检测: valgrind ./dist/06-func-memory\n");
  printf("本程序已正确释放所有分配的内存\n");

  return 0;
}
