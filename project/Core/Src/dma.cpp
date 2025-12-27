#include "dma.hpp"
#include "variables.hpp"

#define ADC1_DR_Address    0x40012440
volatile uint16_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;
volatile uint16_t RegularConvData_Tab[4];

/**
  * @brief  DMA channel1 configuration
  * @retval None
  */
void DMA_Config(void)
{
    DMA_InitTypeDef   DMA_InitStructure;

    /* DMA1 clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    /* DMA1 Channel1 Config */
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 3;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    /* DMA1 Channel1 enable */
    DMA_Cmd(DMA1_Channel1, ENABLE);
}


void DMA_USART1_Config(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    // 2.2 配置DMA1_Channel5（USART1_RX对应通道5）
    DMA_InitTypeDef DMA_InitStructure;
    DMA_DeInit(DMA1_Channel5);  // 复位DMA通道

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->RDR;  // 外设地址（USART数据寄存器）
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rx_buffer;        // 内存地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                 // 外设到内存
    DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;                    // 缓冲区大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   // 外设地址不递增
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;            // 内存地址递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 8位数据
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;   // 8位数据
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                      // 普通模式（非循环）
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;              // 中等优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                       // 不支持内存到内存
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);

    // 2.3 使能DMA传输完成中断
    DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);  // 传输完成中断
    DMA_Cmd(DMA1_Channel5, ENABLE);                  // 启动DMA
}
