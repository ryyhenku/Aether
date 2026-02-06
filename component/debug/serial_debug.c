#include "serial_debug.h"
#include <stdio.h>


static uart_ops_t* __debug_serial = NULL;

int init_debug_serial(
    char * debug_serial_name,
    uint32_t baudrate,
    Data_Bits_t data_bits,
    Stop_Bits_t stop_bits,
    Parity_t parity)
{

    //目前暂只支持一路调试串口
    if(__debug_serial != NULL) {
        return -1;
    }

    __debug_serial = uart_ops_get_by_name(debug_serial_name);
    if(__debug_serial == NULL) {
        return -1;
    }

    __debug_serial->pfn_uart_init(baudrate,data_bits,stop_bits,parity);


    __debug_serial->pfn_uart_write("[Debug]Application Start!\r\n",27);
    return 0;       
}

int _write(int file, char *ptr, int len)
{
    /* 发送一个字节数据到串口 */
    if (__debug_serial != NULL) {
        __debug_serial->pfn_uart_write(ptr,len);
        return (len);
    }
}
