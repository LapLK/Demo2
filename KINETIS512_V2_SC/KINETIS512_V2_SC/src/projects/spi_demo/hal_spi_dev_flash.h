

uint hal_spi_dev_flash_get_id(void);
void hal_spi_dev_flash_erase_block(uint addr);
void hal_spi_dev_flash_erase_dev(void);
void hal_spi_dev_flash_program_byte(uint addr, byte b);
void hal_spi_dev_flash_program_page(uint addr, char *buf);
byte hal_spi_dev_flash_read_byte(uint addr);
void hal_spi_dev_flash_read_page(uint addr, char *buf);
uint hal_spi_dev_flash_get_page_size(void);
uint hal_spi_dev_flash_get_block_size(void);
uint hal_spi_dev_flash_get_dev_size(void);


void hal_spi_dev_flash_get_id_test(void);
void hal_spi_dev_flash_test(void);

