//AHB1 BUS
#define PHERI_BASE							(0x40000000UL)
#define AHB1_OFFSET						(0x00020000UL)
#define AHB1_BASE							(PHERI_BASE + AHB1_OFFSET)

//GPIOA
#define GPIOA_OFFSET   					(0x00UL)
#define GPIOA_BASE							(AHB1_BASE + GPIOA_OFFSET)

//RCC CLOCK
#define RCC_OFFSET							(0x3800UL)
#define RCC_BASE								(AHB1_BASE + RCC_OFFSET)

//RCC AHB1ENR
#define  AHB1ENR_OFFSET				(0x30UL)
#define  AHB1EN_E							(*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

//MODER
#define GPIOA_MODER_OFFSET	(0x00UL)
#define GPIOA_MODER_E				(*(volatile unsigned int *) (GPIOA_BASE + GPIOA_MODER_OFFSET))

//ODR
#define ODR_OFFSET						(0x14UL)
#define GPIOA_ODR_E						(*(volatile unsigned int *)(GPIOA_BASE + ODR_OFFSET))
#define __IO         volatile

/*typedef struct
{
	__IO uint32_t    DUMMY[20];
	__IO uint32_t    AHB1ENR;
}RCC_typedeg;
typedef struct
{
	__IO uint32_t    MODER;
	__IO uint32_t    DUMMY[4];
    __IO uint32_t    ODR;
}GPIOA_typedef;*/

//ENABLE PROCESS
#define GPIOA_EN  							(1U <<  0)
#define LED_PIN_5								(1U << 5)

#define   RCC              ((RCC_typedef *)(RCC_BASE	)
#define  GPIOA			((GPIOA_typedef *)(GPIOA_BASE))
void delay();
int main()
{
		AHB1EN_E |= GPIOA_EN;
		GPIOA_MODER_E  |= 0x00000400;
		while(1)
		{
			GPIOA_ODR_E  ^= LED_PIN_5;
			delay();
		}
}

void delay ()
{
	for(int i=0 ; i<1777777; i++);
}
