
#include "subsys_spi.h"

spi_ops_t *p_spi_2;
extern void     board_bsp_devs_register();

uint8_t test_buf[5] = {0x0,0x0};
void main()
{
    /*所有的设备都被将被注册，在这之后，可以使用对应外设子系统的接口调用驱动 */
    board_bsp_devs_register();

    p_spi_2 = spi_bus_ops_get_by_name("SPI2");

    /* 初始化SPI1 */
    spi_bus_init(p_spi_2);

    spi_bus_cs_select(p_spi_2);
    /*SPI1写测试*/
    spi_bus_write(p_spi_2,test_buf,2); 
    spi_bus_cs_deselect(p_spi_2);
}