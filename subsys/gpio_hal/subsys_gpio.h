#ifndef __SUBSYS_GPIO_H__
#define __SUBSYS_GPIO_H__

#include <stdio.h>



#define  PortGPIOA 0
#define  PortGPIOB 1
#define  PortGPIOC 2
#define  PortGPIOD 3
#define  PortGPIOE 4
#define  PortGPIOF 5
#define  PortGPIOG 6
#define  PortGPIOH 7
#define  PortGPIOI 8


typedef enum
{
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH
} gpio_pin_state_t;

typedef struct
{
    char *gpio_name;
    int (*gpio_init)(void);
    int (*gpio_write)(uint8_t port, uint8_t pin, gpio_pin_state_t state);
    gpio_pin_state_t (*gpio_read)(uint8_t port, uint8_t pin);
    int (*gpio_toggle)(uint8_t port, uint8_t pin);
} gpio_ops_t;

void gpio_dev_register(gpio_ops_t *ops);
gpio_ops_t* gpio_ops_get_by_name(char *name);
int gpio_init(gpio_ops_t *gpio_dev);
int gpio_write(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin, gpio_pin_state_t state);
gpio_pin_state_t gpio_read(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin);
int gpio_toggle(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin);

#endif /* __SUBSYS_GPIO_H__ */
