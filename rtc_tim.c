#include "rtc_tim.h"

#include "discoveryf4utils.h"
#include "xprintf.h"
#include "uart_IRQ.h"

volatile time_t UnixTime;

void EnableTimerInterrupt( void )
{
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = RTC_TIM_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void InitializeTimerRTC( void )
{
	RCC_ClocksTypeDef RCC_Clocks;
    TIM_TimeBaseInitTypeDef timerInitStructure; 
	
    RCC_RTC_TIM_CLK_INIT(RCC_RTC_TIM_CLK, ENABLE);
	RCC_GetClocksFreq(&RCC_Clocks);
	xprintf2("RCC_Clocks.SYSCLK_Frequency = %ld\n",RCC_Clocks.SYSCLK_Frequency);
	
    timerInitStructure.TIM_Prescaler = ((RCC_Clocks.SYSCLK_Frequency/2)/10000) - 1; // TIM_Prescaler + 1
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 10000;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(RTC_TIM, &timerInitStructure);
	
	EnableTimerInterrupt();
	TIM_ITConfig(RTC_TIM, TIM_IT_Update, ENABLE);
	
    TIM_Cmd(RTC_TIM, ENABLE);
}

void RTC_TIM_IRQHandler( void )
{
	
    if (TIM_GetITStatus(RTC_TIM, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(RTC_TIM, TIM_IT_Update);
		STM_EVAL_LEDToggle(LED_ORANGE);
		UnixTime ++;
	}
}

void SetRTC( time_t SetUnixTime )
{
	UnixTime = SetUnixTime;
}

time_t GetRTC( void )
{
	return UnixTime;
}

void PrintTime( void )
{
    char logtime[0xff];
	strftime(logtime,0xff,"\n\r/%Y.%m.%d %T ",(const void *)localtime((const time_t*)&UnixTime));
	UART_TransmitLine( logtime );
}
