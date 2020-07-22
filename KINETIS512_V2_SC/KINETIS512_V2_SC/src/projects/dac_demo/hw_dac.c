/*
 * File:		dac12bit.c
 * Purpose:		function implementations
 *
 */

#include "hw_dac.h"
#include <stdint.h>



static void _buf_reg_config (DAC_MemMapPtr dacx_base_ptr,byte WatermarkMode, byte BuffMode, byte Vreference, byte TrigMode, byte BuffInitPos,byte BuffUpLimit);
static void _buf_fill_data( DAC_MemMapPtr dacx_base_ptr);
static int  _set_dac_buffer( DAC_MemMapPtr dacx_base_ptr, byte dacindex, int buffval);
static void _pdb_init(void);
static void _vref_init(void);


static void dac_set(int value)
{
    DAC_DATH_REG(DAC0_BASE_PTR,0) = (value>>8)&0xf;
    DAC_DATL_REG(DAC0_BASE_PTR,0) = value&0xff;
}
static void dac_delta(int value)
{
    uint16 v;

    v  = (DAC_DATH_REG(DAC0_BASE_PTR,0)<<8);
    v |= (DAC_DATL_REG(DAC0_BASE_PTR,0));
    v += value;
    dac_set(v);
    printf("dac value: %d\n", v);
}
static void _dac_key_ops(int delta)
{
    char c;
    printf("(u)p, (d)own, e(x)it\n");
    while(1)
    {
        c = in_char();
        if(c == 'u')
            dac_delta(delta);
        else if(c == 'd') 
            dac_delta(-1*delta);
        else if(c == 'x') 
            break;
        else;
    }
}
static void _dac0_reg_init(void)
{
    unsigned char dacbuff_index = 0;   

    for (dacbuff_index=0; dacbuff_index<16;dacbuff_index++)
    {
        _set_dac_buffer( DAC0_BASE_PTR, dacbuff_index, DACx_DAT_RESET); 
    }

    DAC_SR_REG(DAC0_BASE_PTR) = DACx_SR_RESET;
    DAC_C0_REG(DAC0_BASE_PTR) = DACx_C0_RESET;
    DAC_C1_REG(DAC0_BASE_PTR) = DACx_C1_RESET;
    DAC_C2_REG(DAC0_BASE_PTR) = DACx_C2_RESET;
}
static void _dac_buf_init(DAC_MemMapPtr dacx_base_ptr,byte BuffMode, byte vref, byte TrigMode, byte BuffInitPos, byte BuffUpLimit)
{
    // Initilized DAC1
    _buf_reg_config(dacx_base_ptr,DAC_BFWM_1WORD, BuffMode, vref, TrigMode,BuffInitPos, BuffUpLimit);
    // buffer content increases by 256
    _buf_fill_data(dacx_base_ptr);
}

/**************************************************************/ 
void dac0_clk_enable (void )
{
    SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK; //Allow clock to enable DAC0
}
void _vref_init(void)
{
    SIM_SCGC4 |= SIM_SCGC4_VREF_MASK;
    VREF_SC = 0x81;// Enable Vrefo and select internal mode
    //VREF_SC = 0x82; // Tight-regulation mode buffer enabled is reconmended over low buffered mode
    while (!(VREF_SC & VREF_SC_VREFST_MASK)  ){} // wait till the VREFSC is stable
}
void _buf_reg_config (DAC_MemMapPtr dacx_base_ptr, byte WatermarkMode, byte BuffMode, byte vref, byte TrigMode, byte BuffInitPos,byte BuffUpLimit){

    DAC_C0_REG(dacx_base_ptr) = ( DAC_BFB_PTR_INT_DISABLE |             
                                  DAC_BFT_PTR_INT_DISABLE |             
                                  DAC_BFWM_INT_DISABLE  |             
                                  DAC_HP_MODE    |             
                                  DAC_SW_TRIG_STOP |            
                                  TrigMode |  
                                  vref |     
                                  DAC_ENABLE    // DAC enalbed
                                  );  
    
    if (vref == DAC_SEL_VREF) 
        _vref_init();

    DAC_C1_REG(dacx_base_ptr) = ( DAC_BF_ENABLE  |  //Buffer Enabled            
                                  WatermarkMode |  // set 1, 2, 3,or 4 word(s) mode           
                                  BuffMode        // set traversal mode, normal, swing, or onetime   
                                  );

    DAC_C2_REG(dacx_base_ptr) = BuffInitPos | BuffUpLimit;
}


void _buf_fill_data( DAC_MemMapPtr dacx_base_ptr)
{  
    int data = 0; 
    byte i =  0;
    
    // for loop: Initializes the buffer words so that next buffer has an increment of 256 except last one (255)  
    for (i=0; i<16; i++)
    {
        if(i == 15)
        {
            //Last buffer.The last word buffer (16th word) will have the value (16*0xff)-1 = 4096-1=4095=0xFFF. 
            data+= 255; 
        }
        else
        { 
            //Not last buffer.The next word buffer will have increment of 0xFF from previous word buffer.         
            data+= 256;             
        }

        _set_dac_buffer( dacx_base_ptr, i, data);
    }
}
int _set_dac_buffer( DAC_MemMapPtr dacx_base_ptr, byte dacindex, int buffval)
{
    int temp = 0; 
    // initialize all 16 words buffer with a the value buffval
    DAC_DATL_REG(dacx_base_ptr, dacindex)  =   (buffval&0x0ff); 
    DAC_DATH_REG(dacx_base_ptr, dacindex)  =   (buffval&0xf00) >>8;                                
    temp  = DAC_DATH_REG(dacx_base_ptr, dacindex)<<8;
    temp |= DAC_DATL_REG(dacx_base_ptr, dacindex);
    return temp; 
}
void _pdb_init(void)
{
    SIM_SCGC6     |= SIM_SCGC6_PDB_MASK; // enable system clock to PDB
    PDB0_SC        = PDB_SC_PDBEN_MASK;  // enable PDB module
    PDB0_DACINT0   = 60000;              // Effective after writting PDBSC_DACTOE = 1, DAC output changes are base on the interval defined by this value
    PDB0_SC       |=PDB_SC_LDOK_MASK   ; // load the value assigned to PDB_DACINT0 to register   
    PDB0_SC       |= PDB_SC_TRGSEL(15);  // software trigger
    PDB0_SC       |=PDB_SC_CONT_MASK;    // CONT mode
    PDB0_DACINTC0 |= PDB_INTC_TOE_MASK;  // DAC output delay from PDB Software trigger
    PDB0_SC       |= PDB_SC_SWTRIG_MASK; // reset counter to 0. This triggers the PDB input. 
}
void test_dac_vref(void)
{
    _dac0_reg_init();
    _vref_init();
    
    DAC_C0_REG(DAC0_BASE_PTR)  = ( DAC_BFB_PTR_INT_DISABLE |
                                   DAC_BFT_PTR_INT_DISABLE |
                                   DAC_BFWM_INT_DISABLE    |
                                   DAC_HP_MODE             |
                                   DAC_SW_TRIG_STOP        |
                                   DAC_SEL_SW_TRIG         |
                                   DAC_SEL_VREF            | // vref = 1.2V
                                   DAC_ENABLE ); 

    // Buffer disabled
    DAC_C1_REG(DAC0_BASE_PTR)= ( DAC_BF_DISABLE  |  
                                 DAC_BF_NORMAL_MODE |          
                                 DAC_BFWM_1WORD |
                                 DAC_DMA_DISABLE  );

    DAC_C2_REG(DAC0_BASE_PTR) = DAC_SET_PTR_AT_BF(0)| DAC_SET_PTR_UP_LIMIT(0x0f);

    _dac_key_ops(20);
}
void test_dac_buffer_mode_normal(void)
{
    int j = 0;

    _dac0_reg_init();//reset DAC0 value to default reset value;  
    _dac_buf_init( DAC0_BASE_PTR, 
                   DAC_BF_NORMAL_MODE, 
                   DAC_SEL_VREF,
                   DAC_SEL_SW_TRIG,
                   DAC_SET_PTR_AT_BF(0),
                   DAC_SET_PTR_UP_LIMIT(15) ); 
    while (1)
    {
        DAC_C0_REG(DAC0_BASE_PTR) |= DAC_SW_TRIG_NEXT; //SW trigger to advance to DAC0's next word buffer
        for (j=0;j<10000;j++){}  // random delay
    }
}
void test_dac_buffer_mode_swing(void)
{
    int j = 0;

    _dac0_reg_init();//reset DAC0 value to default reset value;  
    _dac_buf_init( DAC0_BASE_PTR, 
                   DAC_BF_SWING_MODE, 
                   DAC_SEL_VREF,
                   DAC_SEL_SW_TRIG,
                   DAC_SET_PTR_AT_BF(0),
                   DAC_SET_PTR_UP_LIMIT(15) ); 
    while (1)
    {
        DAC_C0_REG(DAC0_BASE_PTR) |= DAC_SW_TRIG_NEXT; //SW trigger to advance to DAC0's next word buffer
        for (j=0;j<10000;j++){}  // random delay
    }
}
void test_dac_buffer_mode_one_time(void)
{
    int j = 0;

    _dac0_reg_init();//reset DAC0 value to default reset value;  
    _dac_buf_init( DAC0_BASE_PTR, 
                   DAC_BF_ONE_TIME_MODE, 
                   DAC_SEL_VREF,
                   DAC_SEL_SW_TRIG,
                   DAC_SET_PTR_AT_BF(0),
                   DAC_SET_PTR_UP_LIMIT(15));
    while (1)
    {
        DAC_C0_REG(DAC0_BASE_PTR) |= DAC_SW_TRIG_NEXT; //SW trigger to advance to DAC0's next word buffer
        for (j=0;j<10000;j++){}  // random delay
    }
}
void test_dac_triggered_by_pdb(void)
{
    _dac0_reg_init();
    _dac_buf_init( DAC0_BASE_PTR, 
                   DAC_BF_SWING_MODE,
                   DAC_SEL_VREF,
                   DAC_SEL_PDB_HW_TRIG,
                   DAC_SET_PTR_AT_BF(0),
                   DAC_SET_PTR_UP_LIMIT(15));
    _pdb_init();  
}





 






















