/**
 **************************************************************************************************
 * @file        refresh_task.c
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
#include "refresh_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_calc.h"
#include "app_refresh.h"

/**
 * @addtogroup    refresh_task_Modules 
 * @{  
 */

/**
 * @defgroup      refresh_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      refresh_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      refresh_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      refresh_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      refresh_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t refresh_task_tim;
TaskHandle_t  Refresh_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      refresh_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      refresh_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void refresh_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      refresh_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Refresh_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Refresh_Task,\
							"Refresh Task",\
							128,
							NULL,
							3,
							&Refresh_Task_Handle);
	return basetype;
}


void Refresh_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("Refresh Task Enter\r\n");
	UBaseType_t refreshtask_ramainheap = 0;

	APP_RefreshMB_ConfParam();
	
	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & REFRESH_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Refresh Task Looping\r\n");
			refreshtask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Refresh Task ramain heap:%d %%\r\n",refreshtask_ramainheap);
		}
		if((event_flag & REFRESH_TASK_CHARATERISTIC_EVENT) != 0x00)
		{
			DEBUG("Refresh Task CHARATERISTIC_EVENT\r\n");
			APP_RefreshMB_Charateristic();
		}	

		if((event_flag & REFRESH_TASK_WAVE_EVENT) != 0x00)
		{
			DEBUG("Refresh Task WAVE_EVENT\r\n");
		}	
		if((event_flag & REFRESH_TASK_CONF_EVENT) != 0x00)
		{
			DEBUG("Refresh Task CONF_EVENT\r\n");
			APP_RefreshMB_ConfParam();
		}	
		
	}
}


void Refresh_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Refresh_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Refresh_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Refresh_Task_Tim_Init(void)
{
	refresh_task_tim = xTimerCreate(	"RefreshTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									refresh_task_tim_callback );
}

void Refresh_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( refresh_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( refresh_task_tim,0);
}
static void refresh_task_tim_callback(TimerHandle_t xTimer)
{
	//Refresh_Task_Event_Start(Refresh_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

