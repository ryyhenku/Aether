#include "serial_debug.h"
#include <stdio.h>
#include "ssc_adapter.h"
#include "applInterface.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "8IO.h"
void SysTick_Delay_Init(void) {
    // SysTick 使用系统时钟（假设 72MHz）
    // 不启用中断，只用于查询计数
    SysTick->CTRL = 0;            // 先禁用
    SysTick->LOAD = 0xFFFFFF;     // 24位最大值
    SysTick->VAL = 0;             // 清空当前值
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;  // 选择系统时钟，不使能中断
}

void Delay_us(uint32_t us) {
    // 1us 需要计数的次数 = 时钟频率(MHz) = 72 次
    uint32_t ticks = us * 72;  // 72MHz 时
    
    SysTick->LOAD = ticks;      // 设置重装值
    SysTick->VAL = 0;           // 清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // 启动计时
    
    // 等待计数到 0
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
    
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计时
}

void Delay_ms(uint32_t ms) {

    while (ms--) {
        Delay_us(1000);  // 延时 1ms
    }

}


int main()
{
    int ret;
    board_init();
    ret = init_debug_serial("Debug_UART",115200,Data_Bits_8,Stop_Bits_1,None_Parity);
    if (ret != 0) {
        return ret;
    }

    HW_Init();

	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	Delay_ms(200);
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
	Delay_ms(200);

	MainInit();
	bRunApplication = 1;
	/***************************** ECAT Init  END******************************/
	
	/***************************** User Application Init BEGIN******************************/
	
	/***************************** User Application Init END*******************************/
	
			
	/*此LOOP中的代码,执行时不应该存在阻塞的行为，应该尽可能快的执行；
	  如果该LOOP中的 User Application Loop 部分代码过于耗时，可能会影响到EtherCAT的正常通信(尤其是在DC或SM模式下)*/
		
	do{
		/***************************** User Application Loop BEGIN******************************/
		
    PDOChannel0x7000.LED1 ? GPIO_ResetBits(GPIOC,GPIO_Pin_0):GPIO_SetBits (GPIOC, GPIO_Pin_0); //LED1
    PDOChannel0x7000.LED2 ? GPIO_ResetBits(GPIOC, GPIO_Pin_1):GPIO_SetBits(GPIOC, GPIO_Pin_1); //LED2
    PDOChannel0x7000.LED3 ? GPIO_ResetBits(GPIOC, GPIO_Pin_2):GPIO_SetBits(GPIOC, GPIO_Pin_2); //LED3
    PDOChannel0x7000.LED4 ? GPIO_ResetBits(GPIOC, GPIO_Pin_3):GPIO_SetBits(GPIOC, GPIO_Pin_3); //LED4
    PDOChannel0x7000.LED5 ? GPIO_ResetBits(GPIOC, GPIO_Pin_4):GPIO_SetBits(GPIOC, GPIO_Pin_4); //LED5
    PDOChannel0x7000.LED6 ? GPIO_ResetBits(GPIOC, GPIO_Pin_5):GPIO_SetBits(GPIOC, GPIO_Pin_5); //LED6
    PDOChannel0x7000.LED7 ? GPIO_ResetBits(GPIOC, GPIO_Pin_6):GPIO_SetBits(GPIOC, GPIO_Pin_6); //LED7
    PDOChannel0x7000.LED8 ? GPIO_ResetBits(GPIOC, GPIO_Pin_7):GPIO_SetBits(GPIOC, GPIO_Pin_7); //LED8
		
		/************************** *** User Application Loop END*******************************/
		MainLoop();
	}while(bRunApplication == 1);

    while(1);

}
