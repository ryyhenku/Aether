#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "subsys_uart.h"

void Uart1_Init(uint32_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity)
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    
    USART_Init(USART1, &USART_InitStructure);
    
    USART_Cmd(USART1, ENABLE);
}

uint16_t Uart1_Write(void *p_tx_buffer, uint16_t size)
{
    uint8_t* p_tx_buf = (uint8_t*)p_tx_buffer;
    uint16_t i ;
    for(i = 0;i < size;i++) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, p_tx_buf[i]); // 写入数据到发送寄存器
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);

    }

    return i;
}

uint16_t Uart1_Read(void *p_rx_buffer, uint16_t size)
{
    return 0;
}

static uart_ops_t __uart1_ops = {
    "Debug_UART",
    Uart1_Init,
    Uart1_Write,
    Uart1_Read,
};

void st_uart1_dev_register()
{
    uart_dev_register(&__uart1_ops);
}