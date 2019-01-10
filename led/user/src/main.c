#include "main.h"

int main(void)
{
    	/* __IO keyword is volatile symbol. You can find this definition in Core_cm3.h */
    	
    	static __IO uint16_t time = 100;
 	
	/*!< At this stage the microcontroller clock setting is already configured, 
        this is done through SystemInit() function which is called from startup
        files before to branch to application main.
        To reconfigure the default setting of SystemInit() function, 
        refer to system_stm32f4xx.c file */
	
    	// Enable GPIOF clock from AHB1 
    	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	// Initialize the delay time for 1us 
	SysTick_Init();
	
	// Setup led to push-pull mode and pull-up resistor
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	// delay 2s for startup 
	delay_nms(2000);

     	static uint8_t cnt = 0, i , j;
  	/* Infinite loop */
  	while (1)
  	{
		/* main code here */
	    	
	    	// if cnt is equal to 11, set it to zero
	    	// 0x0b is 11 in hex format
	    	if((cnt & 0x0b) == 0x0b )
		{
		    	cnt = 0;
		}else
		{
			cnt++;
		}
		
		// Attention: GPIO_ResetBits() will turn on led because the led is connect to pull-up resistor
		// Attention: GPIO_SetBits() will turn of led because the led is connect to pull-up resistor
		for(i = 0; i < cnt; i++)
		{
	    		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
			delay_nms(time);	
	    		GPIO_SetBits(GPIOF, GPIO_Pin_9);
			delay_nms(time);	   
		}
		for(j = 0; j < cnt; j++)
		{
		    	GPIO_ResetBits(GPIOF, GPIO_Pin_10);
			delay_nms(time);	
	    		GPIO_SetBits(GPIOF, GPIO_Pin_10);
			delay_nms(time);
		}
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

