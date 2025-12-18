#include "batVolt.hpp"

static void Bat_delay(uint8_t ms)
{
    for(uint8_t cnt_ms=0; cnt_ms<ms; cnt_ms++)
    {
        uint32_t i=0;
        while(i<12000)
            i++;
    }
}

/**********************************************************
函数名称：ADC_GetValue_Avg
函数功能：AD检测
入口参数：无
出口参数：uint16_t 采样结果(0-4095)
备    注：采样通道需自行设置为输入口
	      采样10次,取中间八次的平均值为采样结果返回

          (主任务使用前记得延时，否则采样值会很奇怪到65000多)
**********************************************************/
uint16_t Bat_GetValue_Avg(void)
{
    uint32_t val_sum = 0;
    uint8_t i =0;
//    ADC_ChannelConfTypeDef sConfig;
//    sConfig.Channel = ADC_CHANNEL_11;
//    sConfig.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;   //采样时间越久，采集越准确
//    sConfig.Rank = ADC_REGULAR_RANK_1;
//    sConfig.SingleDiff = ADC_SINGLE_ENDED;
//    sConfig.OffsetNumber = ADC_OFFSET_NONE;
//    sConfig.Offset  = 0;
//    HAL_ADC_ConfigChannel(&hadc1,&sConfig); //之前会卡死在这里的原因是结构体没有配置完全，导致进入错误句柄
//    HAL_ADCEx_Calibration_Start(&hadc1,ADC_SINGLE_ENDED); //校准

    for(i=0; i<10; i++)
    {
        HAL_ADC_Start(&hadc1);                               //开启ADC
        if(HAL_ADC_PollForConversion(&hadc1,1000) == HAL_OK)  //轮询转换
        {
            while(__HAL_ADC_GET_FLAG(&hadc1,ADC_FLAG_EOC));
        }
        uint16_t val = HAL_ADC_GetValue(&hadc1);
        if(i!=0 && i!=9)
            val_sum += val;
//        printf("第%d次采集的adc数据为= %d\r\n",i+1,val);
        HAL_ADC_Stop(&hadc1);
        Bat_delay(5);
    }
//    printf("adc_avg_8 = %d\r\n",val_sum/8);
//    return (double)((double)val_sum/8*3.3/4095);
    return (uint16_t)(val_sum/8);
}


/**********************************************************
函数名称：Bat_getSOC
函数功能：得到避锁器SOC
入口参数：bat_val     采集的ADC数值
出口参数：uint8_t     SOC结果(0-100)
备    注：SOC获取阈值参照
        ----------------------------------------------------------------------------------
        |  SOC%    | 100  |  90  |  80  |  70  |  60  |  50  |  40  |  30  |  20  |  10  |
        ----------------------------------------------------------------------------------
        | 电池电压V| 4.10 | 4.05 | 4.00 | 3.93 | 3.87 | 3.82 | 3.79 | 3.74 | 3.68 | 3.60 |
        ----------------------------------------------------------------------------------
        |  ADC采样 | 2360 | 2330 | 2300 | 2260 | 2230 | 2200 | 2180 | 2155 | 2120 | 2080 |
        ----------------------------------------------------------------------------------
**********************************************************/
uint16_t Bat_getSOC(uint16_t bat_val)
{
    uint16_t result = 0;
    if(bat_val >=2360)
        result = 100;
    else if(bat_val >=2330)
        result = 90;
    else if(bat_val >=2300)
        result = 80;
    else if(bat_val >=2260)
        result = 70;
    else if(bat_val >=2230)
        result = 60;
    else if(bat_val >=2200)
        result = 50;
    else if(bat_val >=2180)
        result = 40;
    else if(bat_val >=2155)
        result = 30;
    else if(bat_val >=2120)
        result = 20;
    else if(bat_val >=2080)
        result = 10;
    return result;
}
