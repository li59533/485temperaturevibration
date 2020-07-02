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
#include "sample_task.h"
#include "refresh_task.h"
#include "hal_task.h"
#include "period_task.h"
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
	
	basetype = Modbus_Task_Init();
	basetype = Sample_Task_Init();
	//basetype = Second_Task_Init();
	basetype = Refresh_Task_Init();

	basetype = Hal_Task_Init();
	//basetype = First_Task_Init();
	basetype = Period_Task_Init();
	
	//vTaskStartScheduler();
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

static StackType_t 		IdleTaskStack[configMINIMAL_STACK_SIZE];			//空闲任务任务堆栈
static StaticTask_t 	IdleTaskTCB;																	//空闲任务控制块
static StackType_t 		TimerTaskStack[configTIMER_TASK_STACK_DEPTH];	//定时器服务任务堆栈
static StaticTask_t 	TimerTaskTCB;	

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
	*ppxIdleTaskStackBuffer=IdleTaskStack;
	*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
	*ppxTimerTaskTCBBuffer=&TimerTaskTCB;
	*ppxTimerTaskStackBuffer=TimerTaskStack;
	*pulTimerTaskStackSize=configTIMER_TASK_STACK_DEPTH;
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

