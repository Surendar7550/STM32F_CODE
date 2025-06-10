#include "stm32f4xx.h"
//void delayms(int n);

int main()
{
	RCC->AHB1ENR |=1;
	GPIOA->MODER &=~0x00000C00;
	GPIOA->MODER |=0x00000400;
	while(1)
	{
		GPIOA->ODR |=0x00000020;
		//delayms(500);
		for(int i=0;i<30000;i++);
		GPIOA->ODR &=~0x00000020;
		//delayms(500);
	}
}
//void delayms (int n)
//{
//	int i;
//	for(;n>0;n--)
//		for(i=0;i<3195;i++);
//}
