/**
 **************************************************************************************************
 * @file        modbus_task.c
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
#include "modbus_task.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "ModbusRTU_Slave.h"
#include "ModbusHardwareInit.h"
/**
 * @addtogroup    modbus_task_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_task_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_task_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      modbus_task_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_task_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      modbus_task_Private_Variables 
 * @brief         
 * @{  
 */
TimerHandle_t modbus_task_tim;
TaskHandle_t  Modbus_Task_Handle = NULL;

/**
 * @}
 */
 
/**
 * @defgroup      modbus_task_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_task_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void modbus_task_tim_callback(TimerHandle_t xTimer);
/**
 * @}
 */

/**
 * @defgroup      modbus_task_Functions 
 * @brief         
 * @{  
 */

uint32_t Modbus_Task_Init(void)
{
	BaseType_t basetype = { 0 };
	basetype = xTaskCreate(Modbus_Task,\
							"Modbus Task",\
							1024,
							NULL,
							3,
							&Modbus_Task_Handle);
	return basetype;
}


void Modbus_Task(void * pvParameter)
{
	uint32_t event_flag = 0;
	ModbusFunctionInit();
	DEBUG("Modbus Task Enter\r\n");
	UBaseType_t modbustask_ramainheap = 0;

	while(1)
	{
		xTaskNotifyWait(0x00,ULONG_MAX,&event_flag , portMAX_DELAY);
		
		if((event_flag & MODBUS_TASK_TEST_EVENT) != 0x00)
		{
			DEBUG("Modbus Task Looping\r\n");
			modbustask_ramainheap = uxTaskGetStackHighWaterMark(NULL);
			DEBUG("Modbus Task ramain heap:%d %%\r\n",modbustask_ramainheap);
	
		}
		
		if((event_flag & MODBUS_TASK_DATAPROCESS_EVENT) != 0x00)
		{
			ModbusDataProcess();
			DEBUG("MODBUS_TASK_DATAPROCESS_EVENT\r\n");
		}		
	}
}


void Modbus_Task_Event_Start(uint32_t events, uint8_t event_from)
{
	switch(event_from)
	{
		case EVENT_FROM_TASK:
		{
			xTaskNotify(Modbus_Task_Handle , events , eSetBits);
		}
		break;
		case EVENT_FROM_ISR:
		{
			xTaskNotifyFromISR(Modbus_Task_Handle, events, eSetBits , NULL);
		}
		break;
		default:break;
	}
}




void Modbus_Task_Tim_Init(void)
{
	modbus_task_tim = xTimerCreate(	"ModbusTimOUT",			/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
									pdMS_TO_TICKS(1000),
									pdTRUE,
									NULL,
									modbus_task_tim_callback );
}

void Modbus_Task_StartTim(uint16_t time_count)
{
	xTimerChangePeriod( modbus_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStart( modbus_task_tim,0);
}

void Modbus_Task_StartTimFromISR(uint16_t time_count)
{
	xTimerChangePeriodFromISR( modbus_task_tim,  pdMS_TO_TICKS(time_count) , 0 );
	xTimerStartFromISR( modbus_task_tim,0);
}

static void modbus_task_tim_callback(TimerHandle_t xTimer)
{

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

