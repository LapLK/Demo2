/*
 * File:		flex_bus_demo.c
 * Purpose:		Main process
 *
 */

#include "common.h"

/********************************************************************/
#define FLEX_BUS_BASE_ADDRESS 0x60000000
void flex_bus_init(void)
{
    #define OFF_CHIP_ACCESS_ALLOW   3

    SIM_MemMapPtr   sim = SIM_BASE_PTR;

    /* Enable clock to FlexBus module */
    sim->SCGC7 |= SIM_SCGC7_FLEXBUS_MASK;
    sim->SOPT2 |= SIM_SOPT2_FBSL(OFF_CHIP_ACCESS_ALLOW);

    // see schmatic for this pin configuration
    PORTB_PCR10 = PORT_PCR_MUX(5);
    PORTB_PCR11 = PORT_PCR_MUX(5);
    PORTB_PCR16 = PORT_PCR_MUX(5);
    PORTB_PCR17 = PORT_PCR_MUX(5);
    PORTB_PCR18 = PORT_PCR_MUX(5);
    PORTB_PCR19 = PORT_PCR_MUX(5);
    PORTB_PCR20 = PORT_PCR_MUX(5);
    PORTB_PCR21 = PORT_PCR_MUX(5);
    PORTB_PCR22 = PORT_PCR_MUX(5);
    PORTB_PCR23 = PORT_PCR_MUX(5);

    PORTC_PCR0 = PORT_PCR_MUX(5);
    PORTC_PCR1 = PORT_PCR_MUX(5);
    PORTC_PCR2 = PORT_PCR_MUX(5);
    PORTC_PCR3 = PORT_PCR_MUX(5);
    PORTC_PCR4 = PORT_PCR_MUX(5);
    PORTC_PCR5 = PORT_PCR_MUX(5);
    PORTC_PCR6 = PORT_PCR_MUX(5);
    PORTC_PCR7 = PORT_PCR_MUX(5);
    PORTC_PCR8 = PORT_PCR_MUX(5);
    PORTC_PCR9 = PORT_PCR_MUX(5);
    PORTC_PCR10 = PORT_PCR_MUX(5);
    PORTC_PCR11 = PORT_PCR_MUX(5);
    PORTC_PCR12 = PORT_PCR_MUX(5);
    PORTC_PCR13 = PORT_PCR_MUX(5);
    PORTC_PCR14 = PORT_PCR_MUX(5);
    PORTC_PCR15 = PORT_PCR_MUX(5);

    PORTD_PCR0 = PORT_PCR_MUX(5);
    PORTD_PCR1 = PORT_PCR_MUX(5);
    PORTD_PCR2 = PORT_PCR_MUX(5);
    PORTD_PCR3 = PORT_PCR_MUX(5);
    PORTD_PCR4 = PORT_PCR_MUX(5);
    PORTD_PCR5 = PORT_PCR_MUX(5);
    PORTD_PCR6 = PORT_PCR_MUX(5);

    FB_CSAR0 = 0x60000000;
    //FB_CSMR0 = 0xffff0000 | FB_CSMR_V_MASK;
    //FB_CSCR0 = (1<<6);


    //Enable cs signal
    FB_CSMR0 |= FB_CSMR_V_MASK;

    //right justified mode cs bit9 = 1;
    // FB_CSCR0 |= FB_CSCR_BLS_MASK;
    //8-bit port
    FB_CSCR0 &= ~FB_CSCR_PS(3);
    FB_CSCR0 |= FB_CSCR_PS(1);

    //set Auto-ack
    FB_CSCR0 |= FB_CSCR_AA_MASK;
    //set BEM set to 1
    FB_CSCR0 |= FB_CSCR_BEM_MASK;
    //ASET 01
    FB_CSCR0 &= ~FB_CSCR_ASET(0x3); 
    FB_CSCR0 |= FB_CSCR_ASET(0x1); 
    //RDAH 00
    FB_CSCR0 &= ~FB_CSCR_RDAH(0x3);
    FB_CSCR0 |= FB_CSCR_RDAH(0x0);
    //WRAH 00
    FB_CSCR0 &= ~FB_CSCR_WRAH(0x3);
    FB_CSCR0 |= FB_CSCR_WRAH(0x0);
    //WS 06
    FB_CSCR0 &= ~FB_CSCR_WS(0x3F);
    FB_CSCR0 |= FB_CSCR_WS(0x6);

    //set BEM set to 1
    FB_CSCR0 |= FB_CSCR_BEM_MASK;
    //address bit24-16 are not decoded
    FB_CSMR0 |= FB_CSMR_BAM(0x1ff);
    //                         group1       group2           group3           group4            group5
    //CSPMCR value 0x00000000  fb_ale       fb_cs_b[4]       fb_cs_b[5]       fb_tbst_b         fb_ta_b
    //CSPMCR value 0x11111000  fb_cs_b[1]   fb_siz[0]        fb_siz[1]        fb_cs_b[2]       fb_cs_b[3]
    //CSPMCR value 0x22222000  fb_ts_b      fb_bwe_31_24_b   fb_bwe_23_16_b   fb_bwe_15_8_b    fb_bwe_7_0_b
    //CSPMCR value 0x33333000  fb_ale       fb_cs_b[4]       fb_cs_b[5]       fb_tbst_b        1'b1

    //set be0/1 to MRAM
    FB_CSPMCR |= 0x02200000;
}
void main (void)
{
	char ch;
    char * p = (char *)FLEX_BUS_BASE_ADDRESS;
  	
    printf("***********************************************\n");
    printf("FLEX BUS test, you need to connect the \n");
    printf("TWR-MEM board and add jumper at J15 and J10 \n");
    printf("to test the code.\n");
    printf("Presss any key to continue.\n");
    printf("***********************************************\n");
    in_char();
    
    
    flex_bus_init();

    printf("write to SRAM on flex bus, 0x00, 0xff, 0x55, 0xaa\n");
    *p++ = 0x00;
    *p++ = 0xff;
    *p++ = 0x55;
    *p++ = 0xaa;
    
    p = (char *)FLEX_BUS_BASE_ADDRESS;
    printf("reading SRAM from flex bus: %x,%x,%x,%x\n", p[0],p[1],p[2],p[3]);

	while(1)
	{
		ch = in_char();
		out_char(ch);
	} 
}
/********************************************************************/





