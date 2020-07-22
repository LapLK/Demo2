
/*
    by: b35970@freescale.com
*/

#include "common.h"
#include "global.h"
#include "hal_spi.h"





#define PAGE_SIZE 256

#define CMD_GET_ID      0x9f
#define CMD_BLOCK_ERASE 0x20
#define CMD_DEV_ERASE   0x60
#define CMD_PROGRAM     0x02
#define CMD_READ        0x0B
#define CMD_GET_SR      0x05
#define CMD_SET_SR      0x01
#define CMD_WRITE_EN    0x06
#define CMD_WRITE_DIS   0x04



static byte get_sr(void)
{
    byte v;
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_GET_SR,false);
    v = hal_spi_transfer_one_byte(0x00,true);
    hal_spi_transfe_stop();
    return v;
}
static void write_enable(void)
{
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_WRITE_EN,true);
    hal_spi_transfe_stop();
}
static void wait(void)
{
    while(get_sr()&0x01 == 0x01)
        ;
}

static void global_unprotected(void)
{
    write_enable();
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_SET_SR,false);
    hal_spi_transfer_one_byte(0,true);
    hal_spi_transfe_stop();
    wait();
}
void hal_spi_dev_flash_get_id_test(void)
{
    u8 v;
    printf("test - get - id, should get 0x1f, 0x45, 0x01.\n");
    hal_spi_transfe_start();
    v = hal_spi_transfer_one_byte(CMD_GET_ID,false);
    v = hal_spi_transfer_one_byte(0x00,false); printf("v=%x\n",v);
    v = hal_spi_transfer_one_byte(0x00,false); printf("v=%x\n",v);
    v = hal_spi_transfer_one_byte(0x00,false); printf("v=%x\n",v);
    v = hal_spi_transfer_one_byte(0x00,true);  printf("v=%x\n",v);
    hal_spi_transfe_stop();
}
uint hal_spi_dev_flash_get_id(void)
{
    uint r = 0;
    printf("test - get - id\n");
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_GET_ID,false);
    r |= hal_spi_transfer_one_byte(0x00,false)<<0;
    r |= hal_spi_transfer_one_byte(0x00,false)<<8;
    r |= hal_spi_transfer_one_byte(0x00,false)<<16;
    r |= hal_spi_transfer_one_byte(0x00,true)<<24;
    hal_spi_transfe_stop();
    return r;
}
void hal_spi_dev_flash_erase_block(uint addr)
{
    write_enable();
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_BLOCK_ERASE,false);
    hal_spi_transfer_one_byte(addr>>16,false);
    hal_spi_transfer_one_byte(addr>>8, false);
    hal_spi_transfer_one_byte(addr>>0, true);
    hal_spi_transfe_stop();
    wait();
}
void hal_spi_dev_flash_erase_dev(void)
{
    write_enable();
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_DEV_ERASE,true);
    hal_spi_transfe_stop();
    wait();
}
void hal_spi_dev_flash_program_byte(uint addr, byte b)
{
    write_enable();
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_PROGRAM,false);
    hal_spi_transfer_one_byte(addr>>16,false);
    hal_spi_transfer_one_byte(addr>>8, false);
    hal_spi_transfer_one_byte(addr>>0, false);
    hal_spi_transfer_one_byte(b, true);
    hal_spi_transfe_stop();

    wait();
}
void hal_spi_dev_flash_program_page(uint addr, char *buf)
{
    int i;
    write_enable();
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_PROGRAM,false);
    hal_spi_transfer_one_byte(addr>>16,false);
    hal_spi_transfer_one_byte(addr>>8, false);
    hal_spi_transfer_one_byte(addr>>0, false);
    for(i=0;i<(PAGE_SIZE-1);i++)
        hal_spi_transfer_one_byte(buf[i],false);
    hal_spi_transfer_one_byte(buf[i],true);
    hal_spi_transfe_stop();
    wait();
}
byte hal_spi_dev_flash_read_byte(uint addr)
{
    byte r;
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_READ,false);
    hal_spi_transfer_one_byte(addr>>16,false);
    hal_spi_transfer_one_byte(addr>>8, false);
    hal_spi_transfer_one_byte(addr>>0, false);
    hal_spi_transfer_one_byte(0x00,false);
    r = hal_spi_transfer_one_byte(0x00,true);
    hal_spi_transfe_stop();
    return r;
}
void hal_spi_dev_flash_read_page(uint addr, char *buf)
{
    int i;
    hal_spi_transfe_start();
    hal_spi_transfer_one_byte(CMD_READ,false);
    hal_spi_transfer_one_byte(addr>>16,false);
    hal_spi_transfer_one_byte(addr>>8, false);
    hal_spi_transfer_one_byte(addr>>0, false);
    hal_spi_transfer_one_byte(0x00,false);
    for(i=0;i<(PAGE_SIZE-1);i++)
        buf[i] = hal_spi_transfer_one_byte(0x00,false);
    buf[i] = hal_spi_transfer_one_byte(0x00,true);
    hal_spi_transfe_stop();
}
uint hal_spi_dev_flash_get_page_size(void)
{
    return 256;
}
uint hal_spi_dev_flash_get_block_size(void)
{
    return 1024*4;
}
uint hal_spi_dev_flash_get_dev_size(void)
{
    return 0x100000;
}
void hal_spi_dev_flash_test2(void)
{
    global_unprotected();
}

void print_buf(void *buf, uint size)
{
    int i;
    byte *p = (byte*)buf;
    for(i=0;i<size;i++)
    {
        printf("0x%.2x,", p[i]);
        if(((i+1)&0x3) == 0)
            printf("  ");
        if(((i+1)&0x7) == 0)
            printf("\n");
    }

    printf("\n");
}
void hal_spi_dev_flash_test(void)
{
    static char buf[256];
    int i;

    hal_spi_dev_flash_get_id_test();

    printf("unprotecting:...\n");
    global_unprotected();
    printf("erasing:...\n");
    hal_spi_dev_flash_erase_block(0);
    printf("reading page...\n");
    hal_spi_dev_flash_read_page(0,buf);
    print_buf(buf,PAGE_SIZE);

    printf("programing a page...\n");
    for(i=0;i<256;i++)
        buf[i] = i+0x30;
    hal_spi_dev_flash_program_page(0,buf);

    printf("clearing buffer..\n");
    for(i=0;i<256;i++)
        buf[i] = 0;

    printf("reading page...\n");
    hal_spi_dev_flash_read_page(0,buf);
    print_buf(buf,PAGE_SIZE);
    
    printf("demo end.\n");
}

