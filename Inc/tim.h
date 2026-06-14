#ifndef TIM_H_
#define TIM_H_

#include "stm32g071xx.h"

void tim2_1hz_init(void);
void tim2_delay(uint32_t delay_ms);

#endif /* TIM_H_ */
