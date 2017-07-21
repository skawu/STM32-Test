#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

extern void UART3_config(void);
extern void USART3_SendChar(char c);
extern void USART3_SendStr(char *str);
//extern char putchar(char c);

#endif

