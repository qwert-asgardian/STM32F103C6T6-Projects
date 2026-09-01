#include <stm32f10x.h>

void delay(unsigned int a) {
    while(a--);
}

int main(void) {
    unsigned char arr[10] = {
        0x3F,0x06,0x5B,0x4F,0x66,
        0x6D,0x7D,0x07,0x7F,0x6F
    };

    int count = 0;
    int i;

    RCC->APB2ENR |= (1 << 2) | (1 << 3);

    GPIOB->CRL = 0x22222222;
    GPIOB->CRH = 0x22222222;

    while (1) {
        int num1 = count;
        int num2 = 9999 - count;

        int digits[8];
        digits[0] = (num1 / 1000) % 10;
        digits[1] = (num1 / 100)  % 10;
        digits[2] = (num1 / 10)   % 10;
        digits[3] = num1 % 10;
        digits[4] = (num2 / 1000) % 10;
        digits[5] = (num2 / 100)  % 10;
        digits[6] = (num2 / 10)   % 10;
        digits[7] = num2 % 10;

        for (i = 0; i < 8; i++) {
            GPIOB->BSRR = 0xFF00;
            GPIOB->ODR = (GPIOB->ODR & ~0x00FF) | arr[digits[i]];
            GPIOB->BRR = (1 << (8 + i));
            delay(1000);
        }

        count++;
        if (count > 9999) count = 0;
    }
}