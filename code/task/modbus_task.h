/**
 **************************************************************************************************
 * @file        modbus_task.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUS_TASK_H_
#define _MODBUS_TASK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    modbus_task_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_task_Exported_Macros 
 * @{  
 */
#define MODBUS_TASK_TEST_EVENT 			(0X01 << 0)
#define MODBUS_TASK_TEST2_EVENT			(0X01 << 1)
#define MODBUS_TASK_DATAPROCESS_EVENT	(0X01 << 2)
#define MODBUS_TASK_REV_EVENT			(0x01 << 3)
/**
 * @}
 */

/**
 * @defgroup      modbus_task_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      modbus_task_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_task_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_task_Exported_Functions 
 * @{  
 */
uint32_t Modbus_Task_Init(void); 
void Modbus_Task(void * pvParameter);
void Modbus_Task_Event_Start(uint32_t events, uint8_t event_from);
void Modbus_Task_Tim_Init(void);
void Modbus_Task_StartTim(uint16_t time_count);
void Modbus_Task_StartTimFromISR(uint16_t time_count);
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


