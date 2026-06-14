#include "tim.h"

void tim2_1hz_init(void) {
    // enable clock access to tim2
    RCC->APBENR1 |= RCC_APBENR1_TIM2EN;

    // set prescaler: 16MHz / 16000 = 1kHz timer clock
    TIM2->PSC = 15999;

    // set auto-reload: 1kHz / 1000 = 1Hz overflow
    TIM2->ARR = 999;

    // clear counter
    TIM2->CNT = 0;

    // enable timer
    TIM2->CR1 |= TIM_CR1_CEN;
}

void tim2_delay(uint32_t delay_ms) {
    TIM2->ARR = delay_ms - 1;
    TIM2->CNT = 0;
    while (!(TIM2->SR & TIM_SR_UIF));
    TIM2->SR &= ~TIM_SR_UIF;
}