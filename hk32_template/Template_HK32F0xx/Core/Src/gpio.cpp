#include "gpio.hpp"

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void vGPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
  /* GPIO Ports Clock Enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    
  /*Configure GPIO pin Output Level */
  GPIO_WriteBit(GPIOB, AMP_SHUT_Pin|VBUS_DET_Pin|CHG_EN_Pin|V_5V_EN_Pin
                          |CAN_EN_Pin|TTS_BUSY_Pin|TTS_DAT_Pin, Bit_RESET);

  /*Configure GPIO pin Output Level */
  GPIO_WriteBit(GPIOA, CAT1_RST_Pin|CAT1_EN_Pin|CAT1_PWRK_Pin, Bit_SET);
    
    
  /*Configure GPIO pin : TOUCH_Pin */
  GPIO_InitStruct.GPIO_Pin = TOUCH_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(TOUCH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : AMP_SHUT_Pin VBUS_DET_Pin CHG_EN_Pin V_5V_EN_Pin
                           CAN_EN_Pin TTS_BUSY_Pin TTS_DAT_Pin */
  GPIO_InitStruct.GPIO_Pin = AMP_SHUT_Pin|VBUS_DET_Pin|CHG_EN_Pin|V_5V_EN_Pin
                          |CAN_EN_Pin|TTS_BUSY_Pin|TTS_DAT_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CHG_DET_Pin */
  GPIO_InitStruct.GPIO_Pin = CHG_DET_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(CHG_DET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CHG_STB_Pin */
  GPIO_InitStruct.GPIO_Pin = CHG_STB_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(CHG_STB_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CAT1_RST_Pin CAT1_EN_Pin CAT1_PWRK_Pin */
  GPIO_InitStruct.GPIO_Pin = CAT1_RST_Pin|CAT1_EN_Pin|CAT1_PWRK_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
    
}
