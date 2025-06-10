#define PHER_BASE 				(0x40000000UL)
#define AHB1_OFFSET			(0x00020000U)
#define AHB1_BASE				(PHER_BASE + AHB1_OFFSET)

#define GPIOB_OFFSET			(0x400UL)
#define GPIOB_BASE				(AHB1_BASE + GPIOB_OFFSET )

//  GPIOC
#define GPIOC_OFFSET			(0x800UL)
#define GPIOC_BASE 			(AHB1_BASE + GPIOC_OFFSET)

//RCC SECTION
#define RCC_OFFSET				(0x3800UL )
#define RCC_BASE					(AHB1_BASE + RCC_OFFSET)

//RCC AHB1 ENABLE
#define AHB1ENR_OFFSET  (0x30UL)
#define RCC_AHB1ENR         (*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

#define MODER_OFFSET		(0x00UL)
#define RCC_GPIOB_MODER				(*(volatile unsigned int *)(GPIOB_BASE + MODER_OFFSET))

#define RCC_GPIOC_MODER			(*(volatile unsigned int *)(GPIOC_BASE + MODER_OFFSET))
#define ODR_OFFSET			(0x14UL)
#define GPIOB_ODR				(*(volatile unsigned int *)(GPIOB_BASE + ODR_OFFSET))

#define GPIOC_ODR 				(*(volatile unsigned int *)(GPIOC_BASE + ODR_OFFSET))

#define GPIOB_EN					(1U << 1)
#define GPIOC_EN 					(1U << 2)
#define LED_PIN6					(1U <<6)
#define LED_PIN13					(1U << 13)
#define LED_PIN14					(1U << 14)
#define LED_PIN15					(1U << 15)
void delay();
int main()
{
	RCC_AHB1ENR |=GPIOB_EN;
	RCC_AHB1ENR |=GPIOC_EN;
	RCC_GPIOB_MODER   |= 0x04000000;
	RCC_GPIOB_MODER   |= 0x10000000;
	RCC_GPIOB_MODER   |= 0x40000000;
    RCC_GPIOC_MODER  |= 0x00001000;
	while(1)
	{

		GPIOC_ODR ^=LED_PIN6;
		GPIOB_ODR ^=LED_PIN13;
		GPIOB_ODR ^=LED_PIN14;
		GPIOB_ODR ^=LED_PIN15;
		for( int i=0;i<177777;i++);

	}
}
void delay()
{
	for(int i=0;i<177777;i++);
}
