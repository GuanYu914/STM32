#include "main.h"

int main(void)
{
 	/*!< At this stage the microcontroller clock setting is already configured, 
        this is done through SystemInit() function which is called from startup
        files before to branch to application main.
        To reconfigure the default setting of SystemInit() function, 
        refer to system_stm32f4xx.c file */
	
	// Initialize the delay time for 1us 
	SysTick_Init();
	
	// delay 100ms for startup 
	delay_nms(100);
     
  	/* Infinite loop */
  	while (1)
  	{
		/* main code */
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

