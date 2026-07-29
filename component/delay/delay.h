#ifndef __DELAY_H__
#define __DELAY_H__

#include "stdio.h"
typedef void (*pfn_init)(void);
typedef void(*pfn_delay_ms_t)(uint16_t ms);
typedef void(*pfn_delay_us_t)(uint32_t us);
int init_block_delay(pfn_init init,pfn_delay_ms_t pfn_ms,pfn_delay_us_t pfn_us);
int init_nonblock_delay(pfn_init init,pfn_delay_ms_t pfn_ms,pfn_delay_us_t pfn_us);

void delay_ms(uint16_t ms);
void delay_us(uint32_t us);

#endif /*__DELAY_H__*/
