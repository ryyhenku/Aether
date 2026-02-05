SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR riscv32)

set(MCPU_FLAGS "-march=rv32imafdc -mabi=ilp32")

INCLUDE(${PATH_WORKSPACE_ROOT}/tools/riscv/compile_cmake/riscv.cmake)