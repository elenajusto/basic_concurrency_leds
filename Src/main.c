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
void control_rgb_Led(int red, int green, int blue);

/* Main Program Entry */
int main(void) {
	/* Init gpio ports */
	init_port_b();
	init_port_a();
	
	/* Main Program Loop */
	while(1) {
		control_rgb_Led(1,0,0);
 		delay_ms(200);
		control_rgb_Led(0,0,0);
		delay_ms(200);

		control_rgb_Led(0,1,0);
		delay_ms(200);
		control_rgb_Led(0,0,0);
		delay_ms(200);

		control_rgb_Led(0,0,1);
		delay_ms(200);
		control_rgb_Led(0,0,0);
		delay_ms(200);
		

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

void control_rgb_Led(int red_on, int green_on, int blue_on) {
	if (red_on) {
		pin_high(GPIOB, RED_LED_PIN);
	} else {
		pin_low(GPIOB, RED_LED_PIN);
	}

	if (green_on) {
		pin_high(GPIOB, GREEN_LED_PIN);
	} else {
		pin_low(GPIOB, GREEN_LED_PIN);
	}

	if (blue_on) {
		pin_high(GPIOA, BLUE_LED_PIN);
	} else {
		pin_low(GPIOA, BLUE_LED_PIN);
	}
}