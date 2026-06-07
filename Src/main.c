#include "stm32g0xx.h"
#include "gpio.h"
#include "delay.h"

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
uint8_t g_flash_led = 0;
uint32_t g_w_delay = W_DELAY_SLOW;
uint32_t g_rgb_delay = RGB_DELAY_SLOW;

/* Prototypes */
void init_port_b(void);
void init_port_a(void);

void control_rgb_led(int red, int green, int blue);

void task_read_buttons(void);
void task_flash(void);
void task_rgb(void);

/* Main Program Entry */
int main(void) {
	/* Init gpio ports */
	init_port_b();
	init_port_a();
	
	/* Main Program Loop */
	while(1) {
		task_read_buttons();
		task_flash();
		task_rgb();
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
		control_rgb_led(1, 0, 0);
		delay(g_rgb_delay);
		control_rgb_led(0, 1, 0);
		delay(g_rgb_delay);
		control_rgb_led(0, 0, 1);
		delay(g_rgb_delay);
	}
}
