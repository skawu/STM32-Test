#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

extern void UART3_config(void);
extern void UART3_SendData(char c[], int length);

#endif

