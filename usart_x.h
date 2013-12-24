//******************************************************************************
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_X_H
#define __USART_X_H

#ifdef	DBG_USART2
//===============================================================
// TX -> PA2
// RX -> PA3
#define DBG_UART                           USART2
#define RCC_DBG_UART_CLK                   RCC_APB1Periph_USART2
#define RCC_DBG_UART_CLK_INIT              RCC_APB1PeriphClockCmd
#define DBG_UART_IRQn                      USART2_IRQn
#define DBG_UART_IRQHandler                USART2_IRQHandler

#define DBG_UART_GPIO_AF                   GPIO_AF_USART2
#define RCC_DBG_UART_GPIO_CLK              RCC_AHB1Periph_GPIOA
#define RCC_DBG_UART_GPIO_CLK_INIT		   RCC_AHB1PeriphClockCmd

//DMA1 			Stream 5	Stream 6
//Channel 4 -	USART2_RX	USART2_TX
#define RCC_DBG_UART_DMA_CLK               RCC_AHB1Periph_DMA1
#define RCC_DBG_UART_DMA_CLK_INIT          RCC_AHB1PeriphClockCmd
#define DBG_UART_DMA_CHANNEL               DMA_Channel_4
#define DBG_UART_DMA_IT_TC_RX              DMA_IT_TCIF5
#define DBG_UART_DMA_STREAM_RX             DMA1_Stream5
#define DBG_UART_DMA_STREAM_RX_IRQn        DMA1_Stream5_IRQn
#define DBG_UART_DMA_STREAM_RX_IRQHandler  DMA1_Stream5_IRQHandler
#define DBG_UART_DMA_IT_TC_TX              DMA_IT_TCIF6
#define DBG_UART_DMA_STREAM_TX             DMA1_Stream6
#define DBG_UART_DMA_STREAM_TX_IRQn        DMA1_Stream6_IRQn
#define DBG_UART_DMA_STREAM_TX_IRQHandler  DMA1_Stream6_IRQHandler

#define DBG_UART_TX_PIN                    GPIO_Pin_2
#define DBG_UART_TX_GPIO_PORT              GPIOA
#define DBG_UART_TX_SOURCE                 GPIO_PinSource2

#define DBG_UART_RX_PIN                    GPIO_Pin_3
#define DBG_UART_RX_GPIO_PORT              GPIOA
#define DBG_UART_RX_SOURCE                 GPIO_PinSource3

#define DBG_UART_BAUDRATE                  115200
//===============================================================
#endif

#ifdef	DBG_USART3
//===============================================================
// TX -> PD8
// RX -> PD9
#define DBG_UART                           USART3
#define RCC_DBG_UART_CLK                   RCC_APB1Periph_USART3
#define RCC_DBG_UART_CLK_INIT              RCC_APB1PeriphClockCmd
#define DBG_UART_IRQn                      USART3_IRQn
#define DBG_UART_IRQHandler                USART3_IRQHandler

#define DBG_UART_GPIO_AF                   GPIO_AF_USART3
#define RCC_DBG_UART_GPIO_CLK              RCC_AHB1Periph_GPIOD
#define RCC_DBG_UART_GPIO_CLK_INIT		   RCC_AHB1PeriphClockCmd

//DMA1 			Stream 1	Stream 3
//Channel 4 -	USART3_RX	USART3_TX
#define RCC_DBG_UART_DMA_CLK               RCC_AHB1Periph_DMA1
#define RCC_DBG_UART_DMA_CLK_INIT          RCC_AHB1PeriphClockCmd
#define DBG_UART_DMA_CHANNEL               DMA_Channel_4
#define DBG_UART_DMA_IT_TC_RX              DMA_IT_TCIF3
#define DBG_UART_DMA_STREAM_RX             DMA1_Stream3
#define DBG_UART_DMA_STREAM_RX_IRQn        DMA1_Stream3_IRQn
#define DBG_UART_DMA_STREAM_RX_IRQHandler  DMA1_Stream3_IRQHandler
#define DBG_UART_DMA_IT_TC_TX              DMA_IT_TCIF4
#define DBG_UART_DMA_STREAM_TX             DMA1_Stream4
#define DBG_UART_DMA_STREAM_TX_IRQn        DMA1_Stream4_IRQn
#define DBG_UART_DMA_STREAM_TX_IRQHandler  DMA1_Stream4_IRQHandler

#define DBG_UART_TX_PIN                    GPIO_Pin_8
#define DBG_UART_TX_GPIO_PORT              GPIOD
#define DBG_UART_TX_SOURCE                 GPIO_PinSource8

#define DBG_UART_RX_PIN                    GPIO_Pin_9
#define DBG_UART_RX_GPIO_PORT              GPIOD
#define DBG_UART_RX_SOURCE                 GPIO_PinSource9

#define DBG_UART_BAUDRATE                  115200
//===============================================================
#endif

#ifdef	DBG_USART6
//===============================================================
// TX -> PC6
// RX -> PC7
#define DBG_UART                           USART6
#define RCC_DBG_UART_CLK                   RCC_APB2Periph_USART6
#define RCC_DBG_UART_CLK_INIT              RCC_APB2PeriphClockCmd
#define DBG_UART_IRQn                      USART6_IRQn
#define DBG_UART_IRQHandler                USART6_IRQHandler

#define DBG_UART_GPIO_AF                   GPIO_AF_USART6
#define RCC_DBG_UART_GPIO_CLK              RCC_AHB1Periph_GPIOC
#define RCC_DBG_UART_GPIO_CLK_INIT		   RCC_AHB1PeriphClockCmd

//DMA2 			Stream 1	Stream 2	Stream 6	Stream 7
//Channel 5 -	USART6_RX	USART6_RX	USART6_TX	USART6_TX
#define RCC_DBG_UART_DMA_CLK               RCC_AHB1Periph_DMA2
#define RCC_DBG_UART_DMA_CLK_INIT          RCC_AHB1PeriphClockCmd
#define DBG_UART_DMA_CHANNEL               DMA_Channel_5
#define DBG_UART_DMA_IT_TC_RX              DMA_IT_TCIF1
#define DBG_UART_DMA_STREAM_RX             DMA2_Stream1
#define DBG_UART_DMA_STREAM_RX_IRQn        DMA2_Stream1_IRQn
#define DBG_UART_DMA_STREAM_RX_IRQHandler  DMA2_Stream1_IRQHandler
#define DBG_UART_DMA_IT_TC_TX              DMA_IT_TCIF6
#define DBG_UART_DMA_STREAM_TX             DMA2_Stream6
#define DBG_UART_DMA_STREAM_TX_IRQn        DMA2_Stream6_IRQn
#define DBG_UART_DMA_STREAM_TX_IRQHandler  DMA2_Stream6_IRQHandler

#define DBG_UART_TX_PIN                    GPIO_Pin_6
#define DBG_UART_TX_GPIO_PORT              GPIOC
#define DBG_UART_TX_SOURCE                 GPIO_PinSource6

#define DBG_UART_RX_PIN                    GPIO_Pin_7
#define DBG_UART_RX_GPIO_PORT              GPIOC
#define DBG_UART_RX_SOURCE                 GPIO_PinSource7

#define DBG_UART_BAUDRATE                  115200
//===============================================================
#endif

#endif /* __USART_X_H */
//******************************************************************************
