cmake_minimum_required(VERSION 3.5.0)

if(Board STREQUAL "stm32f103_ethercat")
    set_property(GLOBAL PROPERTY Driver_Sources
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/misc.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
    )
    set_property(GLOBAL PROPERTY Driver_Includes
        ${PATH_WORKSPACE_ROOT}/drivers/STM32F10x_StdPeriph_Driver/inc
    )

elseif(Board STREQUAL "HPM6450")

    set_property(GLOBAL PROPERTY Driver_Sources

        ${PATH_WORKSPACE_ROOT}/drivers/HPM/drivers/src/hpm_pcfg_drv.c
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/drivers/src/hpm_pllctl_drv.c
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/drivers/src/hpm_uart_drv.c
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/HPM6750/hpm_clock_drv.c
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/HPM6750/hpm_sysctl_drv.c
    )
    set_property(GLOBAL PROPERTY Driver_Includes
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/HPM6750/
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/ip/
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/drivers/inc/
    )
endif()


set_property(GLOBAL PROPERTY Common_Driver_Sources
    ${PATH_WORKSPACE_ROOT}/drivers/Common_Drivers/ET1100/ET1100.c
)

set_property(GLOBAL PROPERTY Common_Driver_Includes
    ${PATH_WORKSPACE_ROOT}/drivers/Common_Drivers/ET1100/
)