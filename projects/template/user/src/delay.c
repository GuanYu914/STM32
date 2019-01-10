#include "delay.h"

static __IO uint32_t sysTickCounter = 0;

/*SysTick function will produce interrupt when time is equal to the function parameter multiply 
  the cycle of SystemCoreClock. You can't set to the value of function parameter more than 2 to
  the 24th power because the SysTick timer is 24 bit.
 
  Ex. SysTick_Config(SystemCoreClock / 1000000)
  ps. SystemCoreClock is defined in a file named system_stm32f4xx.c. For this, SystemCoreClock is set to 168MHz

      (168000000 / 1000000) * (1 / 168000000) = 10^-6(s) = 1us -> will produce a interrupt 
 */

void SysTick_Init(void)
{
    	/*********************************
	 *SystemCoreClock/1000    -> 1ms *  
	 *SystemCoreClock/100000  ->10us *
	 *SystemCoreClock/1000000 -> 1us *
	 *********************************/
    	while(SysTick_Config(SystemCoreClock / 1000000) != 0)
	{
	    // SysTick interrupt now equals 1us
	}
}

/* This function will be called from SysTick_Handler() */

void TimingDelay_Decrement(void)
{
    	if(sysTickCounter != 0x00)
	{
	    	sysTickCounter--;
	}
}

void delay_nus(u32 n)
{
    	sysTickCounter = n;
	while(sysTickCounter != 0)
	{
	    // wait until sysTickCounter approches zero
	}
}

void delay_1ms(void)
{
    	// 1000us = 1ms
    	sysTickCounter = 1000;
	while(sysTickCounter != 0)
	{

	}
}

void delay_nms(u32 n)
{
	while(n--){
	    delay_1ms();
	}
}
