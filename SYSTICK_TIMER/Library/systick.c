#include "stm32f4xx.h"
#include "systick.h"

#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUTERFLAG			(1U<<16)

void systickDelayMs(int delay)
{
	//RELOAD WITH VALUE NUMBER OF CLOCK MILLISECOND
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//CLEAR THE CURRENT VALUE REGISTER
	SysTick->VAL = 0;

	//ENABLE SYSTICK AND SELECT INTERNAL CLK SOURCE
	SysTick->CTRL =CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0; i<delay; i++)
	{
		//WAIT AT COUNTER FLAG IS SET
		while((SysTick->CTRL & CTRL_COUTERFLAG)==0){}
	}
	SysTick->CTRL = 0;
}
