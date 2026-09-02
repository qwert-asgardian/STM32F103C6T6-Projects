#include<stm32f10x.h>
void delay(uint32_t a){
	while(a--);
}

void enable(){
		GPIOC-> BSRR = 1 << 14;
		delay(1000);
		GPIOC -> BRR |= 1 << 14;
		delay(1000);
}

void lcd(int rs,int value){
	if(rs){
		GPIOC-> BSRR = 1 << 15;
	}
	else{
		GPIOC -> BRR = 1<< 15;
	}
	GPIOA->ODR &= ~0x0F;
	GPIOA -> ODR |= (value & 0xF0) >> 4;
	enable();
	
	GPIOA->ODR &= ~0x0F;
	GPIOA -> ODR |= (value & 0x0F) ;
	enable();
}

void str(char *ptr){
		while(*ptr != '\0'){
			lcd(1,*ptr++);
		}
}

void EXTI9_5_IRQHandler(void)
{
    if(EXTI->PR & (1<<8))
    {
        GPIOB->BRR  = (1<<0);   // RED OFF
        GPIOB->BRR  = (1<<1);   // YELLOW OFF
        GPIOB->BSRR = (1<<2);   // GREEN ON
        delay(500000);
        EXTI->PR = (1<<8);
    }
}

void EXTI4_IRQHandler(void)
{
    if(EXTI->PR & (1<<4))
    {
        lcd(0,0x01);
        lcd(0,0x80);
        str("GREEN");
        EXTI->PR = (1<<4);
    }
}


int main(){
		unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
		
		RCC -> CR = 0x83;
		RCC -> APB2ENR = 1 << 0 | 1 << 4 | 1 << 2 | 1 << 3;
		
		GPIOA -> CRL = 0x00002222;
		GPIOB -> CRL = 0x00000222;
		GPIOB -> CRH = 0x00000088;
		GPIOC -> CRH = 0x22000000;
		
		AFIO->EXTICR[1] &= ~(0xF << 0);
		AFIO->EXTICR[2] &= ~(0xF << 0);
		AFIO->EXTICR[2] |=  (0x1 << 0);
		EXTI->IMR  |= (1<<4) | (1<<8);
		EXTI->FTSR |= (1<<4) | (1<<8);
		EXTI -> RTSR = 0;
		NVIC_EnableIRQ(EXTI9_5_IRQn);
		
		lcd(0,0x02);
		lcd(0,0x28);
		lcd(0,0x0C);
		lcd(0,0x01);
		lcd(0,0x80);
		
		NVIC_EnableIRQ(EXTI4_IRQn);
		NVIC_EnableIRQ(EXTI9_5_IRQn);
		
		while(1){
			GPIOB -> BSRR = 1 << 0;
			str("RED");
			delay(100000);
			GPIOB -> BRR = 1 <<0;
			lcd(0,0x01);
			lcd(0,0x80);
			
			GPIOB -> BSRR = 1 << 1;
			str("YELLOW");
			delay(100000);
			GPIOB -> BRR = 1 <<1;
			lcd(0,0x01);
			lcd(0,0x80);
			
			GPIOB -> BSRR = 1 << 2;
			str("GREEN");
			delay(100000);
			GPIOB -> BRR = 1 <<2;
			lcd(0,0x01);
			lcd(0,0x80);		
		}
}