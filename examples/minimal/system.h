#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include <cstdio>
#include "stm32f767xx.h"

inline bool on_psp() {
  return __get_CONTROL() & 2;
}

#define print_LR()                                                             \
  {                                                                            \
    uint32_t result;                                                           \
    asm volatile("mov %0, lr" : "=r"(result));                                 \
    printf("%#010lx\r\n", result);                                             \
  }

#endif