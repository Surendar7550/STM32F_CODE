#include "stm32f405xx.h"

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

	GPIOA->AFR[0] |= (1U << 8);   //SET THE ALTERNATE FUNCTION LOW REGISTER FOR UART TX
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &=~(1U << 11);

	RCC->APB1ENR |= USART_EN;		//APB1 BUS ENABLE

	USART2->BRR = ((PERI_CLOCK + (BAUD_RATE /2U)) / BAUD_RATE);

	USART2->CR1 |= CR1_TX_EN ;

	USART2->CR1 |= CR1_UART_EN;
}
void uart_write(uint8_t *ch)
{
	int i=0;
while(ch[i] !='\0')
{
	while(!(USART2->SR  & SR_EN)) {}
	USART2->DR = (ch[i] & 0XFF);
	i++;
}
}
int main()
{
	uart_init();
	uint8_t  my[10]="HELLO";
	while(1)
		{
			uart_write(my);
		}
		return 0;
}
