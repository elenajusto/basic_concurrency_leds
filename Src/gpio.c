#include "gpio.h"

#define GPIOBEN (1U << 1)

void init_pin(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode) {
	port->MODER = (port->MODER & ~(0x3UL << (pin * 2))) | ((uint32_t)mode  << (pin * 2));
}

void pin_high(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << pin);
}

void pin_low(GPIO_TypeDef *port, uint8_t pin) {
	port->BSRR = (1UL << (pin + 16));
}

void init_port_b(void) {
	RCC->IOPENR |= GPIOBEN;
	init_pin(GPIOB, 4, GPIO_MODE_OUTPUT);  // D5
	init_pin(GPIOB, 5, GPIO_MODE_OUTPUT);  // D6
	init_pin(GPIOB, 3, GPIO_MODE_OUTPUT);  // D3
}