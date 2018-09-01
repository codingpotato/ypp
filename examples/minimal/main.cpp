#include "board_init.h"
#include "gpio.h"

int main(void) {
  board_init();

  while (1) {
    gpio_toggle_led0();
    sleep(100);
  }
}
