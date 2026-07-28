#include "subsys_pwm.h"


static pwm_ops_t* pwm_devs[8];
uint32_t pwm_count = 0;


void pwm_dev_register(pwm_ops_t* ops)
{

    if (pwm_count< 8) {
        pwm_devs[pwm_count] = ops;
        pwm_count = pwm_count ++;
    }

}

pwm_ops_t* pwm_ops_get_by_name(char *name)
{
    for(int i = 0; i < 8; i++) {
        if(pwm_devs[i] != NULL) {
            if(strcmp(name,pwm_devs[i]->pwm_name) == 0) {
                return pwm_devs[i];
            }
        }
    }

    return NULL;
}