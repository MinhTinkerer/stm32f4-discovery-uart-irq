#include "FIFO_Buffer.h"

void BufferInit(__IO FIFO_TypeDef *buffer)
{
	buffer->count = 0;//0 bytes in buffer
	buffer->in = 0;//index points to start
	buffer->out = 0;//index points to start
}

ErrorStatus BufferPut(__IO FIFO_TypeDef *buffer, uint8_t ch)
{
	if(buffer->count==USARTBUFFSIZE)
		return ERROR;//buffer full
	buffer->buff[buffer->in++]=ch;
	buffer->count++;
	if(buffer->in==USARTBUFFSIZE)
		buffer->in=0;//start from beginning
	return SUCCESS;
}

ErrorStatus BufferGet(__IO FIFO_TypeDef *buffer, uint8_t *ch)
{
	if(buffer->count==0)
		return ERROR;//buffer empty
	*ch=buffer->buff[buffer->out++];
	buffer->count--;
	if(buffer->out==USARTBUFFSIZE)
		buffer->out=0;//start from beginning
	return SUCCESS;
}

bool BufferIsEmpty(__IO FIFO_TypeDef *buffer)
{
//     if(buffer.count==0)
//         return true;//buffer full
//     return false;
	return buffer->count?false:true;
}

