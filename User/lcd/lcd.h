#ifndef __LCD_H__
#define __LCD_H__
#include "stm32f10x.h"


/* TFT�ṹ�� */
typedef struct
{
    u16 tft_cmd;
    u16 tft_dat;
} tft_typedef;

/* ʹ��NOR/SRAM��Bank1,sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� */
/* ע������ʱSTM32�ڲ�������һλ����! 111110 = 0x3E */
#define TFT_BASE ((uint32_t)(0x6c000000 | 0x000007fe))	//7FE
#define tft ((tft_typedef *)TFT_BASE)

/* �������Ĵ�С */
#define LCD_XMAX	239
#define LCD_YMAX	399

/* ������ɫ�ĺ� */
#define WHITE	0xFFFF
#define BLACK	0x0000
#define BLUE	0x001F
#define RED		0xF800
#define MAGENTA	0xF81F
#define GREEN	0x07E0
#define CYAN	0x7FFF
#define YELLOW	0xFFE0



void lcd_init(void);
void lcd_set_window(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd);
void lcd_clear_screen(u16 color);
void lcd_wrcmd(u16 cmd);
void lcd_wrdat(u16 dat);
void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p,
                     uint16_t wordColor, uint16_t backColor);




#endif
