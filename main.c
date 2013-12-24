#ifdef __cplusplus
 extern "C" {
#endif

//******************************************************************************
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "discoveryf4utils.h"
#include "uart_IRQ.h"
#include "xprintf.h"
//******************************************************************************

//******************************************************************************
int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	   this is done through SystemInit() function which is called from startup
	   file (startup_stm32f4xx.s) before to branch to application main.
	   To reconfigure the default setting of SystemInit() function, refer to
	   system_stm32f4xx.c file
	 */
	uint32_t i = 0;
	uint16_t size = 0;
	uint8_t data[0xff];
	
	STM_EVAL_LEDInit(LED_BLUE);
	STM_EVAL_LEDInit(LED_GREEN);
	STM_EVAL_LEDInit(LED_ORANGE);
	STM_EVAL_LEDInit(LED_RED);
	
	UART_Configuration();
	
	//for(i=0;i<0x00FFFFFF;++i){__NOP();};

	while(1) /* Infinite loop */
	{
		//STM_EVAL_LEDToggle(LED_BLUE);
		//STM_EVAL_LEDToggle(LED_GREEN);
		//STM_EVAL_LEDToggle(LED_ORANGE);
		//STM_EVAL_LEDToggle(LED_RED);
		//for(i=0;i<0x00FFFFFF;++i){__NOP();};

		size = UART_ReceiveBuf(data);
		if( size > 0 )
		{
			UART_TransmitBuf(size,data);
			STM_EVAL_LEDToggle(LED_GREEN);
		}
	}
}
//******************************************************************************


#ifdef __cplusplus
}
#endif
