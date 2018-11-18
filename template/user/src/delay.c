#include "delay.h"

static __IO uint32_t sysTickCounter = 0;

void SysTick_Init(void)
{
    	/*********************************
	 *SystemFrequency/1000    -> 1ms *  
	 *SystemFrequency/100000  ->10us *
	 *SystemFrequency/1000000 -> 1us *
	 *********************************/
    	while(SysTick_Config(SystemCoreClock / 1000000) != 0)
	{
	    // SysTick interrupt now equals 1us
	}
}

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
