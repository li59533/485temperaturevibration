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

//#define 		PERIOD_STK_SIZE 		128  							//�����ջ��С	
//StackType_t 	Period_TaskStack[PERIOD_STK_SIZE];			//�����ջ
//StaticTask_t 	Period_TaskTCB;												//������ƿ�

uint32_t Period_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Period_Task,\
							"Period_Task",\
							64,
							NULL,
							1,
							&Period_Task_Handle);
	
//	Period_Task_Handle=xTaskCreateStatic((TaskFunction_t	)Period_Task,		//������
//										(const char* 	)"Period Task",		//��������
//										(uint32_t 		)PERIOD_STK_SIZE,	//�����ջ��С
//										(void* 		  	)NULL,				//���ݸ��������Ĳ���
//										(UBaseType_t 	) 1, 	//�������ȼ�
//										(StackType_t*   )Period_TaskStack,	//�����ջ
//										(StaticTask_t*  )&Period_TaskTCB);	//������ƿ�              
//		
		
	
	
	return basetype;
}

void Period_Task(void * pvParameter)
{
	DEBUG("Period Task Enter\r\n");
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

