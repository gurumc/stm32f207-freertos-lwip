#include <stm32f2xx.h>

void HardFault_Handler(void)
{
 // GPIOD->ODR |= GPIO_Pin_15;
  for(;;);
}

void BusFault_Handler(void)
{
  //GPIOD->ODR |= GPIO_Pin_15;
  for(;;);
}

void UsageFault_Handler(void)
{
  //GPIOD->ODR |= GPIO_Pin_15;
  for(;;);
}




