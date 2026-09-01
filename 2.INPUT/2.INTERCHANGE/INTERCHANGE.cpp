#include <stm32f10x.h>

int main()
{
    RCC->CR = 0x00000083;
    RCC->APB2ENR |= (1 << 3); 
    GPIOB->CRL = 0x00002888;
		int reverse = 0

    while(1)
    {
        if(GPIOB->IDR & (1 << 0))
        {
            if(reverse){
                GPIOB->ODR &= ~(1 << 3);
						}
            else{
                GPIOB->ODR |= (1 << 3);
						}
            while(GPIOB->IDR & (1 << 0));
        }

        if(GPIOB->IDR & (1 << 1))
        {
            if(reverse)
                GPIOB->ODR |= (1 << 3);
            else
                GPIOB->ODR &= ~(1 << 3);

            while(GPIOB->IDR & (1 << 1));
        }

        if(GPIOB->IDR & (1 << 2))
        {
            reverse = !reverse ;
						while(GPIOB->IDR & (1 << 2));
				}
			}
		}
	
