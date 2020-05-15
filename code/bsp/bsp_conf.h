/**
 **************************************************************************************************
 * @file        bsp_conf.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_CONF_H_
#define _BSP_CONF_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */




/**
 * @addtogroup    bsp_conf_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_conf_Exported_Macros 
 * @{  
 */
// -----------Lib Active list --------------------
#define USING_MKL16_LIB 			1
// -----------------------------------------------
// -----------BSP Module Active list -------------
#define BSP_SMC_MODULE_ENABLE			0
#define BSP_GPIO_MODULE_ENABLE			1
#define BSP_TIM_MODULE_ENABLE			1
#define BSP_RTC_MODULE_ENABLE			0
#define BSP_ADC_MODULE_ENABLE			0
#define BSP_DMA_MODULE_ENABLE			1
#define BSP_USART_MODULE_ENABLE			1
#define BSP_FLASH_MODULE_ENABLE			1
#define BSP_LPV_MODULE_ENABLE			0


#define BSP_CAN_MODULE_ENABLE 			0
#define BSP_DAC_MODULE_ENABLE			0
#define BSP_EXTI_MODULE_ENABLE 			0

#define BSP_IIC_MODULE_ENABLE			0
#define BSP_SPI_MODULE_ENABLE			0
#define BSP_WDG_MODULE_ENABLE			0
#define BSP_SYSTICK_MODULE_ENABLE		0

// -----------------------------------------------

#if USING_MKL16_LIB == 1
	#include "fsl_common.h"
	#include "fsl_port.h"
#endif

#if BSP_ADC_MODULE_ENABLE == 1
	#include "fsl_smc.h"
#endif

#if BSP_SMC_MODULE_ENABLE == 1
	#include "fsl_smc.h"
#endif

#if BSP_GPIO_MODULE_ENABLE == 1
	#include "fsl_gpio.h"
#endif	

#if BSP_TIM_MODULE_ENABLE == 1
	#include "fsl_lptmr.h"	
	#include "fsl_ftm.h"
#endif	

#if BSP_RTC_MODULE_ENABLE == 1	
	#include "fsl_rtc.h"
#endif	


#if BSP_ADC_MODULE_ENABLE == 1	
	#include "fsl_adc16.h"
#endif	

#if BSP_DMA_MODULE_ENABLE == 1	
	#include "fsl_edma.h"
	#include "fsl_dmamux.h"
#endif	

#if BSP_USART_MODULE_ENABLE == 1	
	#include "fsl_uart.h"
	#include "fsl_uart_edma.h"
#endif	

#if BSP_FLASH_MODULE_ENABLE == 1	
	#include "fsl_flash.h"
#endif	

#if BSP_LPV_MODULE_ENABLE == 1	
	#include "fsl_smc.h"
	#include "fsl_pmc.h"
#endif	





/**
 * @}
 */

/**
 * @defgroup      bsp_conf_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_conf_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_conf_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_conf_Exported_Functions 
 * @{  
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
