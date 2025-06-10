#include "stm32f4xx.h"   //user file

#include <stdint.h> //standard file

#define GPIOA_EN          (1U << 0)     //GPIOA ENABLE
#define USART_EN		   (1U << 17)	//UART ENABLE
//#define PA_2					   (1U << 2)		//GPIOA ->PA2 ENABLE
#define CR1_UART_EN  (1U << 13)   //CONTROLER REGISTOR ENBLAE UART
#define CR1_TX_EN		   (1U << 3)		//CONTROLER REGISTOR ENBLAE TRANSMITT
#define SR_EN				    (1U << 7)
//CLOCK DEFINE
#define PERI_CLOCK     16000000

//BAUD RATE
#define  BAUD_RATE		115200

void uart_init()
{
	RCC ->AHB1ENR |=GPIOA_EN;       //AHB1 BUS ENABLE

	//GPIOA->MODER = (0X00000020);   //PA2 CHANGE TO MODE OF ALTERNATE FUNCTION
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &=~(1U << 4);

	// setting PA3 is AF function
	GPIOA->MODER &= ~(1U<<6);
    GPIOA->MODER |= (1U<<7);

	GPIOA->AFR[0] |= (1U << 8);   //SET THE ALTERNATE FUNCTION LOW REGISTER FOR UART TX
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &=~(1U << 11);

	//setting PA3 Mapped with UART_RX
	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);

	RCC->APB1ENR |= USART_EN;		//APB1 BUS ENABLE

	USART2->BRR = ((PERI_CLOCK + (BAUD_RATE /2U)) / BAUD_RATE);

	USART2->CR1 |= CR1_TX_EN ;

	//Receiver Enable
	USART2->CR1 |=(1U<<2);

	USART2->CR1 |= CR1_UART_EN;
}
void delayMs(int delay)
{
    int i;
    for (i=0; delay>0; delay--)
        for (i=0; i<3195; i++) ;
}
void uart_write(uint8_t ch)
{
	//checking UART Transfered or Not
	while(!(USART2->SR & (1U<<7))){}
    USART2->DR =(ch & 0xFF);
}
void string_write(uint8_t *ch)
{
	//String Write inside UART
	while(*ch)
	{
		uart_write(*ch++);
		delayMs(30);
	}
}
uint8_t uart_read(void)
{
	while(!(USART2->SR & (1U << 6))) {}
	return USART2->DR;
}

uint8_t s;
int main()
{
	uart_init();
	uint8_t  my[10]="HELLO";
	while(1)
		{
		    string_write(my);
			delayMs(30);
			s=uart_read();
			uart_write(s);

		}
		return 0;
}
