#include<stm32f10x.h>

void delay(uint32_t a)
{
	while(a--);
}

void enable()
{
	GPIOC->BSRR = 1<<14;
	delay(1000);
	GPIOC->BRR = 1<<14;
	delay(1000);
}	

void lcd(char rs,unsigned char value)
{	
	if(rs){
		GPIOC->BSRR = 1<<15;
	}
	else{
		GPIOC->BRR = 1<<15;
	}
	GPIOA->ODR &= ~0x0F;
	GPIOA -> ODR |= (value & 0xF0) >> 4;
	enable();
	GPIOA->ODR &= ~0x0F;
	GPIOA -> ODR |= (value & 0x0F);
	enable();
}

	void str(char *ptr)
	{
		while(*ptr != '\0'){
			lcd(1,*ptr++);
		}	
	}

int main()
{
	unsigned char arr[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	int h,m,s,d;
	uint16_t digit = 0xF0;
	
	RCC-> CR = 0x00000083;
	RCC-> APB2ENR |= 1<<2 | 1<<3 | 1<<4;
	GPIOA -> CRL = 0x08882222;
	GPIOA->ODR &= ~((1<<4)|(1<<5)|(1<<6));
	GPIOB -> CRL = 0x22222222;
	GPIOB -> CRH = 0x22222222;
	GPIOA -> CRH = 0x00222222;
	GPIOC -> CRH = 0x22000000;
	
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0C);
	lcd(0,0x01);
	lcd(0,0x80);
	
	int run = 0;

while(1)
{
    if(GPIOA->IDR & (1<<4))
        run = 1;

    if(GPIOA->IDR & (1<<5))
        run = 0;

    if(GPIOA->IDR & (1<<6))
    {
        h = m = s = 0;
        run = 0;
    }
		if(run){
			for(h = 0; h < 24; h++){
				for(m = 0; m < 60; m++){
					for(s = 0; s < 60; s++){
						for(d=0;d < 2; d++){
							if((GPIOA-> IDR & (1<<6))){
									h=0;m=0;s=0;
									lcd(0,0x01);
									str("RESET");
									delay(100);
									break;
						}
					lcd(0,0XC8);
					GPIOB -> ODR = (0x3F00 & ~(1<<8)) | arr[h/10];
					delay(10);
					lcd(1,(h/10) + '0');
					GPIOB -> ODR = (0x3F00 & ~(1<<9)) | arr[h%10];
					delay(10);
					lcd(1,(h%10) + '0');
					lcd(1,':');
					GPIOB -> ODR = (0x3F00 & ~(1<<10)) | arr[m/10];
					delay(10);
					lcd(1,(m/10) + '0');
					GPIOB -> ODR = (0x3F00 & ~(1<<11)) | arr[m%10];
					delay(10);
					lcd(1,(m%10) + '0');
					lcd(1,':');
					GPIOB -> ODR = (0x3F00 & ~(1<<12)) | arr[s/10];
					delay(10);
					lcd(1,(s/10) + '0');
					GPIOB -> ODR = (0x3F00 & ~(1<<13)) | arr[s%10];
					delay(10);
					lcd(1,(s%10) + '0');
				}
				}
				}
			}
		}	
}
}

