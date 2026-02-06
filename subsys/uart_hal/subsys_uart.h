#ifndef __SUBSYS_UART_H__
#define __SUBSYS_UART_H__
#include "stdio.h"

typedef enum
{
    Data_Bits_5 = 0,
    Data_Bits_6,
    Data_Bits_7,
    Data_Bits_8
}Data_Bits_t;

typedef enum
{
    Stop_Bits_1 = 0,
    Stop_Bits_1_5,
    Stop_Bits_2
}Stop_Bits_t;

typedef enum
{
    None_Parity = 0,
    Odd_Parity,
    Even_Parity,
    Space_Parity
}Parity_t;


typedef struct
{
    char *uart_name;
    void (*pfn_uart_init)(uint32_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity);
    uint16_t (*pfn_uart_write)(void *p_tx_buffer, uint16_t size);
    uint16_t (*pfn_uart_read)(void *p_rx_buffer, uint16_t size);
}uart_ops_t;

void uart_dev_register(uart_ops_t *ops);
uart_ops_t* uart_ops_get_by_name(char *name);
void uart_dev_init(uart_ops_t *uart_dev,uint16_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity);
uint16_t uart_dev_write(uart_ops_t *uart_dev,void *tx_buffer,uint16_t size);
uint16_t uart_dev_read(uart_ops_t *uart_dev,void *rx_buffer,uint16_t size);


#endif /* __SUBSYS_UART_H__ */