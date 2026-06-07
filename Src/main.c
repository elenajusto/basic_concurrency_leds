#include "stm32g0xx.h"
#include "gpio.h"
#include "delay.h"

/* Prototypes */
void init_port_b(void);
void init_port_a(void);

/* Main Program Entry */
int main(void) {
	/* Init gpio ports */
	init_port_b();
	init_port_a();
	
	/* Main Program Loop */
	while(1) {
		pin_high(GPIOB, 4);
		delay_ms(200);
		pin_low(GPIOB, 4);

		pin_high(GPIOB, 3);
		delay_ms(200);
		pin_low(GPIOB, 3);

		pin_high(GPIOA, 10);
		delay_ms(200);
		pin_low(GPIOA, 10);

	}
}

/* Function definitions */
void init_port_b(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN ;
	init_pin(GPIOB, 4, GPIO_MODE_OUTPUT);  // D5
	init_pin(GPIOB, 3, GPIO_MODE_OUTPUT);  // D3
}

void init_port_a(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN ;
	init_pin(GPIOA, 10, GPIO_MODE_OUTPUT);  // D2
}
