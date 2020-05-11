/**
 **************************************************************************************************
 * @file        second_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "second_task.h"
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    second_task_Modules 
 * @{  
 */

/**
 * @defgroup      second_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      second_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      second_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      second_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      second_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      second_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Second_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      second_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      second_task_Functions 
 * @brief         
 * @{  
 */


uint32_t Second_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Second_Task,\
							"Second_Task",\
							1024,
							NULL,
							4,
							&Second_Task_Handle);
	return basetype;
}

void Second_Task(void * pvParameter)
{
	DEBUG("Second Task Enter\r\n");
	while(1)
	{
		DEBUG("Second Task Looping\r\n");
		vTaskDelay(pdMS_TO_TICKS(3000));

	}
	
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

