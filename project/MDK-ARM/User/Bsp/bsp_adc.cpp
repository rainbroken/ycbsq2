#include "bsp_adc.hpp"
#include "hk32f04axxA.h"
#include "adc.hpp"


void bspAdcInit(void)
{
//    HAL_ADCEx_Calibration_Start(&hadc1);   //ADC
}

/**
  * @brief  ADC get value
  * @param  uint32_t channel adc采样通道 
            (ADC_Channel_0 - ADC_Channel_18)
  * @retval uint16_t 采样结果(0-4096)
  */
uint16_t bspAdcGetValue(uint32_t channel)
{
    uint16_t adc_val_ = 0;
//    ADC_ChannelConfig(ADCx, channel, ADC_SampleTime_28_5Cycles);
//    
//    ADC_StartOfConversion(ADCx);
//    while(ADC_GetFlagStatus(ADC, ADC_FLAG_EOC) == RESET);
//    adc_val_ = ADC_GetConversionValue(ADCx);
//    ADC_StopOfConversion(ADCx);
//    return adc_val_;
//    ADC_ChannelConfig(ADCx, channel, ADC_SampleTime_28_5Cycles);

    while (!ADC_GetFlagStatus(ADC, ADC_FLAG_EOC));
    
    adc_val_ = ADC_GetConversionValue(ADCx);
    return adc_val_;
}
uint16_t bspAdcVal(uint32_t channel)
{
    uint16_t adc_val_ = 0;
    ADC_ChannelConfig(ADCx, channel, ADC_SampleTime_55_5Cycles);
    ADCx->CHSELR = channel;
    while (!ADC_GetFlagStatus(ADCx, ADC_FLAG_ADRDY)){};    
    ADC_StartOfConversion(ADCx);
    while(ADC_GetFlagStatus(ADC, ADC_FLAG_EOC) == RESET);
    adc_val_ = ADC_GetConversionValue(ADCx);
    return adc_val_;
}


uint16_t bspAdcAvgVal(uint32_t channel, uint8_t cnt)
{
    if (cnt <= 6)
    {
        return 0;
    }

    uint32_t sum = 0x00;
    for (uint8_t i = 0; i < cnt; i++) 
    {
        if (i >= 10 && i < cnt - 3) {
            sum += bspAdcGetValue(channel);
        }
    }
    return (uint16_t)(sum / (cnt - 6));
}

