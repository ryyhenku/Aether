#include "subsys_gpio.h"

static gpio_ops_t* __gpio_devs[8];
static uint8_t __gpio_count = 0;

void gpio_dev_register(gpio_ops_t *ops)
{
    if (__gpio_count < 8) {
        __gpio_devs[__gpio_count] = ops;
        __gpio_count = __gpio_count ++;
    }
}

gpio_ops_t* gpio_ops_get_by_name(char *name)
{
    for (int i = 0; i < 8; i++) {
        if (__gpio_devs[i] != NULL) {
            if (strcmp(name, __gpio_devs[i]->gpio_name) == 0) {
                return __gpio_devs[i];
            }
        }
    }

    return NULL;
}

int gpio_init(gpio_ops_t *gpio_dev)
{
    if (gpio_dev != NULL) {
        return gpio_dev->gpio_init();
    }
    return -1;
}

int gpio_write(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin, gpio_pin_state_t state)
{
    if (gpio_dev != NULL) {
        return gpio_dev->gpio_write(port, pin, state);
    }
    return -1;
}

gpio_pin_state_t gpio_read(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin)
{
    if (gpio_dev != NULL) {
        return gpio_dev->gpio_read(port, pin);
    }
    return GPIO_PIN_LOW;
}

int gpio_toggle(gpio_ops_t *gpio_dev, uint8_t port, uint8_t pin)
{
    if (gpio_dev != NULL) {
        return gpio_dev->gpio_toggle(port, pin);
    }
    return -1;
}
