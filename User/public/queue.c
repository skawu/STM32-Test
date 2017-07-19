#include "queue.h"


/*
 *	1����ʼ������
 *	2�����
 *	3������
 *	4���ն����ж�
 *	5���������ж�
 *	6����ȡ���г���
 *	7�����ö���
 */

unsigned char USART_TX_BUF[USART_TX_BUF_SIZE];
unsigned char USART_RX_BUF[USART_RX_BUF_SIZE];

int WritePtr = 0;   //дָ��
int ReadPtr  = 0;   //��ָ��
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
        
        if(WritePtr >= USART_RX_BUF_SIZE)   //�����������һλ��ʹ�ã���ֹ����Խ��
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

