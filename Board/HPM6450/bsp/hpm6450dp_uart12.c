#include "hpm_uart_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_soc.h"
#include "subsys_uart.h"
void Uart12_Init(uint32_t baudrate,Data_Bits_t data_bits,Stop_Bits_t stop_bits,Parity_t parity)
{
    uart_config_t config = {0};
    HPM_IOC->PAD[IOC_PAD_PA26].FUNC_CTL = IOC_PA26_FUNC_CTL_UART12_RXD;
    HPM_IOC->PAD[IOC_PAD_PA27].FUNC_CTL = IOC_PA27_FUNC_CTL_UART12_TXD;
    /* PY port IO needs to configure PIOC as well */
    clock_add_to_group(clock_uart12, 0);

    uart_default_config(HPM_UART12, &config);
    config.baudrate = baudrate;
    config.num_of_stop_bits = stop_bits;
    config.word_length = data_bits;
    config.parity = parity;
    config.fifo_enable = false;
    config.src_freq_in_hz = clock_get_frequency(clock_uart12);
    uart_init(HPM_UART12, &config);
}
uint16_t Uart12_Write(void *p_tx_buffer, uint16_t size)
{
    uint8_t* p_tx_buf = (uint8_t*)p_tx_buffer;
    uint16_t i ;
    for(i = 0;i < size;i++) {
        uart_send_byte(HPM_UART12,p_tx_buf[i]);
    }

    return i;
}

uint16_t Uart12_Read(void *p_rx_buffer, uint16_t size)
{
    return 0;
}

static uart_ops_t __uart12_ops = {
    "Uart12",
    Uart12_Init,
    Uart12_Write,
    Uart12_Read,
};

void uart12_dev_register()
{
    uart_dev_register(&__uart12_ops);
}