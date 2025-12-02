#include "my.h"

#define GPIOCEN			(1U << 2)
#define SYSCFGEN		(1U << 14) //RCC -> SYS CONFIG ENABLE


void pc13_int_init(void)
{
	__disable_irq(); //disable global interrupt

	RCC->AHB1ENR |=GPIOCEN;

	GPIOC->MODER &=~(1U << 26);
	GPIOC->MODER &=~(1U << 27);


	RCC->APB1ENR |=SYSCFGEN;

	//SYSCFG->EXTICR[3] |=(1U << 5); //EXTICR4 IS 3

	SYSCFG->EXTICR[3] &= ~(0xF << 4);
	SYSCFG->EXTICR[3] |= (0x2 << 4);

	EXTI->IMR |=(1U << 13); //INTERRUPT MASK REGISTER

	EXTI->RTSR |=(1U << 13); //RISHING EDGE DEACTION

	//EXTI->FTSR |=(1U << 13); //FALING EDGE DEACTION

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();
}
