#include<stm32f10x.h>
void delay(uint32_t a)
{
		while(a--);
}

	int main(){
		unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
		int size = sizeof(arr) / sizeof(arr[0]);
		int count=0 , i;
		RCC -> CR = 0x00000083;
		RCC -> APB2ENR = 1<<2 | 1<<3;
		
		GPIOA-> CRL = 0x22222222;
		GPIOB -> CRL = 0x00002888;
		
		while(1)
		{
				if(GPIOB -> IDR & (1 << 0)){
						count++;
						if(count > 9){
                    count = 0;
                }
						while(GPIOB -> IDR & (1 << 0));
				}
				GPIOA -> ODR = arr[count];
				
				if(GPIOB -> IDR & (1 << 1)){
						count--;
						if(count < 0){
                    count = 9;
						}
						while(GPIOB -> IDR & (1 << 1));
				}
				GPIOA -> ODR = arr[count];
				
				if(GPIOB -> IDR & (1 << 2)){
						GPIOB -> ODR |= 1<<3;
						for(i=count ; i >= 0; i--){
								GPIOA -> ODR = arr[i];
								delay(100000);
						}
						delay(10000);
						GPIOB -> ODR  &= ~(1<<3);
						count = 0;
		}		
	}
}		
			