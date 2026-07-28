#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "subsys_gpio.h"

static GPIO_TypeDef* __port_table[] = {
    GPIOA, GPIOB, GPIOC, GPIOD, GPIOE,
    GPIOF, GPIOG, GPIOH, GPIOI
};

static uint16_t __pin_table[] = {
    GPIO_Pin_0,  GPIO_Pin_1,  GPIO_Pin_2,  GPIO_Pin_3,
    GPIO_Pin_4,  GPIO_Pin_5,  GPIO_Pin_6,  GPIO_Pin_7,
    GPIO_Pin_8,  GPIO_Pin_9,  GPIO_Pin_10, GPIO_Pin_11,
    GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15
};

int __stm32f407_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* pwm1 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        // 复用模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  // 高速
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        // 上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);


    /* 电机下桥臂 & 预驱芯片 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_Init(GPIOB ,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_13);
    GPIO_ResetBits(GPIOB, GPIO_Pin_14);
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_Init(GPIOF ,&GPIO_InitStructure);

    /* hall */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    GPIO_Init(GPIOH ,&GPIO_InitStructure);


    /*usart1*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
    GPIO_Init(GPIOB ,&GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);  
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 


    /* led */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     
    GPIO_Init(GPIOE ,&GPIO_InitStructure);
    GPIO_SetBits(GPIOE, GPIO_Pin_0);
    GPIO_SetBits(GPIOE, GPIO_Pin_1);




    return 0;
}

int __stm32f407_gpio_write(uint8_t port, uint8_t pin, gpio_pin_state_t state)
{
    if (port >= sizeof(__port_table) / sizeof(__port_table[0])) {
        return -1;
    }
    if (pin >= sizeof(__pin_table) / sizeof(__pin_table[0])) {
        return -1;
    }

    if (state == GPIO_PIN_HIGH) {
        GPIO_SetBits(__port_table[port], __pin_table[pin]);
    } else {
        GPIO_ResetBits(__port_table[port], __pin_table[pin]);
    }

    return 0;
}

gpio_pin_state_t __stm32f407_gpio_read(uint8_t port, uint8_t pin)
{
    if (port >= sizeof(__port_table) / sizeof(__port_table[0])) {
        return GPIO_PIN_LOW;
    }
    if (pin >= sizeof(__pin_table) / sizeof(__pin_table[0])) {
        return GPIO_PIN_LOW;
    }

    uint8_t val = GPIO_ReadInputDataBit(__port_table[port], __pin_table[pin]);
    return (val == Bit_SET) ? GPIO_PIN_HIGH : GPIO_PIN_LOW;
}

int __stm32f407_gpio_toggle(uint8_t port, uint8_t pin)
{
    if (port >= sizeof(__port_table) / sizeof(__port_table[0])) {
        return -1;
    }
    if (pin >= sizeof(__pin_table) / sizeof(__pin_table[0])) {
        return -1;
    }

    GPIO_ToggleBits(__port_table[port], __pin_table[pin]);

    return 0;
}

static gpio_ops_t __stm32f407_gpio_ops = {
    "STM32F407_GPIO",
    __stm32f407_gpio_init,
    __stm32f407_gpio_write,
    __stm32f407_gpio_read,
    __stm32f407_gpio_toggle,
};

void st_gpio_dev_register()
{
    gpio_dev_register(&__stm32f407_gpio_ops);
}
