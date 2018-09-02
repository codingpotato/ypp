#include <cstdio>
#include "board_init.h"
#include "gpio.h"

/*int main(void) {
  board_init();

  while (1) {
    printf("toggle led\r\n");
    gpio_toggle_led(1);
    sleep(100);
  }
}*/

#include <stddef.h>
#include <stdio.h>

using fcontext_t = void *;

struct transfer_t {
  fcontext_t fctx;
  void *data;
};

extern "C" transfer_t jump_fcontext(fcontext_t to, void *vp);
extern "C" fcontext_t make_fcontext(void *sp, size_t size,
                                    void (*fn)(transfer_t));

void f1(transfer_t t) {
  printf("here\n");
  gpio_set_led(1);
  jump_fcontext(t.fctx, nullptr);
}

constexpr int STACK_SIZE = 1024;
char stack[STACK_SIZE];

int main() {
  board_init();

  printf("first\n");
  gpio_set_led(0);

  fcontext_t ctx = make_fcontext(stack + STACK_SIZE, STACK_SIZE, f1);

  jump_fcontext(ctx, nullptr);

  printf("second\n");
  gpio_set_led(2);

  return 0;
}