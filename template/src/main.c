#include "main.h"

/* Use __IO keyword to assign a volatile variable */
/* Use static keyword to ensure the variable will be cleared by program */

static __IO uint32_t uwTimingDelay;
static void Delay(__IO uint32_t nTime);

int main(void)
{
 	/*!< At this stage the microcontroller clock setting is already configured, 
        this is done through SystemInit() function which is called from startup
        files before to branch to application main.
        To reconfigure the default setting of SystemInit() function, 
        refer to system_stm32f4xx.c file */

    	
  	/* The parameter of this is from 0 to 16777215 */
    	/* Setup SysTick to countdown 1ms */
  	SysTick_Config(SystemCoreClock / 1000);

  	/* starup code */
  	/* Insert 100 ms delay */
  	Delay(100);
     
  	/* Infinite loop */
  	while (1)
  	{
		/* main code */
  	}
}

/* Use the parameter to control the time interval you want to set */
void Delay(__IO uint32_t nTime)
{ 
  	uwTimingDelay = nTime;

  	while(uwTimingDelay != 0);
}

/* Interrupt handler function */
void TimingDelay_Decrement(void)
{
  	if (uwTimingDelay != 0x00)
  	{ 
   		uwTimingDelay--;
  	}
}	

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  	/* User can add his own implementation to report the file name and line number,
     	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  	/* Infinite loop */
  	while (1)
  	{
		printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  	}	
}
#endif

