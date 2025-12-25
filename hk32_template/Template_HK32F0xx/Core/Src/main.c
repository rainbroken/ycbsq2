
#include "main.h"
#include "adc.hpp"
#include "can.hpp"
#include "tim.hpp"
#include "usart.hpp"
#include "iic.hpp"
#include "gpio.hpp"

//#include "hk32f0xxa_eval.h"
#include "variables.hpp"
#include "bsp_usart.hpp"
#include "bsp_can.hpp"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*!< At this stage the microcontroller clock setting is already configured,
 *   this is done through SystemInit() function which is called from startup
 *   file (startup_hk32f0xxa.s) before to branch to application main.
 *   To reconfigure the default setting of SystemInit() function, refer to
 *   system_hk32f0xxa.c file
 **/
int main(void)
{
    uint8_t data[8] = {0x01,0x02,0x03,0x04,0x05 ,0x06,0x07,0x08};
//    SystemInit();
    
//    vGPIO_Init();
//    ADC1_Init();
    CAN1_Init();
//    TIM3_Init();
    USART1_UART_Init(115200);
//    USART2_UART_Init(115200);
//    IIC2_Init();
    
    while (1)
    {
        bspCanSend(0x1826F456,data,8);
//        Uart1_Send('a');
        Uart1_print((uint8_t*)"12345\r\n");
//        uart_print((char *)"123456\r\n");
        delay_ms(1000);
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
        ;
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

