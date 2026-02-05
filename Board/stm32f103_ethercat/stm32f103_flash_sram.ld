/* 定义内存区域 */
MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 48K
}

/* 定义堆栈大小 */
__main_stack_top = ORIGIN(RAM) + LENGTH(RAM);    /* 栈顶位于RAM末尾 */

ENTRY(Reset_Handler)

/* 定义输出段 */
SECTIONS
{
    /* 中断向量表放在FLASH起始位置 */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))    /* 保留启动文件中的g_pfnVectors段 */
        . = ALIGN(4);
    } >FLASH

    /* 程序代码 */
    .text :
    {
        . = ALIGN(4);
        *(.text)                /* .text段(代码) */
        *(.text*)              /* 所有.text*段 */
        *(.glue_7)             /* 兼容性支持 */
        *(.glue_7t)             /* 兼容性支持 */
        *(.eh_frame)
        
        KEEP (*(.init))
        KEEP (*(.fini))
        
        . = ALIGN(4);
        _etext = .;             /* 定义代码段结束地址 */
    } >FLASH

    /* 只读数据 */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)             /* .rodata段(只读数据) */
        *(.rodata*)            /* 所有.rodata*段 */
        . = ALIGN(4);
    } >FLASH

    /* 初始化数据(.data) - 在FLASH中存储，启动时复制到RAM */
    _sidata = LOADADDR(.data);
    .data : 
    {
        . = ALIGN(4);
        _sdata = .;            /* .data段在RAM中的起始地址 */
        *(.data)              /* .data段 */
        *(.data*)             /* 所有.data*段 */
        . = ALIGN(4);
        _edata = .;            /* .data段在RAM中的结束地址 */
    } >RAM AT> FLASH

    /* 未初始化数据(.bss) - 启动时清零 */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;             /* .bss段起始地址 */
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;             /* .bss段结束地址 */
        . = ALIGN(4);
        PROVIDE(end = .);      /* 定义 'end' 符号 给printf用 */
    } >RAM

}