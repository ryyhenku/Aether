SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m3)

set(MCPU_FLAGS "-mcpu=cortex-m3 -mthumb")

INCLUDE(${PATH_WORKSPACE_ROOT}/tools/arm/compile_cmake/arm-none-eabi.cmake)