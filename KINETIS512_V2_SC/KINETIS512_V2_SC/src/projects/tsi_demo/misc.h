
#include "common.h"

void tsi_delay(uint32);
void GPIO_Init(void);
void LEDs_On(void);
void LED_Dir_Out(void);

  #define ENABLE_GPIO_CLOCKS (SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK))
  #define LED0_EN (PORTA_PCR11 = PORT_PCR_MUX(1))
  #define LED1_EN (PORTA_PCR29 = PORT_PCR_MUX(1))
  #define LED2_EN (PORTA_PCR28 = PORT_PCR_MUX(1))
  #define LED3_EN (PORTA_PCR10 = PORT_PCR_MUX(1))

  #define LED0_TOGGLE (GPIOA_PTOR = (1<<11))
  #define LED1_TOGGLE (GPIOA_PTOR = (1<<29))
  #define LED2_TOGGLE (GPIOA_PTOR = (1<<28))
  #define LED3_TOGGLE (GPIOA_PTOR = (1<<10))
