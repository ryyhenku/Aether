#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

void __entry_critical(void)
{
    __disable_irq();
}

void __exit_critical(void)
{
    __enable_irq();
}



void (*__pdi_isr)(void);
void (*__sync0_isr)(void);
void (*__sync1_isr)(void);

void EXTI0_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line0)!= RESET)
    {
        __pdi_isr();
        EXTI_ClearITPendingBit(EXTI_Line0); 
    }

}

void EXTI1_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line1)!= RESET)
    {
        __sync0_isr();
        EXTI_ClearITPendingBit(EXTI_Line1); 
    }

}

void EXTI2_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line2)!= RESET)
    {
        __sync1_isr();
        EXTI_ClearITPendingBit(EXTI_Line2); 
    }

}

void ethercat_gpio_cfg(void (*pdi_isr)(void),void (*sync0_isr)(void),void(*sync1_isr)(void))
{

    __pdi_isr = pdi_isr;
    __sync0_isr = sync0_isr;
    __sync1_isr = sync1_isr;

    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);


    uint16_t gpioc_bits = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
                          GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_13;
    uint16_t gpiod_bits = GPIO_Pin_11;
    uint16_t gpioa_bits_1 = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ;
    uint16_t gpioa_bits_2 =  GPIO_Pin_3 | GPIO_Pin_8;

    GPIO_SetBits(GPIOC,gpioc_bits);
    GPIO_SetBits(GPIOD,gpiod_bits);
    GPIO_SetBits(GPIOA,gpioc_bits);
    
    GPIO_InitStructure.GPIO_Pin =  gpioc_bits;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  gpiod_bits;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  gpioa_bits_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  gpioa_bits_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_SetBits(GPIOC,gpioc_bits);
    GPIO_SetBits(GPIOD,gpiod_bits);
    GPIO_SetBits(GPIOA,gpioc_bits);

    /* 中断PA0 */
    EXTI_ClearITPendingBit(EXTI_Line0);                         
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;                              
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                               
    EXTI_Init(&EXTI_InitStructure);                                                  
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);     

    /* 中断PA1 */
    EXTI_ClearITPendingBit(EXTI_Line1);                         
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;                              
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                               
    EXTI_Init(&EXTI_InitStructure);    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);     
    /* 中断PA2 */

    EXTI_ClearITPendingBit(EXTI_Line2);                         
    EXTI_InitStructure.EXTI_Line=EXTI_Line2;                              
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                               
    EXTI_Init(&EXTI_InitStructure);    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);  

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;                        
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;        
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               
    NVIC_Init(&NVIC_InitStructure);                                                           
        
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;                    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;      
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                
    NVIC_Init(&NVIC_InitStructure);                                                            
        
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                        
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;        
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                       
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               
    NVIC_Init(&NVIC_InitStructure);

    NVIC_DisableIRQ(EXTI0_IRQn);
    NVIC_DisableIRQ(EXTI1_IRQn);
    NVIC_DisableIRQ(EXTI2_IRQn);

}

void GPIO_ISR_Enable()
{
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI2_IRQn);
}

void GPIO_ISR_Disable()
{
    NVIC_DisableIRQ(EXTI0_IRQn);
    NVIC_DisableIRQ(EXTI1_IRQn);
    NVIC_DisableIRQ(EXTI2_IRQn);
}

void GPIO_LED_Set(uint8_t RunLed, uint8_t ErrLed)
{
    RunLed ? GPIO_ResetBits(GPIOC, GPIO_Pin_13):
              GPIO_SetBits(GPIOC, GPIO_Pin_13);
    ErrLed ? GPIO_ResetBits(GPIOD, GPIO_Pin_10):
              GPIO_SetBits(GPIOD, GPIO_Pin_10);
}