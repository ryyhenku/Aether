#ifndef __SSC_ADAPTER_H__
#define __SSC_ADAPTER_H__
#include <stdio.h>
#define SLAVE_CORE_IS_ET1100 1
#if SLAVE_CORE_IS_ET1100
#include "ET1100.h"
#endif

extern void GPIO_ISR_Enable();
extern void GPIO_ISR_Disable();
extern void GPIO_LED_Set(uint8_t RunLed, uint8_t ErrLed);
uint16_t HW_Init(void);
void HW_Release(void);


#define ENABLE_ESC_INT() GPIO_ISR_Enable()
#define DISABLE_ESC_INT() GPIO_ISR_Disable()
#define HW_SetLed(RunLed, ErrLed) GPIO_LED_Set(RunLed, ErrLed)
#endif /*__SSC_ADAPTER_H__*/