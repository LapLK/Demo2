/*
 * File:		hscmp.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "lptmr.h"


/********************************************************************/
static void gpio_init(void)
{
    PORTC_PCR7 =(PORT_PCR_MUX(1)); //set pin as GPIO
    GPIOC_PDDR = 1<<7;             //set pin as output
}
static void hscmp_init(void)
{
    //Enable HSCMP module clock
    SIM_SCGC4 |= (SIM_SCGC4_CMP_MASK );

    //Set up HSCMP0 in NVIC. ISR put into vector table in isr.h file
    enable_irq(INT_CMP0-16);   //CMP0 Vector is 39. IRQ# is 39-16=23

    // Configure CMP.
    CMP_CR0_REG(CMP0_BASE_PTR)   = 0x00;  // Filter and digital hysteresis disabled
    CMP_CR1_REG(CMP0_BASE_PTR)   = 0x15;  // Continuous mode, high-speed compare, unfiltered output, output pin disabled
    CMP_FPR_REG(CMP0_BASE_PTR)   = 0x00;  // Filter disabled
    CMP_SCR_REG(CMP0_BASE_PTR)   = 0x1E;  // Enable rising and falling edge interrupts, clear flags
    CMP_DACCR_REG(CMP0_BASE_PTR) = 0xF0;  // 6-bit reference DAC enabled, output set to vdd/64*(48+1)= 2.53v, (Vin selected is vin2=Vdd)
    CMP_MUXCR_REG(CMP0_BASE_PTR) = 0x0F;  // P-input as external channel 1. M-input as 6b DAC = 2.53v, it is adjustable with CMP_DACCR_REG
    CMP_CR1_REG(CMP0_BASE_PTR)  |= CMP_CR1_OPE_MASK; // Enable output pin for HSCMP0.
}

/********************************************************************/
void main (void)
{
    printf("CMP0 Example\n");
    printf("INP = PTC7, INM = 6-BIT DAC output as 2.53v.\n");
    printf("toggle on PTC7, CMP output will change and cause interrupt.\n");
    printf("Press any key to continue...");
    in_char();

    gpio_init();
    hscmp_init();

    while(1)
    {
        //Toggle PTC7
        GPIOC_PTOR = 1<<7;

        //Delay for next toggle
        time_delay_ms(1000);
    }
}
void cmp0_isr(void)
{
    //If rising edge
    if ((CMP0_SCR & CMP_SCR_CFR_MASK)==CMP_SCR_CFR_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFR_MASK;  // Clear the flag
        printf("Rising edge on HSCMP0\n");
    }
    
    //If falling edge
    if ((CMP0_SCR & CMP_SCR_CFF_MASK)==CMP_SCR_CFF_MASK)
    {
        CMP0_SCR |= CMP_SCR_CFF_MASK;  // Clear the flag
        printf("Falling edge on HSCMP0\n");
    }
}



/********************************************************************/
