#include <cstdio>
#include "board_init.h"
#include "gpio.h"

int main(void) {
  board_init();

  while (1) {
    printf("toggle led\r\n");
    gpio_toggle_led(1);
    sleep(100);
  }
}
