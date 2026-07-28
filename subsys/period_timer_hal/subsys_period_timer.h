#ifndef __SUBSYS_PERIOD_TIMER_H__
#define __SUBSYS_PERIOD_TIMER_H__

#include <stdio.h>

typedef void (*period_timer_callback_function_t)(void);

typedef struct
{
    char *period_timer_name;
    int (*period_timer_start)(uint32_t period_us,period_timer_callback_function_t func);
    int (*period_timer_stop)();
}period_timer_ops_t;

void period_timer_dev_register(period_timer_ops_t* ops);
period_timer_ops_t* period_timer_ops_get_by_name(char *name);
int period_timer_start(period_timer_ops_t *timer_dev ,uint32_t period_us,period_timer_callback_function_t func);
int period_timer_stop(period_timer_ops_t *timer_dev);

#endif /* __SUBSYS_PERIOD_TIMER_H__ */