

/* 目前打算在这里添加用到的设备 */
extern void spi1_dev_register();
extern void spi2_dev_register();
void board_bsp_devs_register()
{
    spi1_dev_register(); /* 注册SPI1 */
    spi2_dev_register();
}