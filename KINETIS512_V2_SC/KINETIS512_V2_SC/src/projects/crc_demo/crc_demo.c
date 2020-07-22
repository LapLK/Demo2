
#include "common.h"


/////////////////////////////////////////////////////////////////////
void crc_config (uint32_t poly,uint32_t tot,uint32_t totr,uint32_t fxor,uint32_t tcrc)
{
    CRC_CTRL=(tot<<30)|(totr<<28)|(fxor<<26)|(tcrc<<24);
    CRC_GPOLY=poly;
}


#define WRITE_AS_SEED 0x02000000
void crc_cal_data_16(uint32_t seed,uint16_t data_in,uint32_t result)
{
    uint32_t data_out;
    int i;

    // write seed
    CRC_CTRL |= WRITE_AS_SEED;
    CRC_CRC = seed;

    // write data
    CRC_CTRL &= ~WRITE_AS_SEED;
    CRC_CRCL  = data_in;

    // wait
    for(i=0;i<20;i++)
        ;

    // read result
    data_out = CRC_CRC;

    if(CRC_CTRL&0x20000000)
    {
        // byte transposition
        data_out = data_out>>16;
    }
    else
    {
        data_out &= 0x0000FFFF;
    }
    
    printf("expected value: %x, actual value: %x\n", result, data_out);
}
void crc_cal_data_32(uint32_t seed,uint32_t data_in,uint32_t result)
{
    uint32_t data_out;
    int i;

    // write seed
    CRC_CTRL |= WRITE_AS_SEED;
    CRC_CRC = seed;

    // write data
    CRC_CTRL &= ~WRITE_AS_SEED;
    CRC_CRC   = data_in;

    // wait
    for(i=0;i<20;i++)
        ;

    // read result
    data_out = CRC_CRC;

    if(CRC_CTRL&0x20000000)
    {
        // byte transposition
        data_out = data_out>>16;
    }
    else
    {
        data_out &= 0x0000FFFF;
    }
    
    printf("expected value: %x, actual value: %x\n", result, data_out);
}
/////////////////////////////////////////////////////////////////////


void main(void)
{
    printf("----------------crc demo------------------\n");
    SIM_SCGC6 |= SIM_SCGC6_CRC_MASK;

    crc_config(0x8005,1,2,0,0);
    crc_cal_data_16(0x0000,0x4142,0x61B0);
    crc_cal_data_32(0x0000,0x31323334,0x14BA);
    crc_cal_data_16(0xFFFF,0x4142,0xD1B1);
    crc_cal_data_32(0xFFFF,0x31323334,0x30BA);
    while(1);
}
