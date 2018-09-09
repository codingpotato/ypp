#include <cstdio>
#include "board_init.h"
#include "gpio.h"
#include "system.h"

struct A {
  A() {
    b = 1;
  }
  int b = 0;
};

A a;

int main(void) {
  board_init();

  if (on_psp()) {
    gpio_toggle_led(2);
  }

  while (1) {
    printf("toggle led\r\n");
    gpio_toggle_led(1);
    sleep(100);
  }
}
