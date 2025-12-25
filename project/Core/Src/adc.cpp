#include "adc.hpp"
#include "hk32f04axxA.h"

/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
void ADC1_Init(void)
{
    ADC_InitTypeDef          ADC_InitStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;

    /* GPIOC Peripheral clock enable */
    RCC_AHBPeriphClockCmd(ADC_GPIO_CLK, ENABLE);

    /* ADC1 Peripheral clock enable */
    RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);

    /* Configure ADC Chanenl (1 4 5) as analog input */
    GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN | ADC_BAT_PIN | UN_KNOWN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

    /* ADCs DeInit */
    ADC_DeInit(ADCx);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits*/
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
    ADC_Init(ADCx, &ADC_InitStructure);
    
    
    ADC_ChannelConfig(ADCx, ADC_BAT_CHANNEL ,   ADC_SampleTime_55_5Cycles);
    ADC_ChannelConfig(ADCx, ADC_TEMPER_CHANNEL, ADC_SampleTime_55_5Cycles);
    ADC_ChannelConfig(ADCx, UN_KNOWN_CHANNEL,   ADC_SampleTime_55_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADCx);
    
    /* ADC DMA request in circular mode */
    ADC_DMARequestModeConfig(ADCx, ADC_DMAMode_Circular);
    
    /* Enable ADC_DMA */
    ADC_DMACmd(ADCx, ENABLE);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADCx, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_ADRDY))
    {
        
    }

    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADCx);
}

#if 0
void ADC1_CAHNNEL_Init(uint32_t channel)
{
    ADC_InitTypeDef          ADC_InitStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;

    /* GPIOC Peripheral clock enable */
    RCC_AHBPeriphClockCmd(ADC_GPIO_CLK, ENABLE);

    /* ADC1 Peripheral clock enable */
    RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);

    /* Configure ADC Chanenl (1 4 5) as analog input */
    GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN | ADC_BAT_PIN | UN_KNOWN_PIN;
//    if(channel == ADC_TEMPER_CHANNEL)
//        GPIO_InitStructure.GPIO_Pin = ADC_BAT_PIN;
//    if(channel == ADC_BAT_CHANNEL)
//        GPIO_InitStructure.GPIO_Pin = ADC_TEMPER_PIN;
//    if(channel == UN_KNOWN_CHANNEL)
//        GPIO_InitStructure.GPIO_Pin = UN_KNOWN_PIN;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

//    ADC_Cmd(ADCx, DISABLE);
    /* ADCs DeInit */
    ADC_DeInit(ADCx);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits*/
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADCx, &ADC_InitStructure);
    
    ADC_ChannelConfig(ADCx, channel,    ADC_SampleTime_71_5Cycles);
//    ADC_ChannelConfig(ADCx, ADC_TEMPER_CHANNEL, ADC_SampleTime_71_5Cycles);
//    ADC_ChannelConfig(ADCx, UN_KNOWN_CHANNEL,   ADC_SampleTime_71_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADCx);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADCx, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_ADRDY))
    {
        
    }

    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADCx);
}
#endif

