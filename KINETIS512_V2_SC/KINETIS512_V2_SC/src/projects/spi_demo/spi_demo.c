/*
 * File:		spi_demo.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "global.h"
#include "hal_spi.h"
#include "hal_spi_dev_flash.h"

/********************************************************************/
void main (void)
{
	char ch;
    
    printf("***************************************************\n");
    printf("SPI demo.\n");
    printf("You need to insert the TWR-MEM card for the\n");
    printf("test. Add jumper to J14, pin 1-2.  J4, pin 1-2.\n");
    printf("Press any key to continue.\n");
    printf("***************************************************\n");
    in_char();

  	hal_spi_init();
    hal_spi_dev_flash_test();

	while(1)
	{
		ch = in_char();
		out_char(ch);
	} 
}
/********************************************************************/
