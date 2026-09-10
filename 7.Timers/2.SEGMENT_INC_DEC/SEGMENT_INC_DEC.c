#include<stm32f10x.h>
int count=0;
int arr[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};


void tmr()
{
    if(TIM1->SR & (1<<0))
    {
        TIM1->SR &= ~(1<<0);
				count++;	
		}
}


	
int main(){
	
	RCC -> CR = 0X83;
	RCC ->APB2ENR = 1<< 2 | 1<<11;
	GPIOA -> CRL = 0X22222222;

	TIM1 -> PSC  = 0X1F3F;
  TIM1 -> CR1  = 1 << 0;
  TIM1 -> CNT = 0X0000;
  TIM1 -> SR  = 0;
	 
	while(1){
		while(count < 10){
			TIM1 -> ARR = 0X4AF;
			GPIOA -> ODR = arr[count];
			tmr();
	}
		count = 0;
	
		while(count < 10){
			TIM1 -> ARR = 0X3E7;
			GPIOA -> ODR = arr[9 - count];
			tmr();
		}
		count = 0;
}
	}

	
