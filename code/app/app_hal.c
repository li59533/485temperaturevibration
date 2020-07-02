/**
 **************************************************************************************************
 * @file        app_hal.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "app_hal.h"
#include "MK24F25612.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
/**
 * @addtogroup    app_hal_Modules 
 * @{  
 */

/**
 * @defgroup      app_hal_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_hal_Functions 
 * @brief         
 * @{  
 */
 

void APP_Hal_Rest(void)
{
	DEBUG("Hal Rest\r\n");
	NVIC_SystemReset();	
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

