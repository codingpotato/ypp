#ifndef MAIN_SYSTEM_H
#define MAIN_SYSTEM_H

/*------------------ RealView Compiler -----------------*/
#if defined(__CC_ARM)
#include "cmsis_armcc.h"

/*------------------ ARM Compiler V6 -------------------*/
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#include "cmsis_armcc_V6.h"

/*------------------ GNU Compiler ----------------------*/
#elif defined(__GNUC__)
#include "cmsis_gcc.h"

/*------------------ ICC Compiler ----------------------*/
#elif defined(__ICCARM__)
#include <cmsis_iar.h>

/*------------------ TI CCS Compiler -------------------*/
#elif defined(__TMS470__)
#include <cmsis_ccs.h>

/*------------------ TASKING Compiler ------------------*/
#elif defined(__TASKING__)
/*
 * The CMSIS functions have been implemented as intrinsics in the compiler.
 * Please use "carm -?i" to get an up to date list of all intrinsics,
 * Including the CMSIS ones.
 */

/*------------------ COSMIC Compiler -------------------*/
#elif defined(__CSMC__)
#include <cmsis_csm.h>

#endif

#include <cstdint>
#include <cstdio>

inline bool on_psp() {
  return __get_CONTROL() & 2;
}

#endif