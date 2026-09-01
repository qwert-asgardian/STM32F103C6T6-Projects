#include<stm32f10x.h>
void delay(uint32_t a)
{
		while(a--);
}

	int main(){
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR = 1<<2 | 1<<3;
	
	
	GPIOB -> CRL = 0x00000288;
		
		while(1)
		{
				if(GPIOB -> IDR & (1<<0))
				{
					GPIOB -> ODR |= 1 << 2;
					while(GPIOB -> IDR & (1<<0));
				}
				
				
				if(GPIOB -> IDR & (1<<1))
				{
					GPIOB -> ODR &= ~(1 << 2);
					while(GPIOB -> IDR & (1<<1));
				}
		}
}