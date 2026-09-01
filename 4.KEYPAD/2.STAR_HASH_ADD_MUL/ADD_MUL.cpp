#include <stm32f10x.h>

void delay(uint32_t a)
{
    while(a--);
}

void display(int num, unsigned char arr[])
{
    int d1,d2,d3,d4;

    d1 = (num/1000)%10;
    d2 = (num/100)%10;
    d3 = (num/10)%10;
    d4 = num%10;

    GPIOB->ODR &= ~0x0F;
    GPIOA->ODR = (GPIOA->ODR & ~0xFF) | arr[d1];
    GPIOB->ODR |= (1<<0);
    delay(1000);

    GPIOB->ODR &= ~0x0F;
    GPIOA->ODR = (GPIOA->ODR & ~0xFF) | arr[d2];
    GPIOB->ODR |= (1<<1);
    delay(1000);

    GPIOB->ODR &= ~0x0F;
    GPIOA->ODR = (GPIOA->ODR & ~0xFF) | arr[d3];
    GPIOB->ODR |= (1<<2);
    delay(1000);

    GPIOB->ODR &= ~0x0F;
    GPIOA->ODR = (GPIOA->ODR & ~0xFF) | arr[d4];
    GPIOB->ODR |= (1<<3);
    delay(1000);
}

int main()
{
    unsigned char arr[10] =
    {
        0x3F,0x06,0x5B,0x4F,0x66,
        0x6D,0x7D,0x07,0x7F,0x6F
    };

    RCC->CR |= 0x00000001;
    while(!(RCC->CR & 0x00000002));

    RCC->APB2ENR |= (1<<2) | (1<<3);

    GPIOA->CRL = 0x22222222;

    GPIOB->CRL = 0x08882222;
    GPIOB->CRH = 0x00002222;

    /* PB4 PB5 PB6 = input pulldown */
    GPIOB->ODR &= ~((1<<4)|(1<<5)|(1<<6));

    int a = 0;
    int add = 0;
    int mul = 0;
    int mode = 1;

    while(1)
    {
        /* ---------- ROW A ---------- */
        GPIOB->ODR &= ~0x0F00;
        GPIOB->ODR |= (1<<8);
        delay(1000);

        if(GPIOB->IDR & (1<<4))
        {
            delay(50000);
            a = (a%1000)*10 + 1;
            mode = 1;
            while(GPIOB->IDR & (1<<4));
        }

        if(GPIOB->IDR & (1<<5))
        {
            delay(50000);
            a = (a%1000)*10 + 2;
            mode = 1;
            while(GPIOB->IDR & (1<<5));
        }

        if(GPIOB->IDR & (1<<6))
        {
            delay(50000);
            a = (a%1000)*10 + 3;
            mode = 1;
            while(GPIOB->IDR & (1<<6));
        }

        display((mode==1)?a:(mode==2)?add:mul,arr);

        /* ---------- ROW B ---------- */
        GPIOB->ODR &= ~0x0F00;
        GPIOB->ODR |= (1<<9);
        delay(1000);

        if(GPIOB->IDR & (1<<4))
        {
            delay(50000);
            a = (a%1000)*10 + 4;
            mode = 1;
            while(GPIOB->IDR & (1<<4));
        }

        if(GPIOB->IDR & (1<<5))
        {
            delay(50000);
            a = (a%1000)*10 + 5;
            mode = 1;
            while(GPIOB->IDR & (1<<5));
        }

        if(GPIOB->IDR & (1<<6))
        {
            delay(50000);
            a = (a%1000)*10 + 6;
            mode = 1;
            while(GPIOB->IDR & (1<<6));
        }

        display((mode==1)?a:(mode==2)?add:mul,arr);

        /* ---------- ROW C ---------- */
        GPIOB->ODR &= ~0x0F00;
        GPIOB->ODR |= (1<<10);
        delay(1000);

        if(GPIOB->IDR & (1<<4))
        {
            delay(50000);
            a = (a%1000)*10 + 7;
            mode = 1;
            while(GPIOB->IDR & (1<<4));
        }

        if(GPIOB->IDR & (1<<5))
        {
            delay(50000);
            a = (a%1000)*10 + 8;
            mode = 1;
            while(GPIOB->IDR & (1<<5));
        }

        if(GPIOB->IDR & (1<<6))
        {
            delay(50000);
            a = (a%1000)*10 + 9;
            mode = 1;
            while(GPIOB->IDR & (1<<6));
        }

        display((mode==1)?a:(mode==2)?add:mul,arr);

        /* ---------- ROW D ---------- */
        GPIOB->ODR &= ~0x0F00;
        GPIOB->ODR |= (1<<11);
        delay(1000);

        if(GPIOB->IDR & (1<<4))
        {
            delay(50000);
            add = (a/100) + (a%100);
            mode = 2;
            while(GPIOB->IDR & (1<<4));
        }

        if(GPIOB->IDR & (1<<5))
        {
            delay(50000);
            a = (a%1000)*10;
            mode = 1;
            while(GPIOB->IDR & (1<<5));
        }

        if(GPIOB->IDR & (1<<6))
        {
            delay(50000);
            mul = (a/100) * (a%100);
            mode = 3;
            while(GPIOB->IDR & (1<<6));
        }

        int value;

if(mode==1)
{
    value=a;
}
else if(mode==2)
{
    value=add;
}
else
{
    value=mul;
}

display(value,arr);
    }
}