#include <stm32f10x.h>

void tmr();
void led1();
void led2();
void led3();
void update_digit1();
void update_digit2();
void segment();

int i, j, k;
int count = 0;
int led1_counter = 0;
int led2_counter = 0;
int led3_counter = 0;
int digit1_counter = 0;
int digit2_counter = 0;
int led1_state = 0;
int led2_state = 0;
int led3_state = 0;
int led3_ontime = 5;
int led3_offtime = 2;
int digit1_value = 9;
int digit2_value = 0;
int mux = 0;
int arr[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void tmr()
{
    if (TIM1->SR & (1 << 0))
    {
        TIM1->SR &= ~(1 << 0);
        led1_counter++;
        led2_counter++;
        led3_counter++;
        digit1_counter++;
        digit2_counter++;
    }
}

void update_digit1()
{
    if (digit1_counter >= 10)
    {
        digit1_counter = 0;
        digit1_value--;
        if (digit1_value < 0)
            digit1_value = 9;
    }
}

void update_digit2()
{
    if (digit2_counter >= 20)
    {
        digit2_counter = 0;
        digit2_value++;
        if (digit2_value > 9)
            digit2_value = 0;
    }
}

void led1()
{
    if (led1_counter >= 4)
    {
        led1_counter = 0;
        led1_state = !led1_state;
        if (led1_state)
        {
            GPIOB->BRR = 1 << 0;
        }
        else
        {
            GPIOB->BSRR = 1 << 0;
        }
    }
}

void led2()
{
    if (led2_state)
    {
        if (led2_counter >= 8)
        {
            led2_counter = 0;
            led2_state = 0;
            GPIOB->BSRR = 1 << 1;
        }
    }
    else
    {
        if (led2_counter >= 3)
        {
            led2_counter = 0;
            led2_state = 1;
            GPIOB->BRR = 1 << 1;
        }
    }
}

void led3()
{
    if (led3_state)
    {
        if (led3_counter >= led3_ontime)
        {
            led3_counter = 0;
            led3_state = 0;
            GPIOB->BSRR = 1 << 2;
        }
    }
    else
    {
        if (led3_counter >= led3_offtime)
        {
            led3_counter = 0;
            led3_state = 1;
            GPIOB->BRR = 1 << 2;
            led3_ontime += 8;
            led3_offtime += 3;
        }
    }
}

void segment()
{
    if (mux == 0)
    {
        GPIOA->BRR = 1 << 9;
        GPIOA->ODR = (GPIOA->ODR & 0xFF00) | arr[digit1_value];
        GPIOA->BSRR = 1 << 8;
        mux = 1;
    }
    else
    {
        GPIOA->BRR = 1 << 8;
        GPIOA->ODR = (GPIOA->ODR & 0xFF00) | arr[digit2_value];
        GPIOA->BSRR = 1 << 9;
        mux = 0;
    }
}

int main()
{
    RCC->CR = 0x83;
    RCC->CFGR = 0;
    RCC->APB2ENR = (1 << 2) | (1 << 3) | (1 << 11);

    GPIOA->CRL = 0x22222222;
    GPIOA->CRH = 0x00000022;
    GPIOB->CRL = 0x00000222;
    GPIOB->BSRR = (1 << 0) | (1 << 1) | (1 << 2);

    TIM1->PSC = 0x1F3F;
    TIM1->ARR = 0x0063;
    TIM1->CR1 = 1 << 0;
    TIM1->CNT = 0;
    TIM1->SR = 0;

    while (1)
    {
        tmr();
        led1();
        led2();
        led3();
        update_digit1();
        update_digit2();
        segment();
    }
}