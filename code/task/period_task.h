/**
 **************************************************************************************************
 * @file        period_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _PERIOD_TASK_H_
#define _PERIOD_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "FreeRTOS.h"
#include "self_def.h"
#include "task.h"
/**
 * @addtogroup    period_task_Modules 
 * @{  
 */

/**
 * @defgroup      period_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      period_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      period_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      period_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Period_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      period_task_Exported_Functions 
 * @{  
 */

void Period_Task(void * pvParameter);	
uint32_t Period_Task_Init(void);
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


