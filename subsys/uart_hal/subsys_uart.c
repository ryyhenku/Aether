#include <subsys_uart.h>

static uart_ops_t* __uart_devs[8];
static uint8_t __uart_dev_count = 0;


void uart_dev_register(uart_ops_t *ops)
{
        if (__uart_dev_count< 8) {
        __uart_devs[__uart_dev_count] = ops;
        __uart_dev_count = __uart_dev_count ++;
    }
}
uart_ops_t* uart_ops_get_by_name(char *name)
{
    for(int i = 0; i < 8; i++) {
        if(__uart_devs[i] != NULL) {
            if(strcmp(name,__uart_devs[i]->uart_name) == 0) {
                return __uart_devs[i];
            }
        }
    }

    return NULL;

}
void uart_dev_init(uart_ops_t *uart_dev,uint16_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity)
{
    if(uart_dev != NULL) {
        uart_dev->pfn_uart_init( baudrate, data_bits, stop_bits, parity);
    }

}
uint16_t uart_dev_write(uart_ops_t *uart_dev,void *tx_buffer,uint16_t size)
{
    if(uart_dev != NULL) {
       return uart_dev->pfn_uart_write( tx_buffer, size);
    }
    return 0;
}
uint16_t uart_dev_read(uart_ops_t *uart_dev,void *rx_buffer,uint16_t size)
{
    if(uart_dev != NULL) {
         return uart_dev->pfn_uart_read(rx_buffer, size);
    }
    return 0;
}

