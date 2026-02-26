#include "et1100.h"
#include "subsys_spi.h"

extern void __entry_critical(void);
extern void __exit_critical(void);

typedef union
{
    uint8_t  byte[2];
    uint16_t word;
}alevent;

static spi_ops_t *__g_spi_ops = NULL;

#define ET1100_CMD_NOP                                   0X0
#define ET1100_CMD_READ                                  0X2 
#define ET1100_CMD_READ_WITH_FOLLOWING_WAIT_STATE_BYTES  0X3 
#define ET1100_CMD_WRITE                                 0X4 
#define ET1100_CMD_ADDRESS_EXTENSION                     0X6

static void et1100_cmd(uint16_t address,uint16_t command)
{
    uint8_t tx_cmd[4] = {0,0,0,0};
    uint8_t tx_len = 0;

    //命令的第一个字节总是 {address[12:5]}
    tx_cmd[0] = address >> 5;
    tx_len ++;
    //第二个字节的值取决于是2Byte Mode还是3Byte Mode

    //3Byte Mode
    if(address > 0x1fff) {
        //tx_cmd[1] = {address[4:0] 0b'110}
        tx_cmd[1] = (address << 3) | 0x06;
        //tx_cmd[1] = {address[15:13] command[2:0] 0x00 0x00}
        tx_cmd[2] = ((address >> 8) & 0x0e) | (command << 2);
        tx_len += 2;
    } else {
        //tx_cmd[1] = {address[4:0] command[2:0]}
        tx_cmd[1] = (address << 3) | command;
        tx_len ++;
    }

    if (command == ET1100_CMD_READ_WITH_FOLLOWING_WAIT_STATE_BYTES)
    {
        tx_cmd[tx_len] = 0Xff;
        tx_len ++;
    }
    __g_spi_ops->pfn_spi_write(tx_cmd,tx_len);
}

void et1100_read_isr(void *pData, uint16_t Address, uint16_t Len)
{
    uint8_t tx_data = 0x00;
    __entry_critical();
    __g_spi_ops->pfn_spi_cs_select();
    et1100_cmd(Address,ET1100_CMD_READ_WITH_FOLLOWING_WAIT_STATE_BYTES);
    while(Len > 1) {
        __g_spi_ops->pfn_spi_write_and_read(&tx_data,pData,1);
        pData = (uint8_t*)pData + 1;
        Len --;
    }
    tx_data = 0xff;
    __g_spi_ops->pfn_spi_write_and_read(&tx_data,pData,1);
    __g_spi_ops->pfn_spi_cs_deselect();
    __exit_critical();
}

void et1100_read(void *pData, uint16_t Address, uint16_t Len)
{
    uint8_t tx_data = 0xff;
    __entry_critical();
    while(Len) {

        __g_spi_ops->pfn_spi_cs_select();
        et1100_cmd(Address,ET1100_CMD_READ_WITH_FOLLOWING_WAIT_STATE_BYTES);
        __g_spi_ops->pfn_spi_write_and_read(&tx_data,pData,1);
        __g_spi_ops->pfn_spi_cs_deselect();

        pData = (uint8_t*)pData + 1;
        Address ++;
        Len --;
    }
    __exit_critical();
}

void et1100_write_isr(void *pData, uint16_t Address, uint16_t Len)
{
    __entry_critical();
    __g_spi_ops->pfn_spi_cs_select();
    et1100_cmd(Address,ET1100_CMD_WRITE);
    __g_spi_ops->pfn_spi_write(pData,Len);
    __g_spi_ops->pfn_spi_cs_deselect();
    __exit_critical();

}

void et1100_write(void *pData, uint16_t Address, uint16_t Len)
{
    __entry_critical();
    while(Len) {
        __g_spi_ops->pfn_spi_cs_select();
        et1100_cmd(Address,ET1100_CMD_WRITE);
        __g_spi_ops->pfn_spi_write(pData,1);
        __g_spi_ops->pfn_spi_cs_deselect();
        pData = (uint8_t*)pData + 1;
        Address ++;
        Len --;
    }
    __exit_critical();
}

uint16_t et1100_get_alevent_reg(void)
{
    alevent esc_alevent_reg;
    et1100_read((void*)(&(esc_alevent_reg.word)),
                        0X220,
                        sizeof(alevent));
    return esc_alevent_reg.word;
}

int et1100_init()
{

    /*spi初始化*/
    __g_spi_ops = spi_bus_ops_get_by_name("SPI1");
    if(__g_spi_ops == NULL) {
        return -1;
    }
    __g_spi_ops->pfn_spi_init();

    return 0;
}




