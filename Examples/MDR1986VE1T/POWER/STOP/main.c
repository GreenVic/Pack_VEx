/**
 ******************************************************************************
 * @file    Examples/MDR1986VE1T_EVAL/POWER/STOP/main.c
 * @author  Milandr Application Team
 * @version V1.2.0
 * @date    04/07/2013
 * @brief   Main program body.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2013 Milandr</center></h2>
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_power.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Examples MDR32F9Qx StdPeriph Examples
 * @{
 */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Opora Evaluation Board
 * @{
 */

/** @addtogroup POWER_STANDBY_1T POWER_STANDBY
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
void main ( void )
{
	uint32_t i;
	/* Enables the HSI clock on PORTD */
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);

	/* Configure all unused PORT pins to low power consumption */

	PORT_StructInit(&PORT_InitStructure);
	PORT_InitStructure.PORT_Pin = (PORT_Pin_All & ~PORT_Pin_7);
	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Configure PORTD pins 7 for output to switch LEDs on/off */

	PORT_InitStructure.PORT_Pin = PORT_Pin_7;
	PORT_InitStructure.PORT_OE = PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

	PORT_Init(MDR_PORTD, &PORT_InitStructure);

	/* Enable EXT_INT4 */
	NVIC_EnableIRQ(EXT_INT4_IRQn);

	/* STOP mode */
	POWER_EnterSTOPMode(ENABLE, POWER_STOPentry_WFI );

	while(1){
		if (PORT_ReadInputDataBit(MDR_PORTD, PORT_Pin_7) == 0) {
			PORT_SetBits(MDR_PORTD, PORT_Pin_7);
		}
		else {
			PORT_ResetBits(MDR_PORTD, PORT_Pin_7);
		}
		for (i = 0; i < 200000; i++);

	}
}

/**
 * @brief  Reports the source file ID, the source line number
 *         and expression text (if USE_ASSERT_INFO == 2) where
 *         the assert_param error has occurred.
 * @param  file_id: pointer to the source file name
 * @param  line: assert_param error line source number
 * @param  expr:
 * @retval None
 */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint32_t file_id, uint32_t line)
{
	/* User can add his own implementation to report the source file ID and line number.
	 Ex: printf("Wrong parameters value: file Id %d on line %d\r\n", file_id, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
{
	/* User can add his own implementation to report the source file ID, line number and
	 expression text.
	 Ex: printf("Wrong parameters value (%s): file Id %d on line %d\r\n", expr, file_id, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_ASSERT_INFO */

/** @} *//* End of group POWER_STANDBY_1T */

/** @} *//* End of group __MDR1986VE1T_EVAL */

/** @} *//* End of group __MDR32F9Qx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2013 Milandr *********/

/* END OF FILE main.c */

