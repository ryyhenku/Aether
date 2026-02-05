SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(MCPU_FLAGS "-mcpu=cortex-m4 -mthumb")
set(VFP_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")

INCLUDE(${PATH_WORKSPACE_ROOT}/tools/arm/compile_cmake/arm-none-eabi.cmake)