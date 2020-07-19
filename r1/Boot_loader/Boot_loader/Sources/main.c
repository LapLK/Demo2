/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "pin_mux.h"
#include "clockMan1.h"
#include "lpuart1.h"
#include "flash1.h"
#include "osif1.h"
#include "dmaController1.h"
#include <string.h>

volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */

#include "flash1.h"

static void prvSetupHardware( void );
static void uartTask(void);

#define APPLICATION_ADDRESS        0x0800C000

flash_ssd_config_t flashSSDConfig;

/* Function declarations */
void CCIF_Handler(void);
/* If target is flash, insert this macro to locate callback function into RAM */
START_FUNCTION_DECLARATION_RAMSECTION
void CCIF_Callback(void)
END_FUNCTION_DECLARATION_RAMSECTION

//#define BUFFER_SIZE         0x7D0          /* Size of data source */
#define BUFFER_SIZE         0x630          /* Size of data source */
static uint8_t sourceBuffer[BUFFER_SIZE];

/*!
  \brief Interrupt handler for Flash Command Complete event
*/
void CCIF_Handler(void)
{
    /* Disable Flash Command Complete interrupt */
    FTFx_FCNFG &= (~FTFx_FCNFG_CCIE_MASK);

    return;
}

void send(const char *sourceStr)
{
    uint32_t bytesRemaining;

   	/* Send data via LPUART */
   	LPUART_DRV_SendData(INST_LPUART1, (uint8_t *) sourceStr, strlen(sourceStr));
   	/* Wait for transmission to be successful */
   	while (LPUART_DRV_GetTransmitStatus(INST_LPUART1, &bytesRemaining)
			!= STATUS_SUCCESS)
	{
	}
}

/*UART Task to receive the request and send the response*/
static void uartTask()
{
	uint32_t bytesRemain;
//	volatile status_t ret=-1;

//JK for( ;; )
//	{
//		LPUART_DRV_ReceiveData(INST_LPUART1, &sourceBuffer, BUFFER_SIZE);
		LPUART_DRV_ReceiveDataBlocking(INST_LPUART1, sourceBuffer, BUFFER_SIZE,30000);
		while(LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemain) != STATUS_SUCCESS);
		//ret=LPUART_DRV_GetReceiveStatus(INST_LPUART1, &bytesRemain);
//JK		break;
//	}

}

/*Hardware Initialization*/
static void prvSetupHardware( void )
{
	volatile status_t ret;
	/* Initialize and configure clock,GPIO,LPUART */
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
	LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0);

	/* Disable cache to ensure that all flash operations will take effect instantly,
	     * this is device dependent */
	#ifdef S32K144_SERIES
	    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM0(0xFu) | MSCM_OCMDR_OCM1(0xFu) | MSCM_OCMDR_OCM2(0xFu);
	    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM0(0xFu) | MSCM_OCMDR_OCM1(0xFu) | MSCM_OCMDR_OCM2(0xFu);
	    MSCM->OCMDR[2u] |= MSCM_OCMDR_OCM0(0xFu) | MSCM_OCMDR_OCM1(0xFu) | MSCM_OCMDR_OCM2(0xFu);
	    MSCM->OCMDR[3u] |= MSCM_OCMDR_OCM0(0xFu) | MSCM_OCMDR_OCM1(0xFu) | MSCM_OCMDR_OCM2(0xFu);
	#endif /* S32K144_SERIES */

	/* Install interrupt for Flash Command Complete event */
//JK	INT_SYS_InstallHandler(FTFC_IRQn, CCIF_Handler, (isr_t*) 0);
//JK	INT_SYS_EnableIRQ(FTFC_IRQn);

	/* Enable global interrupt */
	INT_SYS_EnableIRQGlobal();

	/* Always initialize the driver before calling other functions */
	ret = FLASH_DRV_Init(&flash1_InitConfig0, &flashSSDConfig);
/*JK	if (ret != STATUS_SUCCESS)
	{
		return ret;
	}*/
}

/*!
  \brief Callback function for Flash operations
*/
START_FUNCTION_DEFINITION_RAMSECTION
void CCIF_Callback(void)
{
    /* Enable interrupt for Flash Command Complete */
    if ((FTFx_FCNFG & FTFx_FCNFG_CCIE_MASK) == 0u)
    {
        FTFx_FCNFG |= FTFx_FCNFG_CCIE_MASK;
    }
}
END_FUNCTION_DEFINITION_RAMSECTION

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
//int boot_main(void)
int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/
    volatile status_t ret;        /* Store the driver APIs return code */
    uint32_t address;
    uint32_t size;
    uint32_t failAddr;

//JK    flash_callback_t pCallBack;

    prvSetupHardware();

    uartTask();

    /* Set callback function before a long time consuming flash operation
     * (ex: erasing) to let the application code do other tasks while flash
     * in operation. In this case we use it to enable interrupt for
     * Flash Command Complete event */
//JK    pCallBack = (flash_callback_t)CCIF_Callback;
//JK    flashSSDConfig.CallBack = pCallBack;
    flashSSDConfig.CallBack = NULL_CALLBACK;

    INT_SYS_DisableIRQGlobal();
    /* Erase the sixth PFlash sector */
    address = 6u * FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    size = FEATURE_FLS_PF_BLOCK_SECTOR_SIZE;
    //size = BUFFER_SIZE;5
    ret = FLASH_DRV_EraseSector(&flashSSDConfig, address, size);

    /* Disable Callback */
    flashSSDConfig.CallBack = NULL_CALLBACK;

    /* Verify the erase operation at margin level value of 1, user read */
    /*ret = FLASH_DRV_VerifySection(&flashSSDConfig, address, size / FTFx_DPHRASE_SIZE, 1u);
    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }*/

    /* Write some data to the erased PFlash sector */
    size = BUFFER_SIZE;

    ret = FLASH_DRV_Program(&flashSSDConfig, address, size, sourceBuffer);
/*JK    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }*/

    /* Verify the program operation at margin level value of 1, user margin */
    ret = FLASH_DRV_ProgramCheck(&flashSSDConfig, address, size, sourceBuffer, &failAddr, 1u);
/*JK    if (ret != STATUS_SUCCESS)
    {
        return ret;
    }*/


    __asm__("b 0x6480");

    //uartTask();
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
