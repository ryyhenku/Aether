#include "subsys_spi.h"

static spi_ops_t* __spi_buses[8];
static uint8_t __spi_bus_count = 0;

spi_ops_t* spi_bus_ops_get_by_name(char *name)
{
    for(int i = 0; i < 8; i++) {
        if(__spi_buses[i] != NULL) {
            if(strcmp(name,__spi_buses[i]->spi_bus_name) == 0) {
                return __spi_buses[i];
            }
        }
    }

    return NULL;
}

void spi_bus_register(spi_ops_t *spi_bus)
{
    if (__spi_bus_count < 8) {
        __spi_buses[__spi_bus_count] = spi_bus;
        __spi_bus_count = __spi_bus_count ++;
    }

}

void spi_bus_init(spi_ops_t *spi_bus)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_init();
}

void spi_bus_write(spi_ops_t *spi_bus,void *tx_buffer,uint16_t size)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_write(tx_buffer, size);
}

void spi_bus_read(spi_ops_t *spi_bus,void *rx_buffer,uint16_t size)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_read(rx_buffer, size);
}

void spi_bus_write_and_read(spi_ops_t *spi_bus,void *tx_buffer,void *rx_buffer,uint16_t size)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_write_and_read(tx_buffer,rx_buffer, size);
}

void spi_bus_cs_select(spi_ops_t *spi_bus)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_cs_select();
}

void spi_bus_cs_deselect(spi_ops_t *spi_bus)
{
    if(spi_bus == NULL)
        return;
    spi_bus->pfn_spi_cs_deselect();
}
