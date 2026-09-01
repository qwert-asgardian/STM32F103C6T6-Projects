#include <stm32f10x.h>              // Include STM32F10x microcontroller header file
int loop = 0;
int delay(uint32_t a)               // Create a software delay function
{
    while(a--);                     // Decrease 'a' until it becomes zero
}
int main()                          // Main program starts here
{
    RCC->CR = 0x00000083;           // Configure RCC Clock Control Register
    RCC->CFGR = 0x00000000;         // Configure system clock and bus prescalers
    RCC->APB2ENR = 0x0000001C;      // Enable clock for GPIOA, GPIOB and GPIOC
                                    // Bit 2 = GPIOA clock
                                    // Bit 3 = GPIOB clock
                                    // Bit 4 = GPIOC clock
    GPIOA->CRL = 0x22222222;        // Configure PA0-PA7 as 2 MHz push-pull outputs
    GPIOA->CRH = 0x22222222;        // Configure PA8-PA15 as 2 MHz push-pull outputs
    GPIOB->CRL = 0x22222228;        // Configure PB0-PB7 as 2 MHz push-pull outputs // PB0 - INPUT
    GPIOB->CRH = 0x22222222;        // Configure PB8-PB15 as 2 MHz push-pull outputs
    GPIOC->CRH = 0x22200000;        // Configure PC13, PC14 and PC15 as outputs
                                    // PC8-PC12 remain in their default input configuration
    while(1)                        // Infinite loop: program runs continuously
    {
				if(GPIOB->IDR & 1 << 0)
				{
					loop = 1;
				}
				if(loop == 1){
        GPIOA->ODR = 0x0000FFFF;    // Set PA0-PA15 HIGH
        GPIOB->ODR = 0x0000FFFE;    // Set PB0-PB15 HIGH
        GPIOC->ODR = 0x0000E000;    // Set PC13, PC14 and PC15 HIGH
        delay(100000);              // Wait for some time
        GPIOA->BRR = 0x0000FFFF;    // Reset PA0-PA15 to LOW
        GPIOB->BRR = 0x0000FFFE;    // Reset PB0-PB15 to LOW
        GPIOC->BRR = 0x0000E000;    // Reset PC13, PC14 and PC15 to LOW
        delay(100000);              // Wait for some time before repeating
				}
		}	
}