


/*
 * File:		demo_lp_timer.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "demo_lp_timer.h"



/********************************************************************/


/*
    This demo shows how to use how to use the low power timer(LPT).

    Before using LPT, we must set it's clock source and prescale value,

    then we config the compare register and launch the LPT.

    This demo also shows how to use interrupt.
*/
void main (void)
{
    printf("\n\n****************************\n");
    printf("LPTMR Examples\n");
    printf("****************************\n\n");

    printf("This demo\n");

    //Enable Port clocks
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

    /* Enable LPT Module */
    SIM_SCGC5 |= SIM_SCGC5_LPTIMER_MASK;

    /* Time counting using LPO clock */
    lptmr_time_counter(); // 4s, clk src is LPO(1K Hz)

    /* Time counting using LPO clock with Prescaling */
    lptmr_prescale();
    
    /* Internal REF clock*/
    lptmr_internal_ref_input();

    /* Time counting using different clock sources */
    lptmr_external_32khz_input();
    lptmr_external_clk_input();

    /* LPTMR Interrupt Example */
    lptmr_interrupt();

    printf("\n****************************\n");
    printf("End of LPTMR Examples\n");
    printf("****************************\n");
}
/********************************************************************/

/*
 * Get the current LPTMR Counter Value. 
 *
 * On each read of the LPTMR counter register, software must first write to the 
 * LPTMR counter register with any value. This will synchronize and register the
 * current value of the LPTMR counter register into a temporary register. The 
 * contents of the temporary register are returned on each read of the LPTMR 
 * counter register.
 */
uint16 get_counter_value()
{
    LPTMR0_CNR = 0x0;
    return LPTMR0_CNR;
}

/*
 * Zero out all registers.
 *
 */
void lptmr_clear_registers()
{
    LPTMR0_CSR=0x00;
    LPTMR0_PSR=0x00;
    LPTMR0_CMR=0x00;
}

/********************************************************************/
