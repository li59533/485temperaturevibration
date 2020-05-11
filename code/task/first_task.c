/**
 **************************************************************************************************
 * @file        first_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "limits.h"
#include "clog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "first_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */


/**
 * @addtogroup    first_task_Modules 
 * @{  
 */

/**
 * @defgroup      first_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t first_task_tim;
TaskHandle_t  First_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      first_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      first_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void first_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      first_task_Functions 
 * @brief         
 * @{  
 */

uint32_t First_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(First_Task,\
							"First Task",\
							1024,
							NULL,
							3,
							&First_Task_Handle);
	return basetype;
}


void First_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("First Task Enter\r\n");
	UBaseType_t firsttask_ramainheap = 0;

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & FIRST_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("First Task Looping\r\n");
			firsttask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("First Task ramain heap:%d %%\r\n",firsttask_ramainheap);
	
		}
		if((event_flag & FIRST_TASK_TEST2_EVENT) != 0x00)
		{
			DEBUG("First Task FIRST_TASK_TEST2_EVENT\r\n");
		}		
		
		
	}
	
}


void First_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(First_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(First_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void First_Task_Tim_Init(void)
{
	first_task_tim = xTimerCreate(	"FirstTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									first_task_tim_callback );
}

void First_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( first_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( first_task_tim,0);
}
static void first_task_tim_callback(TimerHandle_t xTimer)
{
	//First_Task_Event_Start(First_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

