#include<stm32f10x.h>

void delay(uint32_t a){
		while(a--);
}

int main(){
		RCC -> CR = 0x00000083;
		RCC -> APB2ENR = (1 << 2);
	
		GPIOA -> CRL = 0x22222222;
		
		while(1)
		{
			for(int i = 0; i <8 ; i++)
			{
					GPIOA -> ODR = (1 << i);
					delay(100000);
			}
		}
		return 0;
}
	