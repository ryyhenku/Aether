#ifndef __SUBSYS_PWM_H__
#define __SUBSYS_PWM_H__

#include <stdio.h>
typedef void (*period_timer_callback_function_t)(void);
typedef struct
{
    char *pwm_name;
    int (*pwm_init)(uint32_t freq,period_timer_callback_function_t pfn);
    int (*pwm_start)(uint8_t channel);
    int (*pwm_set_duty)(uint8_t channel,uint32_t duty);
    int (*pwm_stop)(uint8_t channel);
}pwm_ops_t;

void pwm_dev_register(pwm_ops_t* ops);
pwm_ops_t* pwm_ops_get_by_name(char *name);





#endif /* __SUBSYS_PWM_H__ */