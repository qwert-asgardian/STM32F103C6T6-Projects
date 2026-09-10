#include<stm32f10x.h>

int count=0;

void tmr(){
    if(TIM1->SR & 1<<0) {
        count++;
        TIM1 -> SR &= ~(1<<0);
    }
}

int main(){
    RCC -> CR = 0X83;
    RCC -> APB2ENR = (1 << 2) | (1 << 11);
    GPIOA -> CRL = 0X00000222;
    TIM1 -> ARR = 0X007C;
    TIM1 -> PSC  = 0XF9FF;
    TIM1 -> CR1  = 1 << 0;
    TIM1 -> CNT = 0X0000;
    TIM1 -> SR  = 1 << 0;

    while(1){
        tmr();
        if (count == 1){
            GPIOA -> ODR  |= 1 << 0;
        }
        if (count == 2){
            GPIOA -> ODR  &= ~(1 << 0);
        }
        if (count == 3){
            GPIOA -> ODR  |= 1 << 1;
        }
        if (count == 4){
            GPIOA -> ODR  &= ~(1 << 1);
        }
        if (count == 5){
            GPIOA -> ODR  |= 1 << 2;
        }
        if (count == 6){
            GPIOA -> ODR  &= ~(1 << 2);
            count = 0;
        }
    }
}