#include "bsp_adc.hpp"
#include "hk32f04axxA.h"

//void bspAdcInit(void)
//{
//    HAL_ADCEx_Calibration_Start(&hadc1);   //ADC
//}

/**
  * @brief  ADC configuration
  * @param  None
  * @retval None
  */
void ADC_Config(void)
{
    ADC_InitTypeDef          ADC_InitStructure;
    GPIO_InitTypeDef         GPIO_InitStructure;

    /* GPIOC Peripheral clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /* ADC1 Peripheral clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    /* Configure ADC Chanenl 1 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADCs DeInit */
    ADC_DeInit(ADC);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits*/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC, &ADC_InitStructure);
    ADC_ChannelConfig(ADC, ADC_Channel_1, ADC_SampleTime_28_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC);

    /* Enable the ADC peripheral */
    ADC_Cmd(ADC, ENABLE);

    /* Wait the ADRDY flag */
    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_ADRDY))
    {
        
    }

    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADC);
}