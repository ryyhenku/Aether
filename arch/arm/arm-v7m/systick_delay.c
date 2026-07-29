#include "stm32f4xx.h"

void systick_delay_init(void) {
    // SysTick 使用系统时钟（假设 72MHz）
    // 不启用中断，只用于查询计数
    SysTick->CTRL = 0;            // 先禁用
    SysTick->LOAD = 0xFFFFFF;     // 24位最大值
    SysTick->VAL = 0;             // 清空当前值
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;  // 选择系统时钟，不使能中断
}

void systick_delay_us(uint32_t us) {
    // 1us 需要计数的次数 = 时钟频率(MHz) = 72 次
    uint32_t ticks = us * 168;  // 72MHz 时
    
    SysTick->LOAD = ticks;      // 设置重装值
    SysTick->VAL = 0;           // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // 启动计时
    
    // 等待计数到 0
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计时
}

void systick_delay_ms(uint16_t ms) {

    while (ms--) {
        systick_delay_us(1000);  // 延时 1ms
    }

}