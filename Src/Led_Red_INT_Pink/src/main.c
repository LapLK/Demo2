#include "S32K144.h" /* include peripheral declarations S32K144 */

#define PTD0 0 /* Port PTD0, bit 0: FRDM EVB output to blue LED */
#define PTD15 15
#define PTD16 16
#define PTC12 12 /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */

void WDOG_disable (void){
    WDOG->CNT=0xD928C520; /*Unlock watchdog*/
    WDOG->TOVAL=0x0000FFFF; /*Maximum timeout value*/
    WDOG->CS = 0x00002100; /*Disable watchdog*/
}

void Delay(int ms){
	ms*=5000;
	while (ms){--ms;}
}

void PORTC_IRQHandler(){
	if (PTC->PIDR == 0){
//		PTD->PTOR = (1 << PTD15 | 1 << PTD0);
		PTD-> PCOR |= 1<<PTD16;
		PORTC->PCR[12] |= PORT_PCR_ISF(0);
	}
}

int main(void) {
    WDOG_disable();
    /* Enable clocks to peripherals (PORT modules) */
    PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT C */
    PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /* Enable clock to PORT D */


    /* Configure port C12 as GPIO input (BTN 0 [SW2] on EVB) */
    PTC->PDDR &= ~(1<<PTC12); /* Port C12: Data Direction= input (default) */
    PORTC->PCR[12] = 0x00000110; /* Port C12: MUX = GPIO, input filter enabled */


    PORTC->PCR[12] |= PORT_PCR_PS(1);
    PORTC->PCR[12] |= PORT_PCR_PE(1);
    PORTC->PCR[12] |= PORT_PCR_IRQC(10);
    PORTC->PCR[12] |= PORT_PCR_ISF(0);

    S32_NVIC->ICPR[PORTC_IRQn/32] = 1 << (PORTC_IRQn % 32);
    S32_NVIC->ISER[PORTC_IRQn/32] = 1 << (PORTC_IRQn % 32);
    S32_NVIC->IP[PORTC_IRQn] = 0xA;

    /* Configure port D0 as GPIO output (LED on EVB) */
    PTD->PDDR |= 1<<PTD0; /* Port D0: Data Direction= output */
    PTD->PDDR |= 1<<PTD15; /* Port D0: Data Direction= output */
    PTD->PDDR |= 1<<PTD16; /* Port D0: Data Direction= output */
    PORTD->PCR[0] = 0x00000100; /* Port D0: MUX = GPIO */
    PORTD->PCR[15] = 0x00000100; /* Port D0: MUX = GPIO */
    PORTD->PCR[16] = 0x00000100; /* Port D0: MUX = GPIO */

    Delay(100);
    PTD-> PSOR |= 1<<PTD0;
    PTD-> PSOR |= 1<<PTD15;
    PTD-> PSOR |= 1<<PTD16;
    while(1){
//    	PTD-> PCOR |= 1<<PTD16;
    	PTD-> PCOR |= 1<<PTD15;
//    	PTD-> PCOR |= 1<<PTD16;
    }
    return 0;
}
