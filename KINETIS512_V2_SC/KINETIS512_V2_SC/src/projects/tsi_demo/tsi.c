
#include "TSI.h"

extern uint32 __VECTOR_RAM[];

uint16  g16ElectrodeTouch[16] = {0};
uint16  g16ElectrodeBaseline[16] = {0};

uint32  g32DebounceCounter[16] = {DBOUNCE_COUNTS};

/********************************************************************************
 *   TSI_Init: Initializes TSI module
 * Notes:
 *    -
 ********************************************************************************/
void TSI_Init(void)
{
	/*enable TSI clock gate */
    SIM_SCGC5 |= (SIM_SCGC5_TSI_MASK);
    
    PORTA_PCR4 = PORT_PCR_MUX(0);
    PORTB_PCR2 = PORT_PCR_MUX(0);
    PORTB_PCR3 = PORT_PCR_MUX(0);
    PORTB_PCR16 = PORT_PCR_MUX(0);
    
    TSI0_GENCS |= TSI_GENCS_NSCN(10)	//number of consecutive scans per electrode
				| TSI_GENCS_PS(3);		//electrode osc prescaler, divide by 2 ^ x, x is the value set here
				
    TSI0_SCANC |= TSI_SCANC_EXTCHRG(3)	//external osc charge current select, 2*(1+x) uA
				| TSI_SCANC_REFCHRG(31)	//ref osc charge current select, 2*(1+x) uA
				| TSI_SCANC_SMOD(0)		//continue scan
				| TSI_SCANC_AMCLKS(0)	//active mode clock source - LPOSCCLK
				| TSI_SCANC_AMPSC(0);	//active mode prescaler
    
	/* enable TSI pins */
    ELECTRODE_ENABLE_REG = ELECTRODE0_EN_MASK |ELECTRODE1_EN_MASK | ELECTRODE2_EN_MASK |ELECTRODE3_EN_MASK;
    
	/* Enables TSI module */
    TSI0_GENCS |= (TSI_GENCS_TSIEN_MASK);  
	
    /* Init TSI interrupts */
    enable_irq(INT_TSI0-16);
    /***********************/

}

void TSI_Deinit(void)
{
	/* disable TSI interrupt */
    disable_irq(INT_TSI0-16);
	
	/* TSI module disabled */
    TSI0_GENCS &= ~(TSI_GENCS_TSIEN_MASK);
	
	/* disable TSI clock gate */
    SIM_SCGC5 &= ~(SIM_SCGC5_TSI_MASK);
}

/********************************************************************************
 *   TSI_SelfCalibration: Simple auto calibration version
 * Notes:
 *    - Very simple, only sums a prefixed amount to the current baseline
 ********************************************************************************/
void TSI_SelfCalibration(void)
{
	/* software trigger start */
    TSI0_GENCS |= TSI_GENCS_SWTS_MASK;
	
	/* wait till end of scan */
    while(!TSI0_GENCS&TSI_GENCS_EOSF_MASK){};
    
    tsi_delay(100000);
    
    g16ElectrodeBaseline[ELECTRODE0] = ELECTRODE0_COUNT;
    ELECTRODE0_OUTRG = (uint32)((g16ElectrodeBaseline[ELECTRODE0]+ELECTRODE0_OUTRG_VAL));
    g16ElectrodeTouch[ELECTRODE0] = g16ElectrodeBaseline[ELECTRODE0] + ELECTRODE0_TOUCH;
    
    g16ElectrodeBaseline[ELECTRODE1] = ELECTRODE1_COUNT;
    ELECTRODE1_OUTRG = (uint32)((g16ElectrodeBaseline[ELECTRODE1]+ELECTRODE1_OUTRG_VAL));
    g16ElectrodeTouch[ELECTRODE1] = g16ElectrodeBaseline[ELECTRODE1] + ELECTRODE1_TOUCH;
    
    g16ElectrodeBaseline[ELECTRODE2] = ELECTRODE2_COUNT;
    ELECTRODE2_OUTRG = (uint32)((g16ElectrodeBaseline[ELECTRODE2]+ELECTRODE2_OUTRG_VAL));
    g16ElectrodeTouch[ELECTRODE2] = g16ElectrodeBaseline[ELECTRODE2] + ELECTRODE2_TOUCH;
    
    g16ElectrodeBaseline[ELECTRODE3] = ELECTRODE3_COUNT;
    ELECTRODE3_OUTRG = (uint32)((g16ElectrodeBaseline[ELECTRODE3]+ELECTRODE3_OUTRG_VAL));
    g16ElectrodeTouch[ELECTRODE3] = g16ElectrodeBaseline[ELECTRODE3] + ELECTRODE3_TOUCH;

    
    DISABLE_TSI;

}

/********************************************************************************
 *   TSI_isr: TSI interrupt subroutine
 * Notes:
 *    -
 ********************************************************************************/

void TSI_isr(void)
{
  static uint16 TouchEvent = 0;
  uint16 lValidTouch = 0;
  uint16 l16Counter;

  /* clear out of range flag */
  TSI0_GENCS |= TSI_GENCS_OUTRGF_MASK;
  /* clear end of scan flag */
  TSI0_GENCS |= TSI_GENCS_EOSF_MASK;


  /* Process electrode 0 */
  l16Counter = ELECTRODE0_COUNT;
  if(l16Counter>g16ElectrodeTouch[ELECTRODE0])
  {
    TouchEvent |= (1<<ELECTRODE0);
    g32DebounceCounter[ELECTRODE0]--;
    if(!g32DebounceCounter[ELECTRODE0])
    {
      lValidTouch |= ((1<<ELECTRODE0));
      TouchEvent &= ~(1<<ELECTRODE0);
    }
  }
  else
  {
    TouchEvent &= ~(1<<ELECTRODE0);
    g32DebounceCounter[ELECTRODE0] = DBOUNCE_COUNTS;
  }
  /***********************/

  /* Process electrode 1 */
  l16Counter = ELECTRODE1_COUNT;
  if(l16Counter>g16ElectrodeTouch[ELECTRODE1])
  {
    TouchEvent |= (1<<ELECTRODE1);
    g32DebounceCounter[ELECTRODE1]--;
    if(!g32DebounceCounter[ELECTRODE1])
    {
      lValidTouch |= ((1<<ELECTRODE1));
      TouchEvent &= ~(1<<ELECTRODE1);
    }
  }
  else
  {
    TouchEvent &= ~(1<<ELECTRODE1);
    g32DebounceCounter[ELECTRODE1] = DBOUNCE_COUNTS;
  }
  /***********************/

  /* Process electrode 2 */
  l16Counter = ELECTRODE2_COUNT;
  if(l16Counter>g16ElectrodeTouch[ELECTRODE2])
  {
    TouchEvent |= (1<<ELECTRODE2);
    g32DebounceCounter[ELECTRODE2]--;
    if(!g32DebounceCounter[ELECTRODE2])
    {
      lValidTouch |= ((1<<ELECTRODE2));
      TouchEvent &= ~(1<<ELECTRODE2);
    }
  }
  else
  {
    TouchEvent &= ~(1<<ELECTRODE2);
    g32DebounceCounter[ELECTRODE2] = DBOUNCE_COUNTS;
  }
  /***********************/

  /* Process electrode 3 */
  l16Counter = ELECTRODE3_COUNT;
  if(l16Counter>g16ElectrodeTouch[ELECTRODE3])
  {
    TouchEvent |= (1<<ELECTRODE3);
    g32DebounceCounter[ELECTRODE3]--;
    if(!g32DebounceCounter[ELECTRODE3])
    {
      lValidTouch |= ((1<<ELECTRODE3));
      TouchEvent &= ~(1<<ELECTRODE3);
    }
  }
  else
  {
    TouchEvent &= ~(1<<ELECTRODE3);
    g32DebounceCounter[ELECTRODE3] = DBOUNCE_COUNTS;
  }
 
  /***********************/

  if(lValidTouch&((1<<ELECTRODE0)))
  {
    LED0_TOGGLE;
    lValidTouch &= ~((1<<ELECTRODE0));
  }
  if(lValidTouch&((1<<ELECTRODE1)))
  {
    LED1_TOGGLE;
    lValidTouch &= ~((1<<ELECTRODE1));
  }
  if(lValidTouch&((1<<ELECTRODE2)))
  {
    LED2_TOGGLE;
    lValidTouch &= ~((1<<ELECTRODE2));
  }
  if(lValidTouch&((1<<ELECTRODE3)))
  {
    LED3_TOGGLE;
    lValidTouch &= ~((1<<ELECTRODE3));
  }

  //TSI_STATUS = 0xFFFFFFFF;
}

