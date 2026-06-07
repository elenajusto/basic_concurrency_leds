#ifndef GPIO_H_
#define GPIO_H_

#include "stm32g0xx.h"
#include <stdbool.h>

void led_init(void);
void led_on(void);
void led_off(void);

void button_init(void);
bool get_btn_state(void);

typedef enum {
    GPIO_MODE_INPUT  = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_AF     = 2,
    GPIO_MODE_ANALOG = 3
} gpio_mode_t;

void init_pin(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode);

void pin_high(GPIO_TypeDef *port, uint8_t pin);
void pin_low(GPIO_TypeDef *port, uint8_t pin);

#endif /* GPIO_H_ */
