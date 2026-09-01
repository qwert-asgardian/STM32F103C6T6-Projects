#include <stm32f10x.h>

#define RS_HIGH() (GPIOA->BSRR = (1<<8))
#define RS_LOW()  (GPIOA->BRR  = (1<<8))

#define EN_HIGH() (GPIOA->BSRR = (1<<9))
#define EN_LOW()  (GPIOA->BRR  = (1<<9))

void delay(unsigned int d)
{
    while(d--);
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

    // Upper nibble
    GPIOA->ODR &= ~0x0F;
    GPIOA->ODR |= ((value & 0xF0) >> 4);
    enable();

    // Lower nibble
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
    RCC->APB2ENR |= (1<<2);      // Enable GPIOA clock

    GPIOA->CRL = 0x00002222;     // PA0-PA3 output
    GPIOA->CRH = 0x00000022;     // PA8, PA9 output

    delay(50000);                // LCD power-up delay

    lcd(0,0x02);                 // 4-bit mode
    lcd(0,0x28);                 // 2 lines, 5x8
    lcd(0,0x0C);                 // Display ON
    lcd(0,0x06);                 // Cursor increment
    lcd(0,0x01);                 // Clear display

    delay(5000);

    str("HELLO!");

    while(1)
    {
    }
}