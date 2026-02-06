#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "subsys_spi.h"






/**SPI2 GPIO Configuration
PA4     ------> CS
PA5     ------> SPI2_SCK
PA6     ------> SPI2_MISO
PA7     ------> SPI2_MOSI
*/



void SPI2_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef  SPI_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);


    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_InitStruct.SPI_DataSize = 8;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit  = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode     = SPI_Mode_Master;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

    SPI_Init(SPI2, &SPI_InitStruct);
	SPI_Cmd(SPI2, ENABLE);
}

void SPI2_Write(void *p_tx_buffer,uint16_t size)
{
    uint8_t *tx_data = (uint8_t *)p_tx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI2, *tx_data++);
	    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
        (void)SPI_I2S_ReceiveData(SPI2);
    }

}

void SPI2_Read(void *p_rx_buffer, uint16_t size)
{
    uint8_t *rx_data = (uint8_t *)p_rx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI2, 0xFF); 
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
        *rx_data++ = SPI_I2S_ReceiveData(SPI2);
    }
}

void SPI2_Write_And_Read(void *p_tx_buffer, void *p_rx_buffer, uint16_t size)
{
    uint8_t *tx_data = (uint8_t *)p_tx_buffer;
    uint8_t *rx_data = (uint8_t *)p_rx_buffer;
    
    while (size--)
    {
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)==RESET);
        SPI_I2S_SendData(SPI2, *tx_data++);
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==RESET);
        *rx_data++ = SPI_I2S_ReceiveData(SPI2);
    }
}

void SPI2_CS_Select(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void SPI2_CS_Dselect(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

static spi_ops_t __spi2_ops = {
    "SPI2",
    SPI2_Init,  
    SPI2_Write,
    SPI2_Read,
    SPI2_Write_And_Read,
    SPI2_CS_Select,
    SPI2_CS_Dselect
};

void spi2_dev_register()
{
    spi_bus_register(&__spi2_ops);
}