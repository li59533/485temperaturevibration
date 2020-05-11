/**
 **************************************************************************************************
 * @file        rtos_tools.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"
/**
 * @addtogroup    rtos_tools_Modules 
 * @{  
 */

/**
 * @defgroup      rtos_tools_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      rtos_tools_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      rtos_tools_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      rtos_tools_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Functions 
 * @brief         
 * @{  
 */
 
void RTOS_Delay_ms(uint32_t count)
{
	vTaskDelay(pdMS_TO_TICKS(count));	
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

