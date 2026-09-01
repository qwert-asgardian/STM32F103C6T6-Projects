#include<stm32f10x.h>

void delay(uint32_t a){
		while(a--);
}

int main(){
		int count = 7; int a = 0;
		RCC -> CR = 0x00000083;
		RCC -> APB2ENR = (1 << 2);
	
		GPIOA -> CRL = 0x22222222;
		
		while(1)
		{
			for(int i = 0; i <8 ; i++)
			{
					GPIOA -> ODR = (1 << i) | a;
					delay(70000);
			}
			
			a|= 1<<count--;
			if(count == 0)
				{
					for(int i=0;i<8;i++){
							GPIOA -> ODR &= ~(1<<i);
						delay(70000);
					}
					a = 0; count = 7;
				}
			}
			
				return 0;
		}
	