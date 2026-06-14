#include "gpio_exti.h"
#include "stm32g071xx.h"

/* Enable interrupts for button one.
*  Currently connected to GPIOA Pin 9 (PA9)
*/
void button_one_exti_init(void) {
    // Disable global interrupts
    __disable_irq();

    // Assuming GPIO has already been configured
    // Assuming Pin has already been configured

    // Enable SYSCFG clock
    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;

    // Select PORTA for EXTI9    
    EXTI->EXTICR[2] &= ~EXTI_EXTICR3_EXTI9;   // 0x00 = PA

    // Unmask EXTI9
    EXTI->IMR1  |=  EXTI_IMR1_IM9;       // unmask line 9
    
    // Select falling edge trigger
    EXTI->FTSR1 |=  EXTI_FTSR1_FT9;      // falling edge trigger
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT9;      // disable rising edge

    // Enable EXTI9 line in NVIC
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    // Enable global interrupts
    __enable_irq();
}

/* Enable interrupts for button two.
*  Currently connected to GPIOA Pin 7 (PA7)
*/
void button_two_exti_init(void) {
    // Disable global interrupts
    __disable_irq();

    // Assuming GPIO has already been configured
    // Assuming Pin has already been configured

    // Enable SYSCFG clock
    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;

    // Select PORTA for EXTI9    
    EXTI->EXTICR[2] &= ~EXTI_EXTICR3_EXTI9;   // 0x00 = PA

    // Unmask EXTI9
    EXTI->IMR1  |=  EXTI_IMR1_IM7;       // unmask line 7
    
    // Select falling edge trigger
    EXTI->FTSR1 |=  EXTI_FTSR1_FT7;      // falling edge trigger
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT7;      // disable rising edge

    // Enable EXTI7 line in NVIC
    NVIC_EnableIRQ(EXTI4_15_IRQn);

    // Enable global interrupts
    __enable_irq();
}