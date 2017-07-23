#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

extern void UART_config(USART_TypeDef* USARTx);
extern void USART_SendChar(USART_TypeDef* USARTx,char c);
extern void USART_SendStr(USART_TypeDef* USARTx, char *str);
//extern char putchar(char c);

#endif

