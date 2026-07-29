#include "subsys_uart.h"
#include "subsys_pwm.h"
#include "subsys_period_timer.h"
#include "subsys_gpio.h"

#include "serial_debug.h"
#include <stdio.h>
pwm_ops_t* pwm_dev;
gpio_ops_t * gpio_dev;
typedef void(*pctr) (void);
#define dir 1  //0  顺时针转  1逆时针转
uint32_t test_duty = 500;
static uint32_t cnt;
static uint8_t speed_raise = 1;
static test_for_hall()
{
    /* 霍尔传感器测试 */
    uint8_t hall_u = gpio_dev->gpio_read(PortGPIOH,10);
    uint8_t hall_v = gpio_dev->gpio_read(PortGPIOH,11);
    uint8_t hall_w = gpio_dev->gpio_read(PortGPIOH,12);
    printf("u:%d  v:%d  w:%d\r\n",hall_u,hall_v,hall_w);
}

static test_for_uvw_l_and_drv()
{
    /* 下桥测试 */
    gpio_dev->gpio_toggle(PortGPIOB,13);
    gpio_dev->gpio_toggle(PortGPIOB,14);
    gpio_dev->gpio_toggle(PortGPIOB,15);

    /* 预驱测试 */
    gpio_dev->gpio_toggle(PortGPIOF,10);
}

static test_for_uvw_h()
{
    /* 上桥臂测试 */
    pwm_dev->pwm_set_duty(1,1000);
    pwm_dev->pwm_set_duty(2,1000);
    pwm_dev->pwm_set_duty(3,1000);
}

static void __whul()
{
    pwm_dev->pwm_set_duty(1,0);
    pwm_dev->pwm_set_duty(2,0);
    pwm_dev->pwm_set_duty(3,test_duty); //w上输出pwm

    gpio_dev->gpio_write(PortGPIOB,13,1); //u下高电平
    gpio_dev->gpio_write(PortGPIOB,14,0);
    gpio_dev->gpio_write(PortGPIOB,15,0);
}

static void __vhul()
{
    pwm_dev->pwm_set_duty(1,0);
    pwm_dev->pwm_set_duty(2,test_duty);   //v上输出pwm
    pwm_dev->pwm_set_duty(3,0);

    gpio_dev->gpio_write(PortGPIOB,13,1); //u下高电平
    gpio_dev->gpio_write(PortGPIOB,14,0);
    gpio_dev->gpio_write(PortGPIOB,15,0);
}

static void __vhwl()
{
    pwm_dev->pwm_set_duty(1,0);   
    pwm_dev->pwm_set_duty(2,test_duty); //v上输出pwm
    pwm_dev->pwm_set_duty(3,0);

    gpio_dev->gpio_write(PortGPIOB,13,0);
    gpio_dev->gpio_write(PortGPIOB,14,0);
    gpio_dev->gpio_write(PortGPIOB,15,1);//w下高电平
}

static void __uhwl()
{
    pwm_dev->pwm_set_duty(1,test_duty); //u上输出pwm
    pwm_dev->pwm_set_duty(2,0);
    pwm_dev->pwm_set_duty(3,0);

    gpio_dev->gpio_write(PortGPIOB,13,0);
    gpio_dev->gpio_write(PortGPIOB,14,0);
    gpio_dev->gpio_write(PortGPIOB,15,1); //w下高电平
}

static void __uhvl()
{
    pwm_dev->pwm_set_duty(1,test_duty);  //u上输出pwm
    pwm_dev->pwm_set_duty(2,0);
    pwm_dev->pwm_set_duty(3,0);

    gpio_dev->gpio_write(PortGPIOB,13,0);
    gpio_dev->gpio_write(PortGPIOB,14,1);//v下高电平
    gpio_dev->gpio_write(PortGPIOB,15,0);
}

static void __whvl()
{
    pwm_dev->pwm_set_duty(1,0);
    pwm_dev->pwm_set_duty(2,0);
    pwm_dev->pwm_set_duty(3,test_duty); //w上输出pwm

    gpio_dev->gpio_write(PortGPIOB,13,0);
    gpio_dev->gpio_write(PortGPIOB,14,1);//v下高电平
    gpio_dev->gpio_write(PortGPIOB,15,0);
}
pctr pfunclist_m1[6] =
{
    &__uhwl, &__vhul, &__vhwl,
    &__whvl, &__uhvl, &__whul
};
void call_back()
{
    /*halla  hallb  hall c*/

    cnt += 1;
    uint16_t hall_state;
    uint8_t hall_u = gpio_dev->gpio_read(PortGPIOH,10);
    uint8_t hall_v = gpio_dev->gpio_read(PortGPIOH,11);
    uint8_t hall_w = gpio_dev->gpio_read(PortGPIOH,12);

    hall_state = (hall_u) | (hall_v << 1) | (hall_w << 2);

    if(cnt>=50000) {
        cnt = 0;

        if (test_duty == 500) {
            speed_raise = 1;
        } else if (test_duty == 7000) {
            speed_raise = 0;
        }

        if (speed_raise) {
            test_duty += 500;
        } else {
            test_duty -=500;
        }


        

         //printf("cnt:%d\r\n",hall_state);
    }

    /* 顺序6,2,3,1,5,4 */  

    if(dir == 0) {
        pfunclist_m1[hall_state - 1]();
    } else { //顺序 4 5 1 3 2 6
        pfunclist_m1[hall_state = 7 - hall_state - 1]();  //反转
    }
    
}

int main()
{
    int ret;
    board_init();

    pwm_dev = pwm_ops_get_by_name("TIM1_PWM");
    period_timer_ops_t* timer2 = period_timer_ops_get_by_name("Timer2_Period");
    /*end dev init*/

    gpio_dev = gpio_ops_get_by_name("GPIO");

    /* 初始化PWM */
    pwm_dev->pwm_init(16800,call_back);
    pwm_dev->pwm_start(1);
    pwm_dev->pwm_start(2);
    pwm_dev->pwm_start(3);

    /*LED*/
    gpio_dev->gpio_write(PortGPIOE,0,GPIO_PIN_LOW);
    gpio_dev->gpio_write(PortGPIOE,1,GPIO_PIN_LOW);
    gpio_dev->gpio_write(PortGPIOF,10,1);


    while(1){
        float duty = (float)test_duty/10000 * 100;
        printf("curren duty:%f %% \r\n",duty);
        delay_ms(1000);
    }
}

