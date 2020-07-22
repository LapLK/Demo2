#include "misc.h"

/********************************************************************************
 *   delay: delay
 * Notes:
 *    - 
 ********************************************************************************/
void tsi_delay(uint32 i)
{
  uint32 cnt;
  for(cnt=0;cnt<i;cnt++)  //delay
  {
    asm("nop");
  }
}

/********************************************************************************
 *   GPIO_Init: Initializes GPIO controlling LED
 * Notes:
 *    - 
 ********************************************************************************/
void GPIO_Init(void)
{
  ENABLE_GPIO_CLOCKS;
  
  LED0_EN;
  LED1_EN;
  LED2_EN;
  LED3_EN;

  LEDs_On();
  LED_Dir_Out();
}

void LED_Dir_Out(void)
{
  GPIOA_PDDR = (1<<10)|(1<<11)|(1<<28)|(1<<29);
}

void LEDs_On(void)
{
  GPIOA_PDOR &= ~((1<<10)|(1<<11)|(1<<28)|(1<<29));
}