cmake_minimum_required(VERSION 3.5.0)

if(Board STREQUAL "stm32f103_ethercat")

    set(Startup_ASM
        ${PATH_WORKSPACE_ROOT}/arch/arm/arm-v7m/cortex-m3/cortex_m3_startup_gcc.s
    )
    set_property(GLOBAL PROPERTY Startup_ASM ${Startup_ASM})
    
    set_property(GLOBAL PROPERTY LINKER_SCRIPT 
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/stm32f103_flash_sram.ld
    )
    set_property(GLOBAL PROPERTY Board_Sources
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/board_bsp.c
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/bsp/spi/stm32f103_spi2.c
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/bsp/spi/stm32f103_ethercat_spi.c
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/bsp/uart/stm32f103_debug_uart.c
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/bsp/timer/stm32f103_timer2.c
        ${PATH_WORKSPACE_ROOT}/board/stm32f103_ethercat/bsp/esc_gpio.c
    )
    set_property(GLOBAL PROPERTY Board_Includes

    )

elseif(Board STREQUAL "HPM6450")

    set(Startup_ASM
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/toolchains/gcc/start.S
    )
    set_property(GLOBAL PROPERTY Startup_ASM ${Startup_ASM})

    set_property(GLOBAL PROPERTY LINKER_SCRIPT 
        ${PATH_WORKSPACE_ROOT}/board/HPM6450/ram.ld
    )
    set_property(GLOBAL PROPERTY Board_Sources
        ${PATH_WORKSPACE_ROOT}/board/HPM6450/board_bsp.c
        ${PATH_WORKSPACE_ROOT}/board/HPM6450/bsp/hpm6450dp_uart12.c
    )
    set(GLOBAL PROPERTY Board_Includes
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/HPM6750/
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/HPM6700/ip/
        ${PATH_WORKSPACE_ROOT}/drivers/HPM/drivers/inc/
    )


endif()




# 指定启动文件
