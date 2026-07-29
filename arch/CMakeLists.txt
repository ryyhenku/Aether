cmake_minimum_required(VERSION 3.5.0)

if(Arch STREQUAL "arm")

    set_property(GLOBAL PROPERTY Arch_Sources
        ${PATH_WORKSPACE_ROOT}/arch/arm/arm-v7m/systick_delay.c
    )


elseif(Arch STREQUAL "riscv")

    set_property(GLOBAL PROPERTY Arch_Sources
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/toolchains/gcc/stdio_weak.c
        ${PATH_WORKSPACE_ROOT}/arch/riscv/l1c/hpm_l1c_drv.c
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/toolchains/reset.c
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/toolchains/initfini.c
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/system.c
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/trap.c
    )
    set_property(GLOBAL PROPERTY Arch_Includes
        ${PATH_WORKSPACE_ROOT}/arch/
        ${PATH_WORKSPACE_ROOT}/arch/riscv/hpm/
        ${PATH_WORKSPACE_ROOT}/arch/riscv/l1c/
    )
endif()