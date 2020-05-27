/**
 **************************************************************************************************
 * @file        sample_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SAMPLE_TASK_H_
#define _SAMPLE_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
/**
 * @addtogroup    sample_task_Modules 
 * @{  
 */

/**
 * @defgroup      sample_task_Exported_Macros 
 * @{  
 */
#define SAMPLE_TASK_TEST_EVENT 			(0X01 << 0)
#define SAMPLE_TASK_TEST2_EVENT			(0X01 << 1)
#define SAMPLE_TASK_CALC_EVENT			(0X01 << 2)
/**
 * @}
 */

/**
 * @defgroup      sample_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      sample_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sample_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Sample_Task_Handle ;
/**
 * @}
 */

/**
 * @defgroup      sample_task_Exported_Functions 
 * @{  
 */
uint32_t Sample_Task_Init(void); 
void Sample_Task(void * pvParameter);
void Sample_Task_Event_Start(uint32_t events, uint8_t event_from);
void Sample_Task_Tim_Init(void);
void Sample_Task_StartTim(uint16_t time_count);

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


