#include "gpio.h"

void init_pin(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode) {
	port->MODER = (port->MODER & ~(0x3UL << (pin * 2))) | ((uint32_t)mode  << (pin * 2));
}

void pin_high(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << pin);
}

void pin_low(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << (pin + 16));
}