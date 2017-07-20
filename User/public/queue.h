#ifndef __QUEUE_H__
#define __QUEUE_H__


#include "public.h"

#define USART_TX_BUF_SIZE 64
#define USART_RX_BUF_SIZE 64

#define true 1
#define false 0

extern void init_queue(void);
extern void put_queue_data(unsigned char c);
extern unsigned char get_queue_data(void);
extern int get_queue_data_length(void);
extern void reset_queue_data_ptr(void);
extern int is_full_queue(void);
extern int is_empty_queue(void);


#endif
