

#reset target
monitor reset
monitor sleep 100

#select endian
monitor endian little

monitor flash breakpoints 1

# 初始化时钟
monitor long 0xF4002000 = 0x00000001
monitor long 0xF4002000 = 0x00000002

monitor long 0xF4000800 = 0xffffffff
monitor long 0xF4000810 = 0xffffffff
monitor long 0xF4000820 = 0xffffffff
monitor long 0xF4000830 = 0xffffffff

set architecture riscv:rv32
set architecture riscv:rv32
set architecture riscv:rv32