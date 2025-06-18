#include "stm32f446xx.h"
#include <stdint.h>

#define GPIOAEN			(1U<<0)
#define RCC_ADC_EN		(1U<<8)
#define SQR3_S1_EN  	(1U<<0) //REGULAR SEQUENCE REGISTER 3
#define SQR1_L_EN       0X00    //REGULAR CHANNEL SEQUENCE LENGTH
#define CR2_ADC_ON		(1U<<0) //ENABLE ADC
#define CR2_CONT_EN		(1U<<1) //CONTINUOUS CONVERSION MODE
#define CR2_SWSTART		(1U<<30) // START  CONVERSION OF REGULAR CHANNELS
#define SR_EOC_EN		(1U<<1)  //END OF CONVERSION
void adc_init()
{
	RCC->AHB1ENR |=GPIOAEN;

	//CHNAGE TO ANALOG M0DE
	GPIOA->MODER |=(1U<<0);
	GPIOA->MODER |=(1U<<1);

	RCC->APB2ENR |=RCC_ADC_EN;

	ADC1->SQR3 |=SQR3_S1_EN;

	ADC1->SQR1 |=SQR1_L_EN;

	ADC1->CR2  |=CR2_ADC_ON;
}
void start_conversion()
{
	//ADC1->CR2 &=~(1U<<1);
	ADC1->CR2 |=CR2_CONT_EN;
	ADC1->CR2 |=CR2_SWSTART	;
}
uint32_t sensor_value;
int main()
{
	adc_init();

	while(1)
	{
		/*start_conversion();
		while(!(ADC1->SR & SR_EOC_EN)){}
		sensor_value =(ADC1->DR);*/

	}
	return 0;
}
