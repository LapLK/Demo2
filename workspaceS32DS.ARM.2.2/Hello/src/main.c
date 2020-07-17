#include "S32K144.h"
#include "S32K144_features.h"

#define RED     15
#define GREEN   16
#define BLUE    0

#define BTN0    12
#define BTN1    13
#define BIT(n)  (1 << (n))

#define m_interrupts_start       = 0x00002000;
#define m_interrupts_end         = 0x000023FF;

#define m_flash_config_start     = 0x00002400;
#define m_flash_config_end       = 0x0000240F;

#define m_text_start             = 0x00002410;
#define m_text_end               = 0x0007FFFF;

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;
typedef void (*pFunction)(void);
typedef  void (*iapfun)(void);
pFunction Jump_To_Application;
pFunction jump2app;

#define FLASH_APP1_ADDR     0x00042000

static void Clock_Config(void);
static void Gpio_Config(void);
static void LED_light(u8 color);
void MSR_MSP(u32 addr);
static void iap_load_app(u32 appxaddr);

static u8 color = 0;

int main(void)
{
    u32 cnt;

    cnt = 0;

        Clock_Config();
        Gpio_Config();
        LED_light(7);

        while (1) {
                cnt ++;

                if (PTC->PDIR & (BIT(BTN0) | BIT(BTN1))) {
                        LED_light(0);
                        iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
                } else {
                        LED_light(7);
                }
        }
}

void RTC_Seconds_IRQHandler(void)
{
        LED_light(color ++ % 8);
}

void SOSC_init_8MHz(void)
{
        SCG->SOSCDIV=0x00000101; /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
        SCG->SOSCCFG=0x00000024;
        /* Range=2: Medium freq (SOSC between 1MHz-8MHz)*/
        /* HGO=0: Config xtal osc for low power */
        /* EREFS=1: Input is external XTAL */
        while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
        SCG->SOSCCSR=0x00000001;
        /* LK=0: SOSCCSR can be written */
        /* SOSCCMRE=0: OSC CLK monitor IRQ if enabled */
        /* SOSCCM=0: OSC CLK monitor disabled */
        /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
        /* SOSCLPEN=0: Sys OSC disabled in VLP modes */
        /* SOSCSTEN=0: Sys OSC disabled in Stop modes */
        /* SOSCEN=1: Enable oscillator */
        while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}

void SPLL_init_160MHz(void)
{
        while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
        SCG->SPLLCSR = 0x00000000; /* SPLLEN=0: SPLL is disabled (default) */
        SCG->SPLLDIV = 0x00000302; /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
        SCG->SPLLCFG = 0x00180000; /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
        /* MULT=24: Multiply sys pll by 4+24=40 */
        /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
        while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
        SCG->SPLLCSR = 0x00000001;
        /* LK=0: SPLLCSR can be written */
        /* SPLLCMRE=0: SPLL CLK monitor IRQ if enabled */
        /* SPLLCM=0: SPLL CLK monitor disabled */
        /* SPLLSTEN=0: SPLL disabled in Stop modes */
        /* SPLLEN=1: Enable SPLL */
        while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}

void NormalRUNmode_80MHz (void)
{
        /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
        SCG->RCCR=SCG_RCCR_SCS(6) | SCG_RCCR_DIVCORE(1) | SCG_RCCR_DIVBUS(1) | SCG_RCCR_DIVSLOW(2);
        while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}
        /* Wait for sys clk src = SPLL */
}

static void Clock_Config(void)
{
        SOSC_init_8MHz(); /* Initialize system oscillator for 8 MHz xtal */
        SPLL_init_160MHz(); /* Initialize sysclk to 160 MHz with 8 MHz SOSC */
        NormalRUNmode_80MHz(); /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
}

static void Gpio_Config(void)
{
        //config clock source
        PCC->PCCn[PCC_PORTD_INDEX] = 0x40000000;
        PCC->PCCn[PCC_PORTC_INDEX] = 0x40000000;
        //config LED
        PORTD->PCR[RED] = 0x00000100;
        PORTD->PCR[GREEN] = 0x00000100;
        PORTD->PCR[BLUE] = 0x00000100;
        //set direction
        PTD->PDDR |= BIT(RED) | BIT(GREEN) | BIT(BLUE);
        //default output
        PTD->PDOR |= BIT(RED) | BIT(GREEN) | BIT(BLUE);

        //config BTN
        PORTC->PCR[BTN0] = 0x00000100;
        PORTC->PCR[BTN1] = 0x00000100;

        //set direction
        PTC->PDDR &=~(BIT(BTN0) | BIT(BTN1));
}

static void LED_light(u8 color)
{
        PTD->PDOR |= BIT(RED) | BIT(GREEN) | BIT(BLUE);

        if (color & 0x01)
                PTD->PDOR &=~BIT(RED);
        if (color & 0x02)
                PTD->PDOR &=~BIT(GREEN);
        if (color & 0x04)
                PTD->PDOR &=~BIT(BLUE);
}

void MSR_MSP(u32 addr)
{
__asm("MSR MSP, r0");
__asm("MSR PSP, r0");
S32_SCB->VTOR = (uint32_t)FLASH_APP1_ADDR;
__asm("LDR r0,=#0x00042004");   //load address of main function (use any address you need)
__asm("BLX r0");   //jump to this address
}

void iap_load_app(u32 appxaddr)
{
//	void (*entry)(void);
//	uint32_t pc;
    if(((*(volatile u32*)appxaddr)&0x2FFE0000)==0x20000000)   //检查栈顶地址是否合法.
    {

        MSR_MSP(*(volatile u32*)appxaddr);                    //初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
//        pc = *((volatile uint32_t *)(appxaddr + 4));
//        entry = (void (*)(void))pc;
//           entry();
//        jump2app=(iapfun)*(u32*)(appxaddr+4);       //用户代码区第二个字为程序开始地址(复位地址)
//        jump2app();                                 //跳转到APP.
    }
}
