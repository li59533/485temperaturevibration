/**
 **************************************************************************************************
 * @file        first_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _FIRST_TASK_H_
#define _FIRST_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    first_task_Modules 
 * @{  
 */

/**
 * @defgroup      first_task_Exported_Macros 
 * @{  
 */
#define FIRST_TASK_TEST_EVENT 			(0X01 << 0)
#define FIRST_TASK_TEST2_EVENT			(0X01 << 1)
/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Exported_Functions 
 * @{  
 */
uint32_t First_Task_Init(void); 
void First_Task(void * pvParameter);
void First_Task_Event_Start(uint32_t events, uint8_t event_from);
void First_Task_Tim_Init(void);
void First_Task_StartTim(uint16_t time_count);

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


