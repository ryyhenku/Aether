#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "subsys_uart.h"

int init_debug_serial(char * debug_serial_name,uint32_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity);


#endif /*__DEBUG_H__*/
