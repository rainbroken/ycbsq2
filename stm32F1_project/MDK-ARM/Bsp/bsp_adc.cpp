#include "bsp_adc.hpp"

void bspAdcInit(void)
{
    HAL_ADCEx_Calibration_Start(&hadc1);   //ADC
}
