#include "ssc_adapter.h"
#include "subsys_period_timer.h"



extern void ethercat_gpio_cfg(void (*pdi_isr)(void),void (*sync0_isr)(void),void(*sync1_isr)(void));

void __attribute__((weak)) ECAT_CheckTimer(void) {
    // printf("Default implementation\n");
}

void __attribute__((weak)) PDI_Isr()
{
    // printf("Default implementation\n");
}

void __attribute__((weak)) Sync0_Isr()
{
    // printf("Default implementation\n");
}

void __attribute__((weak)) Sync1_Isr()
{
    // printf("Default implementation\n");
}

void esc_easy_test(void) {
    uint32_t intMask;
    do
    {
        intMask = 0x93;
        HW_EscWriteDWord(intMask, 0x0204);
        intMask = 0;
        HW_EscRead(&intMask, 0x0204, sizeof(intMask));
    } while (intMask != 0x93);
    
    intMask = 0;
    HW_EscWriteDWord(intMask, 0x0204);
}

uint16_t HW_Init(void)
{
    int ret;
    et1100_init();
    period_timer_ops_t* timer2 = period_timer_ops_get_by_name("Timer2_Period");
    ret = period_timer_start(timer2,1000,ECAT_CheckTimer);

    esc_easy_test();  
    ethercat_gpio_cfg(PDI_Isr,Sync0_Isr,Sync1_Isr);


    return 0;
}
void HW_Release(void){

}