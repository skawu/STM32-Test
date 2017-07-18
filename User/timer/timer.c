#include "timer.h"

void timer_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //ʹ�ܶ�ʱ��2ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    //��λ��ʱ��2
    TIM_DeInit(TIM2);

    //���ö�ʱ��
    //��ʱ��ʱ�ӷ�Ƶ,1��ʾ����Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //��ʱ������ģʽ�����ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //��ʱ������,2s
    TIM_TimeBaseStructure.TIM_Period = 2000;
    //Ԥ��Ƶϵ��
    TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1;

    //��ʼ����ʱ��2
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    //�����ʱ��2�����־λ
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    //ʹ�ܶ�ʱ2����ж�
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    //ʹ�ܶ�ʱ��2
    TIM_Cmd(TIM2,ENABLE);

}

void TIM2_NVIC_init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    //����������
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    //TIM2�ж�����
    //ѡ�����õ��жϣ�TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    //�ж�ʹ�ܿ���
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //�����ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;

    //��ʼ���ж�
    NVIC_Init(&NVIC_InitStructure);
}

void time2_config(void)
{
    timer_init();
    TIM2_NVIC_init();
}

