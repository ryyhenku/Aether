#include "delay.h"
#include "serial_debug.h"
#include "subsys_clk.h"
#include "subsys_gpio.h"
/* 目前打算在这里添加用到的设备 */
gpio_ops_t * __gpio_dev;
void board_bsp_devs_register()
{
    st_rcc_dev_register();
    st_gpio_dev_register();
    st_uart1_dev_register();
    st_tim1pwm_dev_register();
    st_tim2_period_dev_register();
}
void systick_delay_init(void);
void systick_delay_us(uint32_t nus);
void systick_delay_ms(uint16_t nms);
void board_init()
{
    board_bsp_devs_register();

    /*dev init */
    clk_ops_t* rcc_dev = clk_ops_get();
    /* 时钟初始化 */
    rcc_dev->clk_init();
    __gpio_dev = gpio_ops_get_by_name("GPIO");
    /* 初始化IO */
    __gpio_dev->gpio_init();
    /* component init */
    init_block_delay(systick_delay_init,systick_delay_ms,systick_delay_us);
    init_debug_serial("Debug_UART",115200,Data_Bits_8,Stop_Bits_1,None_Parity);
}