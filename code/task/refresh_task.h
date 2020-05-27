/**
 **************************************************************************************************
 * @file        refresh_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _REFRESH_TASK_H_
#define _REFRESH_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
/**
 * @addtogroup    refresh_task_Modules 
 * @{  
 */

/**
 * @defgroup      refresh_task_Exported_Macros 
 * @{  
 */
#define REFRESH_TASK_TEST_EVENT 			(0X01 << 0)
#define REFRESH_TASK_TEST2_EVENT			(0X01 << 1)
#define REFRESH_TASK_CHARATERISTIC_EVENT	(0X01 << 2)
#define REFRESH_TASK_WAVE_EVENT				(0X01 << 3)
#define REFRESH_TASK_CONF_EVENT				(0X01 << 4)
#define REFRESH_TASK_MBTOSYS_EVENT			(0X01 << 5)
/**
 * @}
 */

/**
 * @defgroup      refresh_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      refresh_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      refresh_task_Exported_Variables 
 * @{  
 */
extern TaskHandle_t  Refresh_Task_Handle;
/**
 * @}
 */

/**
 * @defgroup      refresh_task_Exported_Functions 
 * @{  
 */
uint32_t Refresh_Task_Init(void); 
void Refresh_Task(void * pvParameter);
void Refresh_Task_Event_Start(uint32_t events, uint8_t event_from);
void Refresh_Task_Tim_Init(void);
void Refresh_Task_StartTim(uint16_t time_count);

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


