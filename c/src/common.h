// 跨平台控制台 UTF-8 编码设置
// 各 .c 文件引入后，在 main() 开头调用 setup_console()

#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
  #include <windows.h>
  #define setup_console() SetConsoleOutputCP(CP_UTF8)
#else
  #define setup_console() ((void)0)
#endif

#endif
