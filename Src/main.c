#include "gpio.h"
#include "delay.h"

bool btn_state;

int main(void) {
	/*Initialize LED*/
	led_init();

	/*Initialize Pushbutton*/
	button_init();

	/* Init port b */
	init_port_b();

	while(1) {
		/*Get Pushbutton State*/
		btn_state = get_btn_state();
		if(btn_state) {
			led_on();
		} else {
			led_off();
		}

		pin_high(GPIOB, 4);
		delay_ms(500);
		pin_low(GPIOB, 4);
		delay_ms(500);
		pin_high(GPIOB, 3);
		delay_ms(500);
		pin_low(GPIOB, 3);
		delay_ms(500);
	}
}
