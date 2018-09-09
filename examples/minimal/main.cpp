#include <cstdio>
#include "board_init.h"
#include "gpio.h"
#include "stm32f7xx_nucleo_144.h"
#include "system.h"

extern "C" void EXTI15_10_IRQHandler() {
  print_LR();
  HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_PIN);
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == USER_BUTTON_PIN) {
    gpio_toggle_led(2);
  }
}

int main(void) {
  board_init();

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  print_LR();

  while (true) {
    printf("toggle led\r\n");
    gpio_toggle_led(1);
    sleep(1000);
  }
}
