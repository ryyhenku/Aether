cmake_minimum_required(VERSION 3.5.0)

set_property(GLOBAL PROPERTY Subsys_Sources
    ${PATH_WORKSPACE_ROOT}/subsys/uart_hal/subsys_uart.c
    ${PATH_WORKSPACE_ROOT}/subsys/spi_hal/subsys_spi.c
    ${PATH_WORKSPACE_ROOT}/subsys/period_timer_hal/subsys_period_timer.c
    ${PATH_WORKSPACE_ROOT}/subsys/pwm_hal/subsys_pwm.c
    ${PATH_WORKSPACE_ROOT}/subsys/clk_hal/subsys_clk.c
    ${PATH_WORKSPACE_ROOT}/subsys/gpio_hal/subsys_gpio.c
)
set_property(GLOBAL PROPERTY Subsys_Includes
    ${PATH_WORKSPACE_ROOT}/subsys/uart_hal/
    ${PATH_WORKSPACE_ROOT}/subsys/spi_hal/
    ${PATH_WORKSPACE_ROOT}/subsys/period_timer_hal
    ${PATH_WORKSPACE_ROOT}/subsys/pwm_hal
    ${PATH_WORKSPACE_ROOT}/subsys/clk_hal
    ${PATH_WORKSPACE_ROOT}/subsys/gpio_hal
)
