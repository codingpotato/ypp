#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

#include "stm32f767xx.h"

inline bool on_psp() {
  return __get_CONTROL() & 2;
}

#endif