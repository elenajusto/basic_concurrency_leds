#include "stm32g0xx.h"
#include "gpio.h"
#include "delay.h"

/* Defines */
#define RED_LED_PIN		4
#define GREEN_LED_PIN	3
#define BLUE_LED_PIN	10
#define BUTTON_ONE_PIN	9
#define BUTTON_TWO_PIN	7

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
		pin_high(GPIOB, RED_LED_PIN);
 		delay_ms(200);
		pin_low(GPIOB, RED_LED_PIN);

		pin_high(GPIOB, GREEN_LED_PIN);
		delay_ms(200);
		pin_low(GPIOB, GREEN_LED_PIN);

		pin_high(GPIOA, BLUE_LED_PIN);
		delay_ms(200);
		pin_low(GPIOA, BLUE_LED_PIN);

	}
}

/* Function definitions */
void init_port_b(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN ;
	init_pin(GPIOB, RED_LED_PIN, GPIO_MODE_OUTPUT);  	// D5 
	init_pin(GPIOB, GREEN_LED_PIN, GPIO_MODE_OUTPUT);	// D3 
}

void init_port_a(void) {
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN ;
	init_pin(GPIOA, BLUE_LED_PIN, GPIO_MODE_OUTPUT);    // D2 
	init_pin(GPIOA, BUTTON_ONE_PIN, GPIO_MODE_INPUT);   // D8
	init_pin(GPIOA, BUTTON_TWO_PIN, GPIO_MODE_INPUT);   // D11
}

void control_rgb_Led(int red, int green, int blue) {
}