//******************************************************************************
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIFO_BUFFER_H
#define __FIFO_BUFFER_H

#include "stm32f4xx.h"
#include "stdbool.h"

#define USARTBUFFSIZE 0xff

typedef struct{
    uint16_t	in;
    uint16_t	out;
    uint16_t	count;
    uint8_t		buff[USARTBUFFSIZE];
}FIFO_TypeDef;

void			BufferInit(		__IO FIFO_TypeDef *buffer);
ErrorStatus		BufferPut(		__IO FIFO_TypeDef *buffer, uint8_t ch);
ErrorStatus 	BufferGet(		__IO FIFO_TypeDef *buffer, uint8_t *ch);
bool 			BufferIsEmpty(	__IO FIFO_TypeDef buffer);

#endif /* __FIFO_BUFFER_H */
//******************************************************************************
