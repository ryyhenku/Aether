#include "subsys_uart.h"
#include "subsys_pwm.h"
#include "subsys_period_timer.h"
#include "subsys_gpio.h"
#include "subsys_clk.h"
#include "serial_debug.h"
#include <stdio.h>
pwm_ops_t* pwm_dev;
gpio_ops_t * gpio_dev;

#define dir 1  //0  顺时针转  1逆时针转
#define test_speed 500
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



void call_back()
{
    /*halla  hallb  hall c*/
    static uint32_t cnt;
    cnt += 1;
    uint16_t hall_state;
    uint8_t hall_u = gpio_dev->gpio_read(PortGPIOH,10);
    uint8_t hall_v = gpio_dev->gpio_read(PortGPIOH,11);
    uint8_t hall_w = gpio_dev->gpio_read(PortGPIOH,12);

    hall_state = (hall_u) | (hall_v << 1) | (hall_w << 2);

    // if(cnt==1000) {
    //     cnt = 0;
    //     printf("cnt:%d\r\n",hall_state);
    // }

    /* 顺序6,2,3,1,5,4 */  

    if(dir == 0) {
        
    } else { //顺序 4 5 1 3 2 6
        hall_state = 7 - hall_state;  //反转
    }
    switch (hall_state) { 
        case 6:                //w上臂导通 u下臂导通 whul
            pwm_dev->pwm_set_duty(1,0);
            pwm_dev->pwm_set_duty(2,0);
            pwm_dev->pwm_set_duty(3,test_speed); //w上输出pwm

            gpio_dev->gpio_write(PortGPIOB,13,1); //u下高电平
            gpio_dev->gpio_write(PortGPIOB,14,0);
            gpio_dev->gpio_write(PortGPIOB,15,0);
        break;

        case 2:                //v上臂导通  u下臂导通 vhul
            pwm_dev->pwm_set_duty(1,0);
            pwm_dev->pwm_set_duty(2,test_speed);   //v上输出pwm
            pwm_dev->pwm_set_duty(3,0);

            gpio_dev->gpio_write(PortGPIOB,13,1); //u下高电平
            gpio_dev->gpio_write(PortGPIOB,14,0);
            gpio_dev->gpio_write(PortGPIOB,15,0);
        break;

        case 3:                //v上臂导通  w下臂导通 vhwl
            pwm_dev->pwm_set_duty(1,0);   
            pwm_dev->pwm_set_duty(2,test_speed); //v上输出pwm
            pwm_dev->pwm_set_duty(3,0);

            gpio_dev->gpio_write(PortGPIOB,13,0);
            gpio_dev->gpio_write(PortGPIOB,14,0);
            gpio_dev->gpio_write(PortGPIOB,15,1);//w下高电平
        break;

        case 1:                //u上臂导通  w下臂导通   uhwl
            pwm_dev->pwm_set_duty(1,test_speed); //u上输出pwm
            pwm_dev->pwm_set_duty(2,0);
            pwm_dev->pwm_set_duty(3,0);

            gpio_dev->gpio_write(PortGPIOB,13,0);
            gpio_dev->gpio_write(PortGPIOB,14,0);
            gpio_dev->gpio_write(PortGPIOB,15,1); //w下高电平
        break;

        case 5:               //u上臂导通  v下臂导通  uhvl
            pwm_dev->pwm_set_duty(1,test_speed);  //u上输出pwm
            pwm_dev->pwm_set_duty(2,0);
            pwm_dev->pwm_set_duty(3,0);

            gpio_dev->gpio_write(PortGPIOB,13,0);
            gpio_dev->gpio_write(PortGPIOB,14,1);//v下高电平
            gpio_dev->gpio_write(PortGPIOB,15,0);
        break;

        case 4:              //w上臂导通  v下臂导通  whvl
            pwm_dev->pwm_set_duty(1,0);
            pwm_dev->pwm_set_duty(2,0);
            pwm_dev->pwm_set_duty(3,test_speed); //w上输出pwm

            gpio_dev->gpio_write(PortGPIOB,13,0);
            gpio_dev->gpio_write(PortGPIOB,14,1);//v下高电平
            gpio_dev->gpio_write(PortGPIOB,15,0);

        break;
    }
  

}

int main()
{
    int ret;
    board_init();

    /*dev init */
    clk_ops_t* rcc_dev = clk_ops_get();
    gpio_dev = gpio_ops_get_by_name("STM32F407_GPIO");
    pwm_dev = pwm_ops_get_by_name("TIM1_PWM");
    period_timer_ops_t* timer2 = period_timer_ops_get_by_name("Timer2_Period");
    /*end dev init*/

    /* 时钟初始化 */
    rcc_dev->clk_init();

    /* 初始化IO */
    gpio_dev->gpio_init();

    /* 初始化PWM */
    pwm_dev->pwm_init(16800,call_back);
    pwm_dev->pwm_start(1);
    pwm_dev->pwm_start(2);
    pwm_dev->pwm_start(3);

    /*LED*/
    gpio_dev->gpio_write(PortGPIOE,0,GPIO_PIN_LOW);
    gpio_dev->gpio_write(PortGPIOE,1,GPIO_PIN_LOW);
    gpio_dev->gpio_write(PortGPIOF,10,1);
    ret = init_debug_serial("Debug_UART",115200,Data_Bits_8,Stop_Bits_1,None_Parity);
    if (ret != 0) {
        return ret;
    }

    while(1){}
}

