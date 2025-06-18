#include "stm32f446xx.h"
#include <stdint.h>

#define GPIOAEN     (1U << 0)
#define ADC1EN      (1U << 8)

#define CR2_ADON    (1U << 0)
#define CR2_CONT    (1U << 1)
#define CR2_SWSTART (1U << 30)

#define SR_EOC      (1U << 1)
#define CR1_EOCIE   (1U << 5)

volatile uint32_t sensor_value = 0;

void adc_init(void)
{
    // Enable GPIOA clock
    RCC->AHB1ENR |= GPIOAEN;

    // Set PA0 to analog mode
    GPIOA->MODER |= (1U << 0) | (1U << 1);

    // Enable ADC1 clock
    RCC->APB2ENR |= ADC1EN;

    // Configure ADC sequence
    ADC1->SQR3 = 1; // Channel 1 (PA0)
    ADC1->SQR1 = 0; // 1 conversion

    // Enable EOC interrupt
    ADC1->CR1 |= CR1_EOCIE;

    // Enable ADC, continuous conversion
    ADC1->CR2 |= CR2_CONT;
    ADC1->CR2 |= CR2_ADON;

    // Enable ADC1 interrupt in NVIC
    NVIC_EnableIRQ(ADC_IRQn);
}

void start_conversion(void)
{
    ADC1->CR2 |= CR2_SWSTART;
}

// ADC interrupt handler
void ADC_IRQHandler(void)
{
    if (ADC1->SR & SR_EOC)
    {
        sensor_value = ADC1->DR; // Reading DR clears EOC
    }
}

int main(void)
{
    adc_init();
    start_conversion();  // Just once

    while (1)
    {
        // Main loop can do other things.
        // sensor_value is updated automatically in the interrupt
    }

    return 0;
}
