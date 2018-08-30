#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "vectors.h"

/**
 * @brief   Memory markers, defined in the linker script
 * @{
 */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;
extern uint8_t _sram;
extern uint8_t _eram;
/** @} */

/**
 * @brief   Allocation of the interrupt stack
 */
__attribute__((used, section(".isr_stack"))) uint8_t isr_stack[ISR_STACKSIZE];

void reset_handler_default(void) {
  uint32_t *dst;
  uint32_t *src = &_etext;

  /* load data section from flash to ram */
  for (dst = &_srelocate; dst < &_erelocate;) {
    *(dst++) = *(src++);
  }
  /* default bss section to zero */
  for (dst = &_szero; dst < &_ezero;) {
    *(dst++) = 0;
  }

  extern void __libc_init_array();
  __libc_init_array();

  extern int main();
  main();
}

void nmi_default(void) {}

void hard_fault_default(void) {}

void mem_manage_default(void) {}

void bus_fault_default(void) {}

void usage_fault_default(void) {}

void debug_mon_default(void) {}

void dummy_handler_default(void) {}

/* Cortex-M common interrupt vectors */
__attribute__((weak, alias("dummy_handler_default"))) void isr_svc(void);
__attribute__((weak, alias("dummy_handler_default"))) void isr_pendsv(void);
__attribute__((weak, alias("dummy_handler_default"))) void isr_systick(void);

/* define Cortex-M base interrupt vectors */
ISR_VECTOR(0)
const cortexm_base_t cortex_vector_base = {
    &_estack,
    {
        /* entry point of the program */
        [0] = reset_handler_default,
        /* [-14] non maskable interrupt handler */
        [1] = nmi_default,
        /* [-13] hard fault exception */
        [2] = hard_fault_default,
        /* [-5] SW interrupt, in RIOT used for triggering context switches */
        [10] = isr_svc,
        /* [-2] pendSV interrupt, in RIOT use to do the actual context switch */
        [13] = isr_pendsv,
        /* [-1] SysTick interrupt, not used in RIOT */
        [14] = isr_systick,

        /* [-12] memory manage exception */
        [3] = mem_manage_default,
        /* [-11] bus fault exception */
        [4] = bus_fault_default,
        /* [-10] usage fault exception */
        [5] = usage_fault_default,
        /* [-4] debug monitor exception */
        [11] = debug_mon_default,
    }};
