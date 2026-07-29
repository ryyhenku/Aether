#include "delay.h"
static pfn_delay_ms_t __pfn_ms;
static pfn_delay_us_t __pfn_us;

int init_block_delay(pfn_init init,pfn_delay_ms_t pfn_ms,pfn_delay_us_t pfn_us)
{

    if (pfn_ms ==NULL || pfn_us==NULL || init==NULL) {
        return -1;
    }
    init();
    __pfn_ms = pfn_ms;
    __pfn_us = pfn_us;
}
int init_nonblock_delay(pfn_init init,pfn_delay_ms_t pfn_ms,pfn_delay_us_t pfn_us) 
{
    if (pfn_ms ==NULL || pfn_us==NULL || init==NULL) {
        return -1;
    }
    init();
    __pfn_ms = pfn_ms;
    __pfn_us = pfn_us;
}

void delay_ms(uint16_t ms)
{
    if(__pfn_ms) {
        __pfn_ms(ms);
    }

}
void delay_us(uint32_t us)
{
      if(__pfn_us) {
        __pfn_ms(us);
    }
  
}