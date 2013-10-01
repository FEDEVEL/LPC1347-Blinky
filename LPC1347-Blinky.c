//#define TARGET_LPC13XX

#include "LPC13xx.h"
#include "system_LPC13xx.h"

volatile uint32_t msTicks = 0; // counter for 1ms SysTicks


//====================================================================================
void main()
{
	uint32_t timer_mark;
	
	SystemInit();
	
	// Init on-board LED as output
	LPC_GPIO0->DIR |= 1 << 7;
	
	// Init SysTick
	SysTick_Config(SystemCoreClock / 1000);				// Generate interrupt every 1 ms
	
	for (;;)
	{
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		LPC_GPIO0->DATA &= ~(1 << 7);				// Turn the LED off
	
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 100));	// Wait until 100ms has passed
		LPC_GPIO0->DATA |= (1 << 7);				// Turn the LED on
	}
}

//====================================================================================
void SysTick_Handler(void)
{
	msTicks++;
}
