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
	GPIOB -> CRL = 0x02222888;
	
	while(1){
			GPIOB -> ODR &= ~0x78; // clears all rows
			GPIOB -> ODR |= 1<<3 ; //sets particular row
//ROW1
			if(GPIOB -> IDR & 1 << 0){
					delay(100);
					GPIOA -> ODR = arr[1];
					while(GPIOB -> IDR & 1 << 0);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 1){
					delay(100);
					GPIOA -> ODR = arr[2];
					while(GPIOB -> IDR & 1 << 1);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 2){
					delay(100);
					GPIOA -> ODR = arr[3];
					while(GPIOB -> IDR & 1 << 2);
					delay(100);
			}
//ROW2
			GPIOB -> ODR &= ~0x78; // clears all rows
			GPIOB -> ODR |= 1<<4 ; //sets particular row

			if(GPIOB -> IDR & 1 << 0){
					delay(100);
					GPIOA -> ODR = arr[4];
					while(GPIOB -> IDR & 1 << 0);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 1){
					delay(100);
					GPIOA -> ODR = arr[5];
					while(GPIOB -> IDR & 1 << 1);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 2){
					delay(100);
					GPIOA -> ODR = arr[6];
					while(GPIOB -> IDR & 1 << 2);
					delay(100);
			}
//ROW3
		GPIOB -> ODR &= ~0x78; // clears all rows
			GPIOB -> ODR |= 1<<5 ; //sets particular row

			if(GPIOB -> IDR & 1 << 0){
					delay(100);
					GPIOA -> ODR = arr[7];
					while(GPIOB -> IDR & 1 << 0);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 1){
					delay(100);
					GPIOA -> ODR = arr[8];
					while(GPIOB -> IDR & 1 << 1);
					delay(100);
			}
			
			if(GPIOB -> IDR & 1 << 2){
					delay(100);
					GPIOA -> ODR = arr[9];
					while(GPIOB -> IDR & 1 << 2);
					delay(100);
			}
//ROW4
			GPIOB -> ODR &= ~0x78; // clears all rows
			GPIOB -> ODR |= 1<<6 ; //sets particular row
			
			if(GPIOB -> IDR & 1 << 1){
					delay(100);
					GPIOA -> ODR = arr[0];
					while(GPIOB -> IDR & 1 << 1);
					delay(100);
			}
	}
}
