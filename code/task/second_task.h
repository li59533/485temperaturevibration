/**
 **************************************************************************************************
 * @file        second_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SECOND_TASK_H_
#define _SECOND_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "FreeRTOS.h"
#include "self_def.h"
#include "task.h"
/**
 * @addtogroup    second_task_Modules 
 * @{  
 */

/**
 * @defgroup      second_task_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      second_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      second_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      second_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Second_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      second_task_Exported_Functions 
 * @{  
 */

void Second_Task(void * pvParameter);	
uint32_t Second_Task_Init(void);
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


