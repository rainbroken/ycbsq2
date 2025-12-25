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

    /* Configure ADC Chanenl 1 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

    /* ADCs DeInit */
    ADC_DeInit(ADC_BAT);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits*/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC_BAT, &ADC_InitStructure);
    ADC_ChannelConfig(ADC_BAT, ADC_Channel_1, ADC_SampleTime_28_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC_BAT);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADC_BAT, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADC_BAT, ADC_FLAG_ADRDY))
    {
        
    }

    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADC_BAT);
}

