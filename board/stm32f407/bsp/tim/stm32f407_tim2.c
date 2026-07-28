#include "subsys_period_timer.h"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"


static void (*__timeout_func)(void);

void TIM2_IRQHandler()
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
         __timeout_func();
    }
}

int period_timer2_start(uint32_t period_us,period_timer_callback_function_t func)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    __timeout_func = func;

    TIM_TimeBaseStructure.TIM_Period = period_us - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);         

}

int period_timer2_stop()
{
    TIM_Cmd(TIM2, DISABLE);   
}

period_timer_ops_t __timer2_ops = {
    .period_timer_name = "Timer2_Period",
    .period_timer_start = period_timer2_start,
    .period_timer_stop = period_timer2_stop
};

void st_tim2_period_dev_register()
{
    period_timer_dev_register(&__timer2_ops);
}