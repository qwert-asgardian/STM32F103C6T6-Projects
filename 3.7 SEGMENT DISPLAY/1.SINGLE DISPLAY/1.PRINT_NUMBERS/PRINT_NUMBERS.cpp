#include<stm32f10x.h>

void delay(uint32_t a)
{
		while(a--);
}

int main(){
	unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR = 1 << 2;
	
	GPIOA -> CRL = 0x22222222;
	while(1){
		for(int i = 0; i < 10 ; i++){
			GPIOA -> ODR = arr[i];
			delay(70000);
			
		}
		
	}
}
	