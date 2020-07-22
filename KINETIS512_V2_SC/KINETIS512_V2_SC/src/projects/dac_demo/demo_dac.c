


/*
    by: G.J, b35970@freescale.com
*/



#include "common.h"
#include "hw_dac.h"



void main (void)
{
    char ch ='0';
    dac0_clk_enable();

    printf("\nWelcome to the Kinetis 12-bit DAC module DEMOs. \n");      
    printf("\nPlease select the following option for the specfific demo\n"); 
    printf("\nYou need to observe the output by an oscilloscope at TP8.\n");

    printf("\n 1: reference voltage from VREF module\n");
    printf("\n 2: buffer mode - nomal\n");
    printf("\n 3: buffer mode - swing\n");
    printf("\n 4: buffer mode - one time\n");
    printf("\n 5: buffer mode - swing, triggered by the PDB module\n");

    while(1)
    {
        ch = in_char();
                      
        switch(ch)
        {
            case '1':
                printf("\n---------------- DEMO 1 ----------------\n"); 
                printf("This demo use 1.2V reference voltage from the on-chip VREF module.\n");
                printf("press 'u' or 'd' to control the output.\n");
                test_dac_vref();
                printf("test end.");
                break;

            case '2':
                printf("\n---------------- DEMO 2 ----------------\n");
                printf("\n In buffered mode where all the 16 word buffers are used.\n");
                printf("\n Buffer is pre-loaded with saw wave output.\n");
                printf("\n Working in normal mode.\n");
                test_dac_buffer_mode_normal();
                break;

            case '3':
                printf("\n---------------- DEMO 3 ----------------\n");
                printf("\n In buffered mode where all the 16 word buffers are used.\n");
                printf("\n Buffer is pre-loaded with saw wave output.\n");
                printf("\n Working in swing mode.\n");
                test_dac_buffer_mode_swing();
                break;
          
            case '4':
                printf("\n---------------- DEMO 4 ----------------\n");
                printf("\n In buffered mode where all the 16 word buffers are used.\n");
                printf("\n Buffer is pre-loaded with saw wave output.\n");
                printf("\n Working in one time mode.\n");
                test_dac_buffer_mode_one_time();
                break;
          
            case '5':
                printf("\n---------------- DEMO 5 ----------------\n");
                printf("\n DACx output is done by hardware trigger via the PDB module.\n");    
                printf("\n read buffer pointer is advanced by time period set forth by the\n");  
                printf("\n the value specified in the PDB_DACINTx register.\n");
                printf("\n still in swing mode.\n");
                test_dac_triggered_by_pdb();
                break;

            default:
                break;
        }
	}
}
/********************************************************************/



