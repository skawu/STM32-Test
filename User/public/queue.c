#include "queue.h"


/*
 *	1、初始化队列
 *	2、入队
 *	3、出队
 *	4、空队列判断
 *	5、满队列判断
 *	6、获取队列长度
 *	7、重置队列
 */

unsigned char USART_TX_BUF[USART_TX_BUF_SIZE];
unsigned char USART_RX_BUF[USART_RX_BUF_SIZE];

int WritePtr = 0;   //写指针
int ReadPtr  = 0;   //读指针
int DataLength = 0;

void init_queue(void)
{
    memset(USART_TX_BUF, 0, sizeof(USART_TX_BUF));
    memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));

    WritePtr = 0;
    ReadPtr  = 0;
    DataLength = 0;
}

void put_queue_data(unsigned char c)
{
    if(!(is_full_queue()))
   {
        USART_RX_BUF[WritePtr] = c;
        WritePtr++;
        
        if(WritePtr >= USART_RX_BUF_SIZE)   //保留数组最后一位不使用，防止数组越界
        {
            WritePtr = 0;
        }
   }
}

unsigned char get_queue_data(void)
{    
    if(!(is_empty_queue()))
    {
        unsigned char c;
        
        c = USART_RX_BUF[ReadPtr];
        ReadPtr++;

        if(ReadPtr >= USART_RX_BUF_SIZE)
        {
            ReadPtr = 0;
        }
        return c;
    }
    else
    {
        return NULL;
    }  
}

int get_queue_data_length(void)
{
    int c = 0;
    if(WritePtr >= ReadPtr)
    {
        c = WritePtr - ReadPtr;
    }

    if(ReadPtr > WritePtr)
    {
        c = USART_RX_BUF_SIZE - ReadPtr + WritePtr;
    }

    return c;
}
void reset_queue_data_ptr(void)
{
    WritePtr = 0;
    ReadPtr  = 0;
}

bool is_empty_queue(void)
{
    if(0 == get_queue_data_length())
    {
        return true;  
    }
    else
    {
        return false;
    }
}

bool is_full_queue(void)
{
    if(USART_RX_BUF_SIZE == get_queue_data_length())
    {
        return ture;
    }
    else
    {
        return false;
    }
}

