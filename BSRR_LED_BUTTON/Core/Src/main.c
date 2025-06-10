#include "stm32f446xx.h"

//LED 			->PA5
//BUTTON  ->PC13

#define GPIOA_EN			(1U << 0)
#define GPIOC_EN			(1U << 2)

#define LED_PIN				(1U << 5)
#define BUTTON				(1U << 13)


int main()
{
	RCC->AHB1ENR |= GPIOA_EN;
	RCC->AHB1ENR |= GPIOC_EN;

	//LED->MODER
	GPIOA->MODER |= 0x00000400;

	//BUTTON->MODER
	GPIOC->MODER |= 0x00000000;

	while(1)
	{
		if (!(GPIOC->IDR  & BUTTON ))
		{
//			GPIOA->BSRR  = LED_PIN;  //LED ON
			GPIOA->ODR   |=LED_PIN;
		}
		else
		{
			//GPIOA->BSRR = (1U << 21); //21 IS BSR RESET OF PA5
			GPIOA->ODR  &=~LED_PIN;
		}
	}

}
