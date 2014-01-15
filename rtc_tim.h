//******************************************************************************
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_TIM_H
#define __RTC_TIM_H

#include "stm32f4xx.h"
#include <time.h>

#define RTC_TIM_TIMER7
	 
#ifdef	RTC_TIM_TIMER2
//===============================================================
#define RTC_TIM                            TIM2
#define RCC_RTC_TIM_CLK                    RCC_APB1Periph_TIM2
#define RCC_RTC_TIM_CLK_INIT               RCC_APB1PeriphClockCmd
#define RTC_TIM_IRQn                       TIM2_IRQn
#define RTC_TIM_IRQHandler                 TIM2_IRQHandler
//===============================================================
#endif

#ifdef	RTC_TIM_TIMER3
//===============================================================
#define RTC_TIM                            TIM3
#define RCC_RTC_TIM_CLK                    RCC_APB1Periph_TIM3
#define RCC_RTC_TIM_CLK_INIT               RCC_APB1PeriphClockCmd
#define RTC_TIM_IRQn                       TIM3_IRQn
#define RTC_TIM_IRQHandler                 TIM3_IRQHandler
//===============================================================
#endif

#ifdef	RTC_TIM_TIMER6
//===============================================================
#define RTC_TIM                            TIM6
#define RCC_RTC_TIM_CLK                    RCC_APB1Periph_TIM6
#define RCC_RTC_TIM_CLK_INIT               RCC_APB1PeriphClockCmd
#define RTC_TIM_IRQn                       TIM6_DAC_IRQn
#define RTC_TIM_IRQHandler                 TIM6_DAC_IRQHandler
//===============================================================
#endif

#ifdef	RTC_TIM_TIMER7
//===============================================================
#define RTC_TIM                            TIM7
#define RCC_RTC_TIM_CLK                    RCC_APB1Periph_TIM7
#define RCC_RTC_TIM_CLK_INIT               RCC_APB1PeriphClockCmd
#define RTC_TIM_IRQn                       TIM7_IRQn
#define RTC_TIM_IRQHandler                 TIM7_IRQHandler
//===============================================================
#endif
 
void InitializeTimerRTC( void );
void SetRTC( time_t SetUnixTime );
time_t GetRTC( void );
void PrintTime( void );

#endif /* __RTC_TIM_H */
//******************************************************************************

