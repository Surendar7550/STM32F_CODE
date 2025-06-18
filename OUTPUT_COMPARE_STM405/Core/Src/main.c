#include "stm32f405xx.h"
#include <stdio.h>
#include <stdint.h>
//PC6 IS LED PIN
#define GPIOCEN			(1U<<2) //GPIOA ENABLE
#define TIM3_EN			(1U<<1) //TIMER3 ENBLAE
#define CEN_EN			(1U<<0) //COUNTER ENABLE
#define SET_TOGGLE		(1U<<4) | (1U<<5) //SET THE TOGGLE MODE CCMR1 REGISTER
#define COMPARE_EN		(1U<<0)  //ENABLE THE COMPARE MODE CCER REGISTER
void output_compare()
{
	RCC->APB1ENR |=TIM3_EN;
	TIM3->PSC = 16000-1; //SET PRESCALER VALUE
	TIM3->ARR = 500-1;   //SET PERIOD VALUE
	//SET OUTPUT COMPARE 1 SELECTION
	TIM3->CCMR1 &=~(1U<<1);
	TIM3->CCMR1 &=~(1U<<1);

	TIM3->CCMR1 |=SET_TOGGLE;
	/*
	TIM2->CCMR1 |=(1U<<4);
	TIM2->CCMR1 |=(1U<<5);
	TIM2->CCMR1 &=~(1U<<6); */

	TIM3->CCER |=COMPARE_EN;

	TIM3->CNT =0;  //CLEAR THE COUNTER

	TIM3->CR1 |=CEN_EN;
}
int main()
{
	RCC->AHB1ENR |=GPIOCEN;
	//PC6 CHANGE MODE FOE ALTERNATE FUNCTION
	GPIOC->MODER |=(1U<<13);
	GPIOC->MODER &=~(1U<<12);
	//SET THE ALTERNATE FUNCTION PA5 TO AF2 SET TIM2_CH1
	GPIOC->AFR[0] &=~(1U<<27);
	GPIOC->AFR[0] &=~(1U<<26);
	GPIOC->AFR[0] |=(1U<<25);
	GPIOC->AFR[0] &=~(1U<<24);

	output_compare();

}
