#include "timer.h"

void timer_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //使能定时器2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    //复位定时器2
    TIM_DeInit(TIM2);

    //配置定时器
    //定时器时钟分频,1表示不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //定时器计数模式，向上计数模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //定时器周期,2s
    TIM_TimeBaseStructure.TIM_Period = 2000;
    //预分频系数
    TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1;

    //初始化定时器2
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
    //清除定时器2溢出标志位
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    //使能定时2溢出中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    //使能定时器2
    TIM_Cmd(TIM2,ENABLE);

}

void TIM2_NVIC_init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    //优先组设置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    //TIM2中断配置
    //选择配置的中断，TIM2中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    //中断使能控制
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;

    //初始化中断
    NVIC_Init(&NVIC_InitStructure);
}

void time2_config(void)
{
    timer_init();
    TIM2_NVIC_init();
}

