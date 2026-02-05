#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "subsys_spi.h"






/**SPI1 GPIO Configuration
PA4     ------> CS
PA5     ------> SPI1_SCK
PA6     ------> SPI1_MISO
PA7     ------> SPI1_MOSI
*/



void SPI1_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef  SPI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);  

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);


    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_InitStruct.SPI_DataSize = 8;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit  = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode     = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

    SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
}

void SPI1_Write(void *p_tx_buffer,uint16_t size)
{
    uint8_t *tx_data = (uint8_t *)p_tx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI1, *tx_data++);
	    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
        (void)SPI_I2S_ReceiveData(SPI1);
    }

}

void SPI1_Read(void *p_rx_buffer, uint16_t size)
{
    uint8_t *rx_data = (uint8_t *)p_rx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI1, 0xFF); 
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
        *rx_data++ = SPI_I2S_ReceiveData(SPI1);
    }
}

void SPI1_Write_And_Read(void *p_tx_buffer, void *p_rx_buffer, uint16_t size)
{
    uint8_t *tx_data = (uint8_t *)p_tx_buffer;
    uint8_t *rx_data = (uint8_t *)p_rx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI1, *tx_data++);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==RESET);
        *rx_data++ = SPI_I2S_ReceiveData(SPI1);
    }
}

void spi1_cs_select(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void spi1_cs_deselect(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
}

static spi_ops_t __spi1_ops = {
    "SPI1",
    SPI1_Init,  
    SPI1_Write,
    SPI1_Read,
    SPI1_Write_And_Read,
    spi1_cs_select,
    spi1_cs_deselect
};

void spi1_dev_register()
{
    spi_bus_register(&__spi1_ops);
}