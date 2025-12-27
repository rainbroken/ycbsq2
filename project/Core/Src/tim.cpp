#include "tim.hpp"

    
//RGB灯定时器
void TIM3_Init(void)
{
//    uint16_t PrescalerValue = 0;
//    
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//    TIM_OCInitTypeDef  TIM_OCInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    
//    /* TIM3 clock enable */
//    RCC_APB1PeriphClockCmd(TIM3_CLK, ENABLE);
//    
//    /* Enable the TIM3 gloabal Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    /* Compute the prescaler value */
//    PrescalerValue = (uint16_t) (SystemCoreClock  / 7000000) - 1;

//    /* Time base configuration */
//    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//    TIM_TimeBaseStructure.TIM_Period = 65535;
//    TIM_TimeBaseStructure.TIM_Prescaler = 0;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

//    /* Prescaler configuration */
//    TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);


//    /* TIM3 enable counter */
//    TIM_Cmd(TIM3, ENABLE);

    RCC_APB1PeriphClockCmd(TIM3_CLK, ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
    
}

//系统走时定时器
void TIM6_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  // 标准库函数[2,7](@ref)
    
//    /* Compute the prescaler value */
//    uint16_t PrescalerValue = (uint16_t) (SystemCoreClock  / 5600000) - 1;
    
    TIM_TimeBaseStructInit(&TIM_InitStruct);
    TIM_InitStruct.TIM_Prescaler = 8 - 1;    // 分频至1MHz（8MHz / 8）
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
    TIM_InitStruct.TIM_Period = 1000 - 1;       // 周期1ms（1MHz / 1000）
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;  // 无分频
    TIM_InitStruct.TIM_RepetitionCounter = 0x00;    //触发中断次数1
    
//    /* Prescaler configuration */
//    TIM_PrescalerConfig(TIM6, PrescalerValue, TIM_PSCReloadMode_Immediate);
    
    TIM_TimeBaseInit(TIM6, &TIM_InitStruct);     
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);     //必须先清除标志位
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);    
    TIM_SelectOutputTrigger(TIM6,TIM_TRGOSource_Update);    //选择update时间更新为触发源
    TIM_Cmd(TIM6, ENABLE);         
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM6_IRQn;  // TIM6中断通道
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0;       // 子优先级
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;          // 使能中断
    NVIC_Init(&NVIC_InitStruct);                    
    
}

