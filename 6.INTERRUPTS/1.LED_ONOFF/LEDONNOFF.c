#include <stm32f10x.h>

void delay(uint32_t a)
{
    while(a--);
}

// Interrupt Service Routine for EXTI Line 0
// CPU automatically jumps here when EXTI0 interrupt occurs
void EXTI0_IRQHandler(void)
{
    // Verify that EXTI0 generated this interrupt
    if(EXTI->PR & (1<<0))
    {
        GPIOC->BRR  = (1<<13);   // Drive PC13 LOW
        GPIOB->BSRR = (1<<0);    // Set PB0 HIGH (LED ON)
        delay(100000);
        GPIOB->BRR = (1<<0);     // Drive PB0 LOW (LED OFF)
			
        // Clear EXTI0 pending flag 1| EXTI uses "Write 1 to Clear"
        EXTI->PR = (1<<0);
    }
}

int main()
{
    RCC->APB2ENR = (1<<0) | (1<<2) | (1<<3) | (1<<4);
    GPIOA->CRL = 0x00000008;
    GPIOB->CRL = 0x00000002;
    GPIOC->CRH = 0x00200000;

    // Route EXTI0 to PA0
    // EXTI0 can be connected to PA0/PB0/PC0/PD0...
    // 0000 selects PA0
    AFIO->EXTICR[0] = 0x00000000;

    // Unmask EXTI0
    // Allows EXTI0 interrupt requests to reach NVIC
    EXTI->IMR = (1<<0);

    // Disable Falling Edge Trigger
    EXTI->FTSR = 0;

    // Enable Rising Edge Trigger
    // Interrupt occurs when PA0 changes from LOW to HIGH
    EXTI->RTSR = (1<<0);

    // Enable EXTI0 interrupt channel inside NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);

    while(1)
    {
        // Keep PC13 HIGH while waiting for interrupts
        GPIOC->ODR = (1<<13);
    }
}