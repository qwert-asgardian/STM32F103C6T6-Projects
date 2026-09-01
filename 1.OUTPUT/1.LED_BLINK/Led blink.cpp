#include<stm32f10x.h>
int delay(uint32_t a){
	while(a--);
}

int main(){
	RCC -> CR = 0x00000083;
	RCC -> APB2ENR = 1<<2 | 1<<3;
	
	GPIOA -> CRL = 0x00000002;
	GPIOB -> CRL = 0x00000008;
	
	/*int led_state = 0;
	while(1){
	if(GPIOB -> IDR & (1<<0)){
			led_state = !led_state;
			while(GPIOB -> IDR & (1<<0)){}
}
	
	if(led_state){
			GPIOA -> ODR |= 1<<0;
	}
	else{
		GPIOA -> ODR &= ~(1<<0);
	}
}
}*/
	while(1){
			if(GPIOB -> IDR & 1<<0){
					delay(10000);
				  if (GPIOB -> IDR & 1<<0){
							GPIOA -> ODR ^= 1<<0;
							while(GPIOB -> IDR & 1<<0){}
							}
					}
			}
	}

	
	