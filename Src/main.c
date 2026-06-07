#include "gpio.h"
#include "delay.h"

bool btn_state;

int main(void) {
	/* Init port b */
	init_port_b();

	while(1) {
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
