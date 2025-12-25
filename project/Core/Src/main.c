
#include "main.h"
#include "adc.hpp"
#include "can.hpp"
#include "tim.hpp"
#include "usart.hpp"
#include "iic.hpp"
#include "gpio.hpp"
#include "dma.hpp"

//#include "hk32f0xxa_eval.h"
#include "variables.hpp"
#include "bsp_usart.hpp"
#include "bsp_can.hpp"

#include "AllTasks.hpp"
#include "OLED.hpp"
#include "OLED_Data.hpp"



/*!< At this stage the microcontroller clock setting is already configured,
 *   this is done through SystemInit() function which is called from startup
 *   file (startup_hk32f0xxa.s) before to branch to application main.
 *   To reconfigure the default setting of SystemInit() function, refer to
 *   system_hk32f0xxa.c file
 **/
extern uint8_t mailbox_res;
// uint16_t adc_val =0xff;
int main(void)
{
    main_setup();
    main_task();


/* ²âÊÔIIC (OLED) */
//    while(1)
//    {
//        OLED_ShowString(1,1,"hello",OLED_6X8);
//        OLED_Update();
//        bspCanSend(0x1826F456,data,8);
//    }

#if 0
    while (1)
    {
//        bspCanSend(0x1826F456,data,8);
//        log_info("systic = %d",mailbox_res);
//
//        /* Clear DMA TC flag */
//        DMA_ClearFlag(DMA1_FLAG_TC1);
//
//        log_info("111 = %d",RegularConvData_Tab[0]);
//        log_info("222 = %d",RegularConvData_Tab[1]);
//        log_info("333 = %d",RegularConvData_Tab[2]);

//        adc_val = bspAdcGetValue(ADC_TEMPER_CHANNEL);
//        log_info("222 = %d",adc_val);
//
//        adc_val = bspAdcGetValue(UN_KNOWN_CHANNEL);
//        log_info("333 = %d",adc_val);
//        uart_print((char *)"123456\r\n");
        delay_ms(1000);
    }
#endif

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


