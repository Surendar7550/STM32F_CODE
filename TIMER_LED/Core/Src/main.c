#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOAEN			(1U<<0) //ENABLE GPIOA
#define LED_PIN_5		(1U<<5) //ENABLE GPIOA ->PA5 FOR LED

#define TIM2_EN			(1U<<0) //ENABLE TIMER 2
#define CR1_CEN			(1U<<0) //ENABLE COUNTER REGISTER IN CONTROLER REGISTRER
#define SR_UIF			(1U<<0) //ENABLE UPDATE INTERRUPT FLAG IN STATUS REGISTER

void timer_call()
{
	RCC->APB1ENR |=TIM2_EN; //ENABLE TIMER2

	TIM2->PSC = 16000-1;  //SET PRESCALER VALUE

	TIM2->ARR = 1000-1;   //SET AUTO-RELOAD VALUE & PERIOD VALUE. GO 0 TO 1000 RETURN 0 TO 1000. UP COUNTER

	TIM2->CNT = 0;        //CLEAR COUNTER VALUE

	TIM2->CR1 |= CR1_CEN; //ENABLE COUNTER REGISTER IN CONTROLER REGISTRER
}

int main()
{
	RCC->AHB1ENR |=GPIOAEN;  //ENABLE GPIOA
	//SET OUTPUT LED PIN FOR PA5
	GPIOA->MODER &=~(1U<<11);
	GPIOA->MODER |=(1U<<10);

	timer_call();
	{
		while(1)
		{
			while(!(TIM2->SR & SR_UIF)){}
			TIM2->SR &=~ SR_UIF;    //CLEAR THE  UPDATE FLAG
			GPIOA->ODR ^=LED_PIN_5; //TOGGLE THE LED
		}
	}

}
/*SR->UIF  0: No update occurred.
           1: Update interrupt pending.*/
