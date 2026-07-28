#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "subsys_pwm.h"


static void (*__tim_update_func)(void);


void TIM1_UP_TIM10_IRQHandler()
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        __tim_update_func();
    }
}

int _pwm1_init(uint32_t freq,period_timer_callback_function_t pfn)
{

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    __tim_update_func = pfn; 

    TIM_TimeBaseStruct.TIM_Prescaler = 0;      // 预分频系数 PSC
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数模式
    TIM_TimeBaseStruct.TIM_Period = 10000 - 1;        // 自动重装载值 ARR   16.8Khz
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;    // 重复计数器，高级定时器特有，一般设为0
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;   // PWM 模式 1
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 使能输出
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable; // 互补输出，不用则禁用
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;  // 输出极性为高电平有效
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High; // 互补极性，不用管
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;  // 空闲状态
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM1, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  // 使能预装载

    TIM_OC2Init(TIM1, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM1, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM1, ENABLE);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM1, ENABLE);
}


int __pwm1_start(uint8_t channel) 
{

    switch(channel) {
        case 1:
            TIM1->CCER |= TIM_CCER_CC1E;   // 使能通道1输出
            break;
        case 2:
            TIM1->CCER |= TIM_CCER_CC2E;   // 使能通道2输出
            break;
        case 3:
            TIM1->CCER |= TIM_CCER_CC3E;   // 使能通道3输出
            break;
        default:
            break;
    }

}

int __pwm1_stop(uint8_t channel) 
{
    switch(channel) {
        case 1:
            TIM1->CCER &= ~TIM_CCER_CC1E;  // 关闭通道1输出
            break;
        case 2:
            TIM1->CCER &= ~TIM_CCER_CC2E;  // 关闭通道2输出
            break;
        case 3:
            TIM1->CCER &= ~TIM_CCER_CC3E;  // 关闭通道3输出
            break;
        default:
            break;
    }
}

void __pwm1_setduty(uint8_t channel, uint16_t duty)
{
    // 限制占空比范围
    if(duty > 10000) duty = 10000;
    
    switch(channel)  {
        case 1:
            TIM1->CCR1 = duty;
            break;
        case 2:
            TIM1->CCR2 = duty;
            break;
        case 3:
            TIM1->CCR3 = duty;
            break;
        default:
            break;
    }
}


static pwm_ops_t __tim1pwm_ops = {
    "TIM1_PWM",
    _pwm1_init,
    __pwm1_start,
    __pwm1_setduty,
    __pwm1_stop,
};

void st_tim1pwm_dev_register()
{
    pwm_dev_register(&__tim1pwm_ops);
}