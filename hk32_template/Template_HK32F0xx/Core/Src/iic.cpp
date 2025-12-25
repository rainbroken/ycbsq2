#include "iic.hpp"

void IIC2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;
    
    /* Configure the I2C clock source. The clock is derived from the HSI */
    RCC_I2CCLKConfig(I2C2_RCC_CLK_HSI);
    
    /* sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
	RCC_APB2PeriphClockCmd(I2C2_COMx_SCL_IO_CLK | I2C2_COMx_SDA_IO_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(I2C2_COMx_CLK, ENABLE);
	
    /* Connect PXx to I2C_SCL*/
    GPIO_PinAFConfig(I2C2_COMx_SCL_IO_PORT, I2C2_COMx_SCL_SOURCE, I2C2_COMx_SCL_AF);

    /* Connect PXx to I2C_SDA*/
    GPIO_PinAFConfig(I2C2_COMx_SDA_IO_PORT, I2C2_COMx_SDA_SOURCE, I2C2_COMx_SDA_AF);

    /* GPIO configuration */

    /* Configure I2C2 pins: SCL */
    GPIO_InitStructure.GPIO_Pin = I2C2_COMx_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(I2C2_COMx_SCL_IO_PORT, &GPIO_InitStructure);
    
    /* Configure I2C2 pins: SDA */
    GPIO_InitStructure.GPIO_Pin = I2C2_COMx_SDA_PIN;
    GPIO_Init(I2C2_COMx_SDA_IO_PORT, &GPIO_InitStructure);
    
    /* I2C configuration */

    /* I2C2 configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
    I2C_InitStructure.I2C_DigitalFilter = 0x00;
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//    I2C_InitStructure.I2C_Timing = sEE_I2C_TIMING;

    /* Apply I2C2 configuration after enabling it */
    I2C_Init(I2C2_COMx, &I2C_InitStructure);

    /* I2C2 Peripheral Enable */
    I2C_Cmd(I2C2_COMx, ENABLE);

//    /* Select the EEPROM address */
//    sEEAddress = sEE_HW_ADDRESS;
    
}

