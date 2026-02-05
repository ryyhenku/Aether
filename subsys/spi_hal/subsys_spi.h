#ifndef __SUBSYS_SPI_H__
#define __SUBSYS_SPI_H__

#include "stdio.h"

/* 每个平台需要实现这个结构 */
typedef struct
{
    char *spi_bus_name;
    void (*pfn_spi_init)(void);
    void (*pfn_spi_write)(void *p_tx_buffer, uint16_t size);
    void (*pfn_spi_read)(void *p_rx_buffer, uint16_t size);
    void (*pfn_spi_write_and_read)(void *p_tx_buffer, void *p_rx_buffer, uint16_t size);
    void (*pfn_spi_cs_select)(void);    
    void (*pfn_spi_cs_deselect)(void);  
}spi_ops_t;
void spi_bus_register(spi_ops_t *spi_bus);
spi_ops_t* spi_bus_ops_get_by_name(char *name);
void spi_bus_init(spi_ops_t *spi_bus);
void spi_bus_write(spi_ops_t *spi_bus,void *tx_buffer,uint16_t size);
void spi_bus_read(spi_ops_t *spi_bus,void *rx_buffer,uint16_t size);
void spi_bus_write_and_read(spi_ops_t *spi_bus,void *tx_buffer,void *rx_buffer,uint16_t size);
void spi_bus_cs_select(spi_ops_t *spi_bus);
void spi_bus_cs_deselect(spi_ops_t *spi_bus);
#endif /* __SUBSYS_SPI_H__*/