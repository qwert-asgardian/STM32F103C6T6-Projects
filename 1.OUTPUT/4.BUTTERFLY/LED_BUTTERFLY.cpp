#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}

int main()
{
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR = 1 << 2 | 1 << 3;
	
	GPIOA -> CRL = 0x22222222;
	GPIOB -> CRL = 0x22222222;
	int i = 0;
	while(1)
	{
		for(i=0;i<8;i++)
		{
			if(i == 4){
				delay(100000);
			}
			GPIOA ->ODR |= 1 << i;
			
		}
		delay(100000);
		
		for(i=0;i<8;i++)
		{
			if(i == 4){
				delay(100000);
			}
			GPIOB ->ODR |= 1 << i;
			
		}
		delay(100000);
		
		for(i=7;i>3;i--)
		{
			GPIOB ->ODR &= ~(1 << i);
		}
		delay(100000);
		
	for(i=3;i>=0;i--)
		{
			GPIOB ->ODR &= ~(1 << i);
		}
		delay(100000);
		
			
		for(i=7;i>3;i--)
		{
			GPIOA ->ODR &= ~(1 << i);
		}
		delay(100000);
		
	for(i=3;i>=0;i--)
		{
			GPIOA ->ODR &= ~(1 << i);
		}
		delay(100000);
	}
}