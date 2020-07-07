/**
 **************************************************************************************************
 * @file        period_task.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "period_task.h"
#include "clog.h"
#include "rtos_tools.h"


/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_uart.h"
#include "bsp_adc.h"

#include "first_task.h"
#include "period_task.h"
#include "modbus_task.h"
#include "sample_task.h"
#include "refresh_task.h"
#include "hal_task.h"


#include "bsp_lmt01.h"
/**
 * @addtogroup    period_task_Modules 
 * @{  
 */

/**
 * @defgroup      period_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      period_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      period_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      period_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      period_task_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      period_task_Public_Variables 
 * @brief         
 * @{  
 */
TaskHandle_t  Period_Task_Handle = NULL;
/**
 * @}
 */

/**
 * @defgroup      period_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      period_task_Functions 
 * @brief         
 * @{  
 */

//#define 		PERIOD_STK_SIZE 		128  							//任务堆栈大小	
//StackType_t 	Period_TaskStack[PERIOD_STK_SIZE];			//任务堆栈
//StaticTask_t 	Period_TaskTCB;												//任务控制块

uint32_t Period_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Period_Task,\
							"Period_Task",\
							1024,
							NULL,
							1,
							&Period_Task_Handle);
	
//	Period_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Period_Task,		//任务函数
//										(const char* 	)"Period Task",		//任务名称
//										(uint32_t 		)PERIOD_STK_SIZE,	//任务堆栈大小
//										(void* 		  	)NULL,				//传递给任务函数的参数
//										(UBaseType_t 	) 1, 	//任务优先级
//										(StackType_t*   )Period_TaskStack,	//任务堆栈
//										(StaticTask_t*  )&Period_TaskTCB);	//任务控制块              
//		
		
	
	
	return basetype;
}

void Period_Task(void * pvParameter)
{
	DEBUG("Period Task Enter\r\n");
	BSP_LMT01_Power_ON();
	while(1)
	{
		//DEBUG("Period Task Looping\r\n");
		BSP_LMT01_CoreLoop();
		RTOS_Delay_ms(20);
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

