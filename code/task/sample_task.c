/**
 **************************************************************************************************
 * @file        sample_task.c
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


#include "sample_task.h"
#include "rtos_tools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

#include "app_sample.h"
#include "bsp_led.h"
#include "app_calc.h"
#include "refresh_task.h"

#include "first_task.h"
/**
 * @addtogroup    sample_task_Modules 
 * @{  
 */

/**
 * @defgroup      sample_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sample_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      sample_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sample_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      sample_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t sample_task_tim;
TaskHandle_t  Sample_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      sample_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      sample_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void sample_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      sample_task_Functions 
 * @brief         
 * @{  
 */

//#define 		SAMPLE_STK_SIZE 		800  							//任务堆栈大小	
//StackType_t 	Sample_TaskStack[SAMPLE_STK_SIZE];			//任务堆栈
//StaticTask_t 	Sample_TaskTCB;												//任务控制块

uint32_t Sample_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Sample_Task,\
							"Sample Task",\
							1024,
							NULL,
							configMAX_PRIORITIES - 1,
							&Sample_Task_Handle);
	

//	Sample_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Sample_Task,		//任务函数
//										(const char* 	)"Sample Task",		//任务名称
//										(uint32_t 		)SAMPLE_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	)configMAX_PRIORITIES - 1, 	//任务优先级
//										(StackType_t*   )Sample_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Sample_TaskTCB);	//任务控制块              

	return basetype;
}


void Sample_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	
	DEBUG("Sample Task Enter\r\n");
	UBaseType_t sampletask_ramainheap = 0;

	// ----Init----
	APP_Sample_Init();
	// ------------
	
	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & SAMPLE_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Sample Task Looping\r\n");
			sampletask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Sample Task ramain heap:%d %%\r\n",sampletask_ramainheap);
		}

		if((event_flag & SAMPLE_TASK_CALC_EVENT) != 0x00)
		{
			DEBUG("Sample Task SAMPLE_TASK_CALC_EVENT\r\n");
			//taskENTER_CRITICAL();
			APP_Calc_Process();
			//taskEXIT_CRITICAL();
			Refresh_Task_Event_Start(REFRESH_TASK_CHARATERISTIC_EVENT, EVENT_FROM_TASK);
		}				
	}
}


void Sample_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Sample_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Sample_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Sample_Task_Tim_Init(void)
{
	sample_task_tim = xTimerCreate(	"SampleTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									sample_task_tim_callback );
}

void Sample_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( sample_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( sample_task_tim,0);
}
static void sample_task_tim_callback(TimerHandle_t xTimer)
{
	//Sample_Task_Event_Start(Sample_TASK_SEND_AT_EVENT, EVENT_FROM_TASK);
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

