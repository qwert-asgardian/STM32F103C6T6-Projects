#include<stm32f10x.h>

void delay(uint32_t a)
{
		while(a--);
}

int main(){
	unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR |= 1 << 2;

	
	GPIOA -> CRL = 0x22222222;
	GPIOA -> CRH = 0x00000022;
	
	int i=0,j=0;
	
	while(1)
	{
		for(i=0; i<100; i++)
		{
			for(j=0;j<10;j++){
				GPIOA->ODR = arr[i/10] | (1<<8);
				delay(5000);
				GPIOA->ODR = 0;
				
				GPIOA -> ODR = arr[i%10] | (1<<9);
				delay(5000);
				GPIOA->ODR = 0;
				
			}			
		}
	}
}
