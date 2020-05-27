/**
 **************************************************************************************************
 * @file        hal_task.c
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

#include "hal_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_calc.h"
#include "system_param.h"
#include "app_sample.h"
#include "app_hal.h"
/**
 * @addtogroup    hal_task_Modules 
 * @{  
 */

/**
 * @defgroup      hal_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t hal_task_tim;
TaskHandle_t  Hal_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      hal_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      hal_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void hal_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      hal_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Hal_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Hal_Task,\
							"Hal Task",\
							1024,
							NULL,
							4,
							&Hal_Task_Handle);
	return basetype;
}


void Hal_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("Hal Task Enter\r\n");
	UBaseType_t haltask_ramainheap = 0;

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & HAL_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Hal Task Looping\r\n");
			haltask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Hal Task ramain heap:%d %%\r\n",haltask_ramainheap);
	
		}
		if((event_flag & HAL_TASK_TEST2_EVENT) != 0x00)
		{
			DEBUG("Hal Task HAL_TASK_TEST2_EVENT\r\n");
			//APP_Calc_Process();
			
		}		
		if((event_flag & HAL_TASK_SAVE_SYS_EVENT) != 0x00)
		{
			RTOS_Delay_ms(100);
			DEBUG("Hal Task Save System EVENT\r\n");
			
			


			APP_StopSample();
			
			taskENTER_CRITICAL();
			//vTaskSuspendAll();
			//taskENTER_CRITICAL(); 
			//taskDISABLE_INTERRUPTS();
			SystemParam_Save();
			//taskENABLE_INTERRUPTS();
			//taskEXIT_CRITICAL();
			//xTaskResumeAll();
			taskEXIT_CRITICAL();
			
			APP_StartSample();	

			RTOS_Delay_ms(100);
			APP_Hal_Rest();
		}			
	}
}




void Hal_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Hal_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Hal_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Hal_Task_Tim_Init(void)
{
	hal_task_tim = xTimerCreate(	"HalTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									hal_task_tim_callback );
}

void Hal_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( hal_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( hal_task_tim,0);
}
static void hal_task_tim_callback(TimerHandle_t xTimer)
{
	//Hal_Task_Event_Start(Hal_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

