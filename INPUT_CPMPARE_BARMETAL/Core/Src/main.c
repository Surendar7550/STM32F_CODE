#include "stm32f446xx.h"
#include <stdio.h>
#include <stdint.h>

//GPIOA ENABLE AND PA5 MODE CHANGE FOR ALTERNATE FUNCTION
#define GPIOAEN			(1U<<0)
#define TIM2_EN			(1U<<0) //TIMER 2 ENABLE

#define TIM3_EN			(1U<<1)
#define CNT_EN			(1U<<0) //COUNTER ENABLE
#define SET_TOGGLE		(1U<<4) | (1U<<5) //SET THE TOGGLE MODE CCMR1 REGISTER
#define CCER_COMP_EN	(1U<<0)
#define SR_UIF_EN		(1U<<0) //STATUS REGISTER UPDATE INTERRUPT ENABLE

//INPUT CAPTURE REGISTER
#define SR_CCIF_EN		(1U<<1) //Capture/compare 1 interrupt flag SET CAPTURE
//#define CCER_CAPT_EN	(1U<<0)
void Output_Compare()
{
	RCC->APB1ENR |=TIM2_EN;

	TIM2->PSC = 16000 - 1; //SET PRESCALER VLAUE
	TIM2->ARR = 1000 - 1;  //SET AUTO RELOAD REGISTER

	//CONFIGURE THE OUTPUT COMPARE MODE
	TIM2->CCMR1 &=~(1U<<0);
	TIM2->CCMR1 &=~(1U<<1);

	//SET TOGGLE MODE ON CCMR1 001 IS TOGGLE
	TIM2->CCMR1 |=SET_TOGGLE;
/*	TIM2->CCMR1 &=~(1U<<6);
	TIM2->CCMR1 |=(1U<<5);
	TIM2->CCMR1 |=(1U<<4);  */

	TIM2->CCER |=CCER_COMP_EN;

	TIM2->CNT =0;

	TIM2->CR1 |=CNT_EN;
}
void Input_Capture()
{
	RCC->APB1ENR |=TIM3_EN;

	TIM3->PSC =16000 - 1;

	//SET CAPTURE MODE
	TIM3->CCMR1 |=(1U<<0);
	TIM3->CCMR1 &=~(1U<<1);

	TIM3->CCER |=CCER_COMP_EN;
	//Capture/Compare 1 output Polarity FOR CCER REFISTER
	//TIM3->CCER &=~(1U<<1);
	//TIM3->CCER &=~(1U<<3);

	TIM3->CR1 |=CNT_EN;
}
int timestamp=0;

int main()
{
	RCC->AHB1ENR |=GPIOAEN;

	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);

	GPIOA->AFR[0] |=(1U<<20);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] &=~(1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);
	Output_Compare();
	//PA6 IS INPUT CAPTURE
	RCC->AHB1ENR |=GPIOAEN;

	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=(1U<<13);

	GPIOA->AFR[0] &=~(1U<<27);
	GPIOA->AFR[0] &=~(1U<<26);
	GPIOA->AFR[0] |=(1U<<25);
	GPIOA->AFR[0] &=~(1U<<24);
	Input_Capture();
	while(1)
	{
		while(!(TIM3->SR & SR_CCIF_EN)){}

		timestamp = TIM3->CCR1; // CAPTURED VALUE
	}
}
