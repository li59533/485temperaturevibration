/**
 **************************************************************************************************
 * @file        rtos_tools.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _RTOS_TOOLS_H_
#define _RTOS_TOOLS_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    rtos_tools_Modules 
 * @{  
 */

/**
 * @defgroup      rtos_tools_Exported_Macros 
 * @{  
 */
#define EVENT_FROM_TASK 1
#define EVENT_FROM_ISR  2

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      rtos_tools_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      rtos_tools_Exported_Functions 
 * @{  
 */
void RTOS_Delay_ms(uint32_t count);

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
