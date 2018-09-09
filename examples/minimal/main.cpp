#include <cstdio>
#include "board_init.h"
#include "gpio.h"
#include "stm32f7xx_nucleo_144.h"

int main(void) {
  board_init();

  while (true) {
    printf("toggle led\r\n");
    gpio_toggle_led(1);
    sleep(1000);
  }
}
