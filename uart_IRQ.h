//******************************************************************************
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_IRQ_H
#define __UART_IRQ_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	DBG_USART3
#include "usart_x.h"
#include "FIFO_Buffer.h"

void UART_Configuration( void );
void UART_TransmitByteIT( uint8_t byte );
void UART_TransmitBuf( uint16_t DataSize, const uint8_t *Data );
uint16_t UART_ReceiveBuf( uint8_t *Data );
void UART_TransmitBuf_DMA( const uint8_t *buf, uint16_t len );
#endif /* __UART_IRQ_H */
//******************************************************************************
