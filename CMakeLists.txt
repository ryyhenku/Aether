



INCLUDE(CMakeForceCompiler) 
CMAKE_FORCE_C_COMPILER(gcc GNU)
CMAKE_FORCE_CXX_COMPILER(g++ GNU)

cmake_minimum_required(VERSION 3.5.0)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_COLOR_DIAGNOSTICS false)


#全局使用 PATH_WORKSPACE_ROOT来定位根目录
set(PATH_WORKSPACE_ROOT ${CMAKE_CURRENT_LIST_DIR})

#指定代码入口 默认main
set(Entry "Reset_Handler" CACHE STRING "Entry")

#指定arch board
set(Arch "riscv" CACHE STRING "Target Arch")
set(Board "HPM6450" CACHE STRING "Target Board")

if(Arch STREQUAL "arm")
    include(${PATH_WORKSPACE_ROOT}/tools/arm/compile_cmake/arm-none-eabi.cmake)
elseif(Arch STREQUAL "riscv")
    include(${PATH_WORKSPACE_ROOT}/tools/riscv/compile_cmake/riscv.cmake)
endif()


if(Board STREQUAL "stm32f103_ethercat")
    set(MCPU_FLAGS "-mcpu=cortex-m3 -mthumb" CACHE STRING "MCPU_FLAGS")
    add_compile_definitions(-DSTM32F10X_HD -DHSE_VALUE=12000000)
elseif(Board STREQUAL "stm32f407")
    set(MCPU_FLAGS "-mcpu=cortex-m4 -mthumb" CACHE STRING "MCPU_FLAGS")
    set(VFP_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16"  CACHE STRING "VFP_FLAGS")
    add_compile_definitions(-DSTM32F40_41xxx -DHSE_VALUE=8000000)
elseif(Board STREQUAL "HPM6450")
    set(MCPU_FLAGS "-march=rv32imafdc -mabi=ilp32f" CACHE STRING "MCPU_FLAGS")
endif()

#导入子模块
add_subdirectory(arch)        
add_subdirectory(board)        
add_subdirectory(component)     
add_subdirectory(drivers)     
add_subdirectory(subsys)   
add_subdirectory(app)   

get_property(Arch_Sources GLOBAL PROPERTY Arch_Sources)
get_property(Board_Sources GLOBAL PROPERTY Board_Sources)
get_property(Component_Sources GLOBAL PROPERTY Component_Sources)
get_property(Driver_Sources GLOBAL PROPERTY Driver_Sources)
get_property(Subsys_Sources GLOBAL PROPERTY Subsys_Sources)
get_property(App_Sources GLOBAL PROPERTY App_Sources)
get_property(Common_Driver_Sources  GLOBAL PROPERTY Common_Driver_Sources)

get_cmake_property(vars GLOBAL PROPERTIES)

get_property(Arch_Includes GLOBAL PROPERTY Arch_Includes)
get_property(Board_Includes GLOBAL PROPERTY Board_Includes)
get_property(Component_Includes GLOBAL PROPERTY Component_Includes)
get_property(Driver_Includes GLOBAL PROPERTY Driver_Includes)
get_property(Subsys_Includes GLOBAL PROPERTY Subsys_Includes)
get_property(App_Includes GLOBAL PROPERTY App_Includes)
get_property(Common_Driver_Includes GLOBAL PROPERTY Common_Driver_Includes)
get_property(LINKER_SCRIPT GLOBAL PROPERTY LINKER_SCRIPT)
get_property(Startup_ASM GLOBAL PROPERTY Startup_ASM)

project(application  
        VERSION 1.0.0 
        LANGUAGES C CXX ASM)

#输出目录
set(OUTPUT_DIR  ${CMAKE_CURRENT_LIST_DIR}/build)



set(ELF_FILE_PATH ${OUTPUT_DIR}/${PROJECT_NAME}.elf)
set(HEX_FILE_PATH ${OUTPUT_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE_PATH ${OUTPUT_DIR}/${PROJECT_NAME}.bin)

#整合
message(STATUS "Binary output directory: ${OUTPUT_DIR}")
message(STATUS "ELF file: ${ELF_FILE_PATH}")
message(STATUS "HEX file: ${HEX_FILE_PATH}")
message(STATUS "BIN file: ${BIN_FILE_PATH}")

set(Build_All_SRC
    ${Startup_ASM}
    ${Arch_Sources}
    ${Board_Sources}
    ${Component_Sources} 
    ${Driver_Sources}
    ${Common_Driver_Sources}   
    ${Subsys_Sources}  
    ${App_Sources}    
)
include_directories(
    ${Arch_Includes}
    ${Board_Includes}
    ${Component_Includes} 
    ${Common_Driver_Includes}
    ${Driver_Includes}   
    ${Subsys_Includes}  
    ${App_Includes}    
)

# 定义调试模式编译参数；

SET(CFCOMMON
    "${MCPU_FLAGS} ${VFP_FLAGS} --specs=nosys.specs -Wall -fmessage-length=0 -ffunction-sections -fdata-sections"
)


SET(CMAKE_C_FLAGS "-O0 -g  ${CFCOMMON}")
SET(CMAKE_CXX_FLAGS "-O0 -g  ${CFCOMMON} -fno-exceptions")
SET(CMAKE_ASM_FLAGS "-O0 -g ${CFCOMMON}")


add_executable(${PROJECT_NAME}.elf ${Build_All_SRC} )


target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}    
    -Wl,--entry=${Entry}        
    -Wl,-Map=${OUTPUT_DIR}/${PROJECT_NAME}.map  
)

target_link_libraries(${PROJECT_NAME}.elf
    -lc
    -lm
    -lnosys
)

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