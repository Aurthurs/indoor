/*
 * 04-pointer.c — 指针
 *
 * 指针是 C 语言最核心也最容易出错的概念。
 * 指针存储内存地址，通过它可以直接操作任意内存位置。
 * 理解指针 = 理解 C 的内存模型。
 */

#include "../common.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

int main(void) {
  setup_console();
  /* ---- 取址 & 与解引用 * ---- */
  // & 取变量的内存地址，* 通过地址访问原变量
  printf("=== 取址与解引用 ===\n");
  int x = 42;
  int *p = &x; // p 指向 x 的地址
  printf("x   = %d\n", x);
  printf("&x  = %p（x 的地址）\n", (void *)&x);
  printf("p   = %p（p 存的就是 x 的地址）\n", (void *)p);
  printf("*p  = %d（通过 p 读 x 的值）\n", *p);
  *p = 100; // 通过指针修改 x
  printf("执行 *p = 100 后: x = %d（x 被间接修改）\n", x);

  /* ---- 指针与数组 ---- */
  // arr[i] 等价于 *(arr + i)，数组名本身可当作指向首元素的指针
  printf("\n=== 指针与数组 ===\n");
  int arr[] = {10, 20, 30, 40, 50};
  printf("arr   = %p\n", (void *)arr);
  printf("&arr[0] = %p（和 arr 一样，都是首元素地址）\n", (void *)&arr[0]);
  printf("通过下标: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n通过指针: ");
  for (int i = 0; i < 5; i++) {
    printf("%d ", *(arr + i)); // 等价于 arr[i]
  }
  printf("\n");

  /* ---- 指针算术 ---- */
  // 指针 +1 不是加 1 字节，而是跳过一个元素大小（sizeof(类型) 字节）
  printf("\n=== 指针算术 ===\n");
  int *p0 = arr;
  int *p1 = p0 + 1; // 跳过 1 个 int（通常 4 字节）
  int *p2 = p0 + 2;
  printf("p0 指向 arr[0]=%d, 地址: %p\n", *p0, (void *)p0);
  printf("p1 指向 arr[1]=%d, 地址: %p\n", *p1, (void *)p1);
  // 地址差值（单位是元素个数而非字节）
  printf("p2 - p0 = %td（元素个数，不是字节数）\n", p2 - p0);

  // 指针遍历数组
  printf("指针遍历: ");
  for (int *pcur = arr; pcur < arr + 5; pcur++) {
    printf("%d ", *pcur);
  }
  printf("\n");

  /* ---- const 与指针的三种组合 ---- */
  // 这是 C 指针最绕的部分，记住：const 修饰离它最近的左侧类型
  printf("\n=== const 与指针 ===\n");
  int a = 1, b = 2;

  // 指向常量的指针：不能通过指针修改值，但指针可指向别处
  const int *pc = &a; // 或 int const *pc
  // *pc = 10;          // 编译错误：不能修改指向的内容
  pc = &b; // 但可以改变指向
  printf("const int *pc：pc 现在指向 b = %d\n", *pc);

  // 常量指针：指针本身不可改，但可以通过它修改内容
  int *const cp = &a;
  *cp = 99; // 可以修改内容
  // cp = &b;           // 编译错误：不能改变指向
  printf("int *const cp：a 已被改为 %d\n", a);

  // 常量指针指向常量：都不能改
  const int *const cpc = &a;
  // *cpc = 10;         // 编译错误
  // cpc = &b;          // 编译错误
  printf("const int *const cpc：cpc 指向 a = %d（都不能改）\n", *cpc);

  /* ---- void* 通用指针 ---- */
  // void* 可以接收任意类型的指针，但不能直接解引用
  printf("\n=== void* 通用指针 ===\n");
  double pi = 3.14;
  void *vp = &pi; // 可以存任意类型的地址
  printf("void* 存了 double 的地址: %p\n", vp);
  // printf("%f", *vp); // 编译错误：void* 不能直接解引用
  printf("解引用 void* 需先转换: %.2f\n", *(double *)vp);

  /* ---- NULL 空指针 ---- */
  // NULL 是空指针宏（C23 起有 nullptr 关键词作为更安全的替代，此处用 NULL
  // 保持兼容）
  int *np = NULL;
  // 注意：解引用 NULL 会导致程序崩溃（段错误）
  if (np == NULL) {
    printf("指针为空，不能解引用\n");
  }

  /* ---- 野指针与悬空指针 ---- */
  // 野指针：未初始化的指针，指向随机地址
  // 悬空指针：指向已释放/已失效内存的指针
  printf("\n=== 野指针与悬空指针 ===\n");
  printf("野指针: int *wild; // 未初始化，值是随机的\n");
  printf("悬空指针: 指向已释放的内存，再使用会崩溃\n");
  // 解决方案：声明时初始化为 NULL，释放后立即置 NULL
  printf("安全做法: int *p = NULL; // 声明时立即初始化\n");

  /* ---- 多级指针 ---- */
  // 二级指针存指针的地址，用于函数中修改指针本身
  /*
   * 为什么需要二级指针？
   * 答案：
   * 因为函数参数是值传递，如果希望在函数内部修改“一级指针本身”，必须传一级指针的地址，因此需要二级指针。
   * int *p 是为了修改 int
   * int **pp 是为了修改 int*
   * int ***ppp 是为了修改 int**
   */
  printf("\n=== 多级指针 ===\n");
  int val = 999;
  int *p_val = &val;     // 一级指针
  int **pp_val = &p_val; // 二级指针：存指针的地址
  printf("val    = %d\n", val);
  printf("*p_val = %d\n", *p_val);
  printf("**pp_val = %d（通过两级解引用访问 val）\n", **pp_val);

  return 0;
}
