/**
 **************************************************************************************************
 * @file        task_list.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "task_list.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "FreeRTOS.h"
#include "task.h"

#include "first_task.h"
#include "second_task.h"

#include "clog.h"

#include "modbus_task.h"
/**
 * @addtogroup    task_list_Modules 
 * @{  
 */

/**
 * @defgroup      task_list_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      task_list_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      task_list_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void blockling_delay(void);
/**
 * @}
 */

/**
 * @defgroup      task_list_Functions 
 * @brief         
 * @{  
 */

void RTOS_Init(void)
{
	BaseType_t basetype = { 0 };
	
	basetype = First_Task_Init();
	basetype = Second_Task_Init();
	basetype = Modbus_Task_Init();
	
	if(pdPASS == basetype)
	{
		vTaskStartScheduler();
	}
	else
	{
		while(1)
		{
			blockling_delay();
			DEBUG("RTOS is not start\r\n");
		}
	}
	
}

static void blockling_delay(void)
{
	for(uint32_t i = 0 ; i < 3000 ; i ++)
	{
		__nop();
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

