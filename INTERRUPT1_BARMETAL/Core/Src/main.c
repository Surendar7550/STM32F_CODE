#include "stm32f446xx.h"
#include <stdio.h>
#include <stdint.h>


/*PA5 IS LED & PC13 BUTTON*/
#define GPIOAEN		(1U<<0)
#define PIN_PA5		(1U<<5)

#define GPIOCEN		(1U<<2)
#define SYSCFEN		(1U<<14) //SYSTEM CONFIGURATION ENABLE
#define BUTTON		(1U<<13)

#define	EXTI_PR		(1U<<13) //PENDING REGISTER ENABLE

static void callback(void);

void interrupt(void)
{
	__disable_irq();  //DISABLE GLOBAL INTERRUPT

	RCC->AHB1ENR |=GPIOCEN;
	//PC13 CHANGE TO INPUT PIN
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	RCC->APB2ENR |=SYSCFEN;

	SYSCFG->EXTICR[3] &= ~(0xF << 4); //SET ALL PIN IS 0
	SYSCFG->EXTICR[3] |= (0x2 << 4);  //SET 5 PIN 1 FOR PC13 BUTTON
	//SYSCFG->EXTICR[3] |=(1U<<5);

	EXTI->IMR |=(1U<<13); //ENABLE INT MARKUP REGISTER

	//EXTI->FTSR |=(1U<<13); //ENABLE FALLING TRIGGER SET REGISTER

	EXTI->RTSR |=(1U<<13);   //ENABLE RISING TRIGGER SET REGISTER

	NVIC_EnableIRQ(EXTI15_10_IRQn); //ENABLE INTERRUPT REQUEST

	__enable_irq();  //ENABLE GLOBAL INTERRUPT
}

int main()
{

	RCC->AHB1ENR |=GPIOAEN;
	//PA5 CHANGE TO OUTPUT PIN
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	interrupt();
	while(1)
	{
		;
	}
}
static void callback(void)
{
	GPIOA->ODR ^=PIN_PA5; //TOGGLE THE LED
}
void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & EXTI_PR)!=0) //CHECK THE PR IS 1 ARE 0
	{
		EXTI->PR |=EXTI_PR;   //CLEAR THE  PR REGISTER
		callback();
	}
}
