

/* 目前打算在这里添加用到的设备 */

void board_bsp_devs_register()
{
    st_rcc_dev_register();
    st_gpio_dev_register();
    st_uart1_dev_register();
    st_tim1pwm_dev_register();
    st_tim2_period_dev_register();
}


void board_init()
{
    board_bsp_devs_register();
}