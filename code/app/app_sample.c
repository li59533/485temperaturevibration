/**
 **************************************************************************************************
 * @file        app_sample.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"

#include "clog.h"
#include "app_sample.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_tim.h"
#include "bsp_adc.h"
/**
 * @addtogroup    app_sample_Modules 
 * @{  
 */

/**
 * @defgroup      app_sample_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sample_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sample_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Functions 
 * @brief         
 * @{  
 */
void APP_Sample_Init(void)
{
	DEBUG("APP_Sample_Init\r\n");
	BSP_Tim_Init(BSP_TIM1);
	BSP_Tim_1_Start();
	BSP_ADC_Init();
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

