/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/* periph driver header file */
#include "lcd.h"
#include "public.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"

int TIM2_Update_flag = 0;
char usart_data_main[] = {'A','B'};


void delay(unsigned int temp)
	{
	int a,j;
	for(a=0;a<temp;a++)
		for(j=0;j<1000;j++);
	}


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    SystemInit();
    lcd_init();
    time2_config();
    gpio_config();
    UART3_config();

	delay(10000);


    UART3_SendData(usart_data_main,sizeof(usart_data_main));

    //lcd_clear_screen(RED);
    while(1)
    {
        if(1 == TIM2_Update_flag)
        {
            lcd_clear_screen(YELLOW);
        }
        else if(2 == TIM2_Update_flag)
        {
            lcd_clear_screen(BLACK);
        }
        else
        {
            lcd_clear_screen(BLUE);
        }
    }
}
