#include "stm32g071xx.h"
#include "stm32g0xx.h"
#include "gpio.h"
#include "delay.h"
#include "gpio_exti.h"
#include <stdio.h>

/* Defines */
#define RED_LED_PIN		4
#define GREEN_LED_PIN	3
#define BLUE_LED_PIN	10
#define BUTTON_ONE_PIN	9
#define BUTTON_TWO_PIN	7

#define W_DELAY_SLOW 	400
#define W_DELAY_FAST 	200
#define RGB_DELAY_SLOW 	4000
#define RGB_DELAY_FAST	1000

/* INit global variables */
volatile uint8_t g_flash_led = 0;
volatile uint32_t g_w_delay = W_DELAY_SLOW;
volatile uint32_t g_rgb_delay = RGB_DELAY_SLOW;

/* Prototypes */
void init_port_b(void);
void init_port_a(void);

void control_rgb_led(int red, int green, int blue);

void task_read_buttons(void);
void task_flash(void);
void task_rgb(void);

void task_rgb_fsm(void);
void task_flash_fsm(void);

/* Main Program Entry */
int main(void) {
	/* Init gpio ports */
	init_port_b();
	init_port_a();
	
	/* Main Program Loop */
	while(1) {
		task_read_buttons();
		task_rgb_fsm();
		task_flash_fsm();
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

void control_rgb_led(int red_on, int green_on, int blue_on) {
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

void task_read_buttons(void) {
	if (pin_read(GPIOA, BUTTON_ONE_PIN)) {
		g_flash_led = 1;
	} else {
		g_flash_led = 0;
	}
	if (pin_read(GPIOA, BUTTON_TWO_PIN)) {
		g_w_delay = W_DELAY_FAST;
		g_rgb_delay = RGB_DELAY_FAST;
	} else {
		g_w_delay = W_DELAY_SLOW;
		g_rgb_delay = RGB_DELAY_SLOW;
	}
}

void task_flash(void) {
	if (g_flash_led == 1) {			// only run task when in flash mode
		control_rgb_led(1, 1, 1);
		delay(g_w_delay);
		control_rgb_led(0, 0, 0);
		delay(g_w_delay);
	}
}

void task_rgb(void) {				// only run task when NOT flash mode
	if (g_flash_led == 0) {
		// red state
		control_rgb_led(1, 0, 0);
		delay(g_rgb_delay);

		// green state
		control_rgb_led(0, 1, 0);
		delay(g_rgb_delay);

		// blue state
		control_rgb_led(0, 0, 1);
		delay(g_rgb_delay);
	}
}

void EXTI4_15_IRQHandler(void) {
	if ((EXTI->FPR1 & EXTI_FPR1_FPIF9) != 0) {
		EXTI->FPR1 |= EXTI_FPR1_FPIF9;
		control_rgb_led(1,0,1);
	}

	if ((EXTI->FPR1 & EXTI_FPR1_FPIF7) != 0) {
		EXTI->FPR1 |= EXTI_FPR1_FPIF7;
		control_rgb_led(0,1,1);
	}
}

void task_rgb_fsm(void) {
	static enum {
		ST_RED,
		ST_GREEN,
		ST_BLUE,
		ST_OFF
	} next_state;

	if (g_flash_led == 0) {
		switch (next_state) {
			case ST_RED:
				control_rgb_led(1, 0, 0);
				delay(g_rgb_delay);
				next_state = ST_GREEN;
				break;

			case ST_GREEN:
				control_rgb_led(0, 1, 0);
				delay(g_rgb_delay);
				next_state = ST_BLUE;
				break;

			case ST_BLUE:
				control_rgb_led(0, 0, 1);
				delay(g_rgb_delay);
				next_state = ST_RED;
				break;

			default:
				next_state = ST_RED;
				break;
		}
	}
}

void task_flash_fsm(void) {
	static enum {
		ST_WHITE,
		ST_BLACK
	} next_state = ST_WHITE;

	if (g_flash_led == 1) {
		switch (next_state) {
			case ST_WHITE:
				control_rgb_led(1, 1, 1);
				delay(g_w_delay);
				next_state = ST_BLACK;
				break;
			
			case ST_BLACK:
				control_rgb_led(0, 0, 0);
				delay(g_w_delay);
				next_state = ST_WHITE;
				break;

			default:
				next_state = ST_WHITE;
				break;
		}
	}
}