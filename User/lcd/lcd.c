#include "lcd.h"

/*
 *	LCD GPIO init
 */
void lcd_gio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* ��ʱ��ʹ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOG,ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    /* FSMC_A10(G0) �� FSMC_NE4(G12)(RS) */
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
                                   | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9
                                   | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15);

    /* FSMC_D* FSMC_NOE FSMC_NWE */
    GPIO_Init(GPIOD,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin= (GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
                                  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13
                                  | GPIO_Pin_14 | GPIO_Pin_15);

    /* FSMC_D4 ~ FSMC_D12 */
    GPIO_Init(GPIOE,&GPIO_InitStructure);
}

/*
 *	LCD FSMC init
 */
void lcd_fsmc_init(void)
{
    FSMC_NORSRAMInitTypeDef 		FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef 	FSMC_NORSRAMTiming;

    /* ���ö�дʱ�򣬸�FSMC_NORSRAMInitStructure���� */
    /* ��ַ����ʱ�䣬3��HCLK���� */
    FSMC_NORSRAMTiming.FSMC_AddressSetupTime = 0x04;	//0x02

    /* ��ַ����ʱ�䣬1��HCLK���� */
    FSMC_NORSRAMTiming.FSMC_AddressHoldTime = 0x02;		//0x00

    /* ���ݽ���ʱ�䣬6��HCLK���� */
    FSMC_NORSRAMTiming.FSMC_DataSetupTime = 0x10;		//0x05

    /* ���ݱ���ʱ�䣬1��HCLK���� */
    FSMC_NORSRAMTiming.FSMC_DataLatency = 0x05;		//0x00

    /* ���߻ָ�ʱ������ */
    FSMC_NORSRAMTiming.FSMC_BusTurnAroundDuration = 0x01;	//0x00

    /* ʱ�ӷ�Ƶ���� */
    FSMC_NORSRAMTiming.FSMC_CLKDivision = 0x01;

    /* ����ģʽ������ڵ�ַ/���ݲ�����ʱ��ABCDģʽ�����𲻴� */
    FSMC_NORSRAMTiming.FSMC_AccessMode = FSMC_AccessMode_B;

    /* ����FSMC_NORSRAMInitStructure������ */
    /* FSMC���ĸ��洢��(bank)������ʹ�õ�һ��(bank1) */
    /* ͬʱ������ʹ�õ���bank����ĵ�4��RAM�� */
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;

    /* ����ʹ�õ���SRAMģʽ */
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;

    /* ���ݿ��Ϊ16λ */
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;

    /* ����дʹ�ܴ� */
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;

    /* ѡ����չģʽʹ�ܣ������ö���д�ò�ͬ��ʱ�� */
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;

    /* ���õ�ַ�����ݸ���ʹ�ܲ��� */
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;

    /* ���ö�дʱ�� */
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct= &FSMC_NORSRAMTiming;

    /* ����дʱ�� */
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTiming;

    /* ��FSMC��ʱ�� */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

    /* ��ʼ��FSMC */
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* ʹ��FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4,ENABLE);
}

void lcd_wrcmd(u16 cmd)
{

    tft->tft_cmd = cmd >> 8;
    tft->tft_cmd = cmd & 0xff;
}

void lcd_wrdat(u16 dat)
{
    tft->tft_dat = dat >> 8;
    tft->tft_dat = dat & 0xff;
}

void lcd_init(void)
{
    u16 i;
    lcd_gio_init();
    lcd_fsmc_init();

    for(i=500; i > 0; i--);

    lcd_wrcmd(0x0001);		//Device Output Control
    lcd_wrdat(0x0100);		//SS=1,shift direction of outputs is from S720 to S1.�������仯��S720��S1.

    lcd_wrcmd(0x0003);		//Entry Mode
    lcd_wrdat(0x1030);		//BGR=1,Reverse the order from RGB to BGR in writing data to the DRAM
    //AM=0,ID[1:0]="11" Write DRAM Direction

    lcd_wrcmd(0x0008);		//Display Control 2
    lcd_wrdat(0x0808);		//Front Porch lines = 8 Back proch lines = 8

    lcd_wrcmd(0x0090);
    lcd_wrdat(0x8000);

    lcd_wrcmd(0x0400);
    lcd_wrdat(0x6200);

    lcd_wrcmd(0x0401);
    lcd_wrdat(0x0001);

    lcd_wrcmd(0x00ff);
    lcd_wrdat(0x0001);

    lcd_wrcmd(0x0102);
    lcd_wrdat(0x01b0);

    lcd_wrcmd(0x0710);
    lcd_wrdat(0x0016);

    lcd_wrcmd(0x0712);
    lcd_wrdat(0x000f);

    lcd_wrcmd(0x0752);
    lcd_wrdat(0x002f);

    lcd_wrcmd(0x0724);
    lcd_wrdat(0x001a);

    lcd_wrcmd(0x0754);
    lcd_wrdat(0x0018);

    for(i = 500; i > 0; i--);

    /* Gamma */
    lcd_wrcmd(0x0308);
    lcd_wrdat(0x0000);

    lcd_wrcmd(0x0381);
    lcd_wrdat(0x5F10);

    lcd_wrcmd(0x0382);
    lcd_wrdat(0x0B02);

    lcd_wrcmd(0x0383);
    lcd_wrdat(0x0614);

    lcd_wrcmd(0x0384);
    lcd_wrdat(0x0111);

    lcd_wrcmd(0x0385);
    lcd_wrdat(0x0000);

    lcd_wrcmd(0x0386);
    lcd_wrdat(0xA90B);

    lcd_wrcmd(0x0387);
    lcd_wrdat(0x0606);

    lcd_wrcmd(0x0388);
    lcd_wrdat(0x0612);

    lcd_wrcmd(0x0389);
    lcd_wrdat(0x0111);

    /* Gamma Setting */
    lcd_wrcmd(0x0702);
    lcd_wrdat(0x003b);

    lcd_wrcmd(0x00ff);
    lcd_wrdat(0x0000);

    /* Vcom Setting */
    lcd_wrcmd(0x0007);
    lcd_wrdat(0x0100);

    for(i = 500; i > 0; i--);

    lcd_wrcmd(0x0200);
    lcd_wrdat(0x0000);

    lcd_wrcmd(0x0201);
    lcd_wrdat(0x0000);
}


/******************************************************************
*  Function Name  : lcd_set_window
*  Description    :	����Ҫ�����Ĵ��ڷ�Χ
*  Input		  : xStart: ������ʼX����
*					yStart: ������ʼY����
*					xEnd: ���ڽ���X����
*					yEnd: ���ڽ���Y����
*  Output		  : None
*  Return 		  : None
******************************************************************/
void lcd_set_window(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd)
{
    lcd_wrcmd(0x0210);
    lcd_wrdat(xStart);

    lcd_wrcmd(0x0211);
    lcd_wrdat(xEnd);

    lcd_wrcmd(0x0212);
    lcd_wrdat(yStart);

    lcd_wrcmd(0x0213);
    lcd_wrdat(yEnd);

    lcd_wrcmd(0x0200);
    lcd_wrdat(xStart);

    lcd_wrcmd(0x0201);
    lcd_wrdat(yStart);

    lcd_wrcmd(0x0202);
}

void lcd_clear_screen(u16 color)
{
    u16 i,j;

    lcd_set_window(0,0,LCD_XMAX,LCD_YMAX);

    for(i = 0; i < (LCD_XMAX + 1); i++)
    {
        for(j = 0; j < (LCD_YMAX + 1); j++)
        {
            lcd_wrdat(color);
        }
    }
}

