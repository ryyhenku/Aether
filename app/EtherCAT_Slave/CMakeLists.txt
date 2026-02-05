# ######################################################################################################################
# 0 硬件平台信息与编译器信息
# ######################################################################################################################
INCLUDE(CMakeForceCompiler) 
CMAKE_FORCE_C_COMPILER(gcc GNU)
CMAKE_FORCE_CXX_COMPILER(g++ GNU)
# 设置CMAKE最低版本
cmake_minimum_required(VERSION 3.5.0)

# 使用的 C 语言版本
set(CMAKE_C_STANDARD 99)

# 使用的 cpp 版本
set(CMAKE_CXX_STANDARD 17)

# 生成 compile_commands.json，可配合 clangd 实现精准的代码关联与跳转
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# 彩色日志输出
set(CMAKE_COLOR_DIAGNOSTICS false)

# 设置工程绝对路径
set(PATH_WORKSPACE_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../)

# 包含 cortex-m3 配置（必须在 project() 之后）
include(${PATH_WORKSPACE_ROOT}/arch/arm/arm-v7m/cortex-m3/cortex-m3.cmake)

# 设置工程输出路径（必须在 project() 之前设置）
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/build)

# 设置当前的工程名称
project(ethercat_slave  
        VERSION 1.0.0 
        LANGUAGES C CXX ASM)

message(STATUS "**** Building project: ${CMAKE_PROJECT_NAME}, Version: ${CMAKE_PROJECT_VERSION} ****")


# 指定链接文件
set(LINKER_SCRIPT ${PATH_WORKSPACE_ROOT}/Board/stm32f103_ethercat/stm32f103_flash_sram.ld)

# 指定启动文件
set(STARTUP_ASM ${PATH_WORKSPACE_ROOT}/arch/cortex-m3/cortex_m3_startup_gcc.s)

set(OUTPUT_NAME ${PROJECT_NAME})

# 设置所有输出文件到统一的目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置输出文件路径
set(ELF_FILE_PATH ${CMAKE_BINARY_DIR}/${OUTPUT_NAME}.elf)
set(HEX_FILE_PATH ${CMAKE_BINARY_DIR}/${OUTPUT_NAME}.hex)
set(BIN_FILE_PATH ${CMAKE_BINARY_DIR}/${OUTPUT_NAME}.bin)

message(STATUS "Binary output directory: ${CMAKE_BINARY_DIR}")
message(STATUS "ELF file: ${ELF_FILE_PATH}")
message(STATUS "HEX file: ${HEX_FILE_PATH}")
message(STATUS "BIN file: ${BIN_FILE_PATH}")

# ######################################################################################################################
# 2 添加源文件和头文件
# ######################################################################################################################


# 设置启动文件的编译选项
set_source_files_properties(${STARTUP_ASM} PROPERTIES
    LANGUAGE ASM
)

#平台相关
#架构
set(Src_Arch
    ${PATH_WORKSPACE_ROOT}/arch/arm/arm-v7m/cortex-m3/cortex_m3_startup_gcc.s
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/src/misc.c
)
set(Inc_Arch
    ${PATH_WORKSPACE_ROOT}/arch/arm/arm-v7m/cortex-m3
)
#驱动
set(Src_Drivers
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/src/system_stm32f10x.c
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c

)

set(Inc_Drivers
    ${PATH_WORKSPACE_ROOT}/Drivers/STM32F10x_StdPeriph_Driver/inc
)


#子系统
set(Inc_Subsys
    ${PATH_WORKSPACE_ROOT}subsys/spi_hal/

)

set(Src_Subsys
    ${PATH_WORKSPACE_ROOT}subsys/spi_hal/subsys_spi.c

)

# 应用
# 添加源文件
set(Src_App
    ${PATH_WORKSPACE_ROOT}/Board/stm32f103_ethercat/board_bsp.c
    ${PATH_WORKSPACE_ROOT}/Board/stm32f103_ethercat/bsp/stm32f103_ethercat_spi.c
    ${PATH_WORKSPACE_ROOT}/Board/stm32f103_ethercat/bsp/stm32f103_spi2.c
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)


set(Src_ALL
    ${Src_Subsys}
    ${Src_Arch}
    ${Src_Drivers}
    ${Src_App}
)

# 添加头文件目录
include_directories(
    ${Inc_Subsys}
    ${Inc_Arch}
    ${Inc_Drivers}
)



add_definitions(-DSTM32F10X_HD -DHSE_VALUE=12000000)

# 创建可执行文件
add_executable(${PROJECT_NAME}.elf ${Src_ALL} )

#target_link_options（更现代的方式）
target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,--entry=Reset_Handler
    -nostartfiles
    -Wl,--gc-sections         # 垃圾回收未使用的段
    -Wl,-Map=${CMAKE_BINARY_DIR}/${OUTPUT_NAME}.map  # 生成映射文件
)

target_link_libraries(${PROJECT_NAME}.elf
    -lc
    -lm
    -lnosys
)

# ######################################################################################################################
# 3 生成额外的输出文件
# ######################################################################################################################

# 生成 HEX 文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE_PATH}
    COMMENT "Generating HEX file: ${HEX_FILE_PATH}"
)

# 生成 BIN 文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE_PATH}
    COMMENT "Generating BIN file: ${BIN_FILE_PATH}"
)

