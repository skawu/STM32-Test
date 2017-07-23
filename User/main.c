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
char usart_data_main[] = "芳芳是个小傻子 \n";
int TIM2_Update_flag_flag = 0;


void delay(unsigned int temp)
{
    int a,j;

    for(a=0; a<temp; a++)
        for(j=0; j<1000; j++);
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
    UART_config(USART3);

    delay(10000);


    USART_SendStr(USART3,usart_data_main);

    //lcd_clear_screen(BLACK);
    //GUI_Show12ASCII(80,160,"Helllo,FangFang!",WHITE,BLACK);

    while(1)
    {


        int TIM2_Update_flag_count = 0;

        if(TIM2_Update_flag_flag != TIM2_Update_flag)
        {
            TIM2_Update_flag_flag = TIM2_Update_flag;
            TIM2_Update_flag_count = 1;
        }
        else
        {
            TIM2_Update_flag_count = 0;
        }

        if(1 == TIM2_Update_flag && TIM2_Update_flag_count)
        {
            lcd_clear_screen(YELLOW);
            GUI_Show12ASCII(60,200,"Helllo,FangFang!",BLACK,YELLOW);
        }
        else if(2 == TIM2_Update_flag && TIM2_Update_flag_count)
        {
            lcd_clear_screen(BLACK);
            GUI_Show12ASCII(60,200,"Helllo,FangFang!",WHITE,BLACK);
        }
        else if(TIM2_Update_flag_count)
        {
            lcd_clear_screen(BLUE);
            GUI_Show12ASCII(60,200,"Helllo,FangFang!",WHITE,BLUE);
        }


        if(0xAA == get_queue_data())
        {
            lcd_clear_screen(RED);
            GUI_Show12ASCII(60,200,"Helllo,FangFang!",WHITE,RED);
            delay(10000);
        }
    }
}
