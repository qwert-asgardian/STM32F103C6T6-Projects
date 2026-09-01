#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int arr[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
int i,j;
int main()
{
	RCC->CR=0X00000083;
	RCC->APB2ENR=0X0C;
	GPIOA->CRL=0X22222222;
	GPIOB->CRL=0X88;//2 PIN INPUT
	while(1)
	{
		if(GPIOB->IDR & 1<<0)
		{
			for(i=0;i<=9;i++)
			{
				GPIOA->ODR=arr[i];
				delay(70000);
				if(i > 9)
				{
					i = 0;
				}
				if(GPIOB->IDR & 1<<1)
			{
				break;
			}

		}
	}
			
		if(GPIOB->IDR & 1<<1)
		{
			for(j=i;j>=0;j--)
			{
				GPIOA->ODR=arr[j];
				delay(70000);
				if(j < 0)
				{
					j = 9;
				}
				if(GPIOB->IDR & 1<<0)
			{
				break;
			}
		
		}
	}
}

}