#include "LPC13Uxx.h"

volatile uint32_t msTicks = 0; // counter for 1ms SysTicks

//====================================================================================
void main()
{
	uint32_t timer_mark;

	// Enable GPIO Clock ( powers the GPIO peripheral )
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	// Select GPIO Mode and disable analog mode, refer to User Manual - UM10524
	LPC_IOCON->PIO0_1 = 0;

	// Set the pin direction, set high for an output
	LPC_GPIO->DIR[0] |= 1<<1;
	
	// Init SysTick
	SysTick_Config(SystemCoreClock / 1000);				// Generate interrupt every 1 ms
	
	for(;;)
	{
		timer_mark = msTicks;					// Take timer snapshot 
		while(msTicks < (timer_mark + 1000));	// Wait until 100ms has passed
		LPC_GPIO->NOT[0] = 1<<1;
	}
}

//====================================================================================
void SysTick_Handler(void)
{
	msTicks++;
}
