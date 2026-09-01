#include <stm32f10x.h>

#define RS_HIGH() (GPIOA->BSRR = (1<<8))
#define RS_LOW()  (GPIOA->BRR  = (1<<8))

#define EN_HIGH() (GPIOA->BSRR = (1<<9))
#define EN_LOW()  (GPIOA->BRR  = (1<<9))

void delay(unsigned int a)
{
    while(a--);
}

void enable(void)
{
    EN_HIGH();
    delay(1000);
    EN_LOW();
    delay(1000);
}

void lcd(char rs, unsigned char value)
{
    if(rs)
        RS_HIGH();
    else
        RS_LOW();

    GPIOA->ODR &= ~0x0F;
    GPIOA->ODR |= ((value & 0xF0) >> 4);
    enable();

    GPIOA->ODR &= ~0x0F;
    GPIOA->ODR |= (value & 0x0F);
    enable();
}

void str(char *p)
{
    while(*p)
    {
        lcd(1,*p++);
    }
}

int main(void)
{
    int count = 0;

    unsigned char arr[10] =
    {
        0x3F,0x06,0x5B,0x4F,0x66,
        0x6D,0x7D,0x07,0x7F,0x6F
    };

    RCC->APB2ENR |= (1<<2) | (1<<3);

    GPIOA->CRL = 0x00002222;
    GPIOA->CRH = 0x00088222;   // PA11, PA12 input pull-up/pull-down

    GPIOB->CRL = 0x22222222;

    // Enable internal pull-ups on PA11 and PA12
    GPIOA->ODR |= (1<<11) | (1<<12);

    delay(50000);

    lcd(0,0x02);
    lcd(0,0x28);
    lcd(0,0x0C);
    lcd(0,0x06);
    lcd(0,0x01);

    delay(5000);

    lcd(0,0x80);
    str("COUNT:");
    lcd(0,0x86);
    lcd(1,count+'0');

    GPIOB->ODR = arr[count];

    while(1)
    {
        // Increment button on PA11
        if(!(GPIOA->IDR & (1<<11)))
        {
            if(count < 9)
            {
                count++;
            }

            while(!(GPIOA->IDR & (1<<11)));

            GPIOB->ODR = arr[count];

            lcd(0,0x86);
            lcd(1,count+'0');
        }

        // Decrement button on PA12
        if(!(GPIOA->IDR & (1<<12)))
        {
            if(count > 0)
            {
                count--;
            }

            while(!(GPIOA->IDR & (1<<12)));

            GPIOB->ODR = arr[count];

            lcd(0,0x86);
            lcd(1,count+'0');
        }
    }
}