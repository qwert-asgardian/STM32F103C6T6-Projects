#include<stm32f10x.h>

void delay(uint32_t a)
{
		while(a--);
}

int main(){
	unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR = 1 << 2 | 1 << 3;

	
	GPIOA -> CRL = 0x22222222;
	GPIOB -> CRL = 0x00002222;
	
	int i=0,j=0,k=0;
	
	while(1)
	{
		for(i=0; i<100; i++)
		{
			k = 99-i;
			for(j=0;j<10;j++){
				GPIOB -> ODR |= 1<<0;
				GPIOA->ODR = arr[(i/10) % 10] ;
				delay(1000);
				GPIOA->ODR = 0;
				GPIOB->ODR = 0;
				
				
				GPIOB -> ODR |= 1<<1;
				GPIOA -> ODR = arr[i % 10] ;
				delay(1000);
				GPIOA->ODR = 0;
				GPIOB->ODR = 0;
				
				GPIOB -> ODR |= 1<<2;
				GPIOA -> ODR = arr[(k/10) % 10]  ;
				delay(1000);
				GPIOA->ODR = 0;
				GPIOB->ODR = 0;
			
				GPIOB -> ODR |= 1<<3;
				GPIOA -> ODR = arr[k % 10];
				delay(1000);
				GPIOA->ODR = 0;
  			GPIOB->ODR = 0;

				
			}			
		}
	}
}
