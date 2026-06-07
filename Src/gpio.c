#include "gpio.h"

#define GPIOAEN (1U<<0)
#define LED_BS5 (1U<<5)  /*Bit Set Pin 5*/
#define LED_BR5 (1U<<21) /*Bit Reset Pin 5*/

#define GPIOCEN (1U<<2)
#define BTN_PIN (1U<<13)

void led_init(void) {
	/*Enable clock access to GPIOA*/
	RCC->IOPENR |= GPIOAEN;

	/*Set PA5 mode to output mode*/
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);
}

void led_on(void) {
	/*Set PA5 high*/
	GPIOA->BSRR |=LED_BS5;
}

void led_off(void) {
	/*Set PA5 low*/
	GPIOA->BSRR |=LED_BR5;
}

void button_init(void) {
	/*Enable clock access to PORTC*/
	RCC->IOPENR |=GPIOCEN;

	/*Set PC13 as an input pin*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);
}

bool get_btn_state(void) {
	/*Note : BTN is active low*/

	/*Check if button is pressed*/
	if(GPIOC->IDR & BTN_PIN) {
		return false;
	} else {
		return true;
	}
}

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