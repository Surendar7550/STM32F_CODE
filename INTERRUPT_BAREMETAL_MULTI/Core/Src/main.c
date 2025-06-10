#include "stm32f446xx.h"
#include <stdio.h>
#include <stdint.h>
#include "my.h"

#define GPIOAEN		(1U << 0)
#define LED_PIN_5	(1U << 5)

#define PR_13       (1U << 13) //PENDING REGISTER

static void in_callback(void);

int main()
{
	RCC->AHB1ENR |=GPIOAEN;

	GPIOA->MODER &=~(1U << 11);
	GPIOA->MODER |=(1U << 10);

	pc13_int_init();
	while(1)
	{

	}

}

static void in_callback(void)
{
	GPIOA->ODR ^= LED_PIN_5;
}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & PR_13)!=0)
	{
		EXTI->PR |=PR_13;  //CLEAR EVERY TIME
		in_callback();
	}
}
