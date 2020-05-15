/**
 **************************************************************************************************
 * @file        ModbusHardwareInit.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "ModbusHardwareInit.h"
#include "ModbusRTU_Slave.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_uart.h"
#include "bsp_tim.h"
#include "clog.h"
/**
 * @addtogroup    ModbusHardwareInit_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusHardwareInit_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Macros_Defines 
 * @brief         
 * @{  
 */
   
/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void modbusGPIOInit(void);
static void modbusUartInit(void);
static void modbusTimInit(void);
/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Functions 
 * @brief         
 * @{  
 */
static void modbusGPIOInit(void)
{

}

static void modbusUartInit(void)
{
	BSP_UART_Init(BSP_485COM);
	BSP_UART_SetBaudRate(BSP_485COM, 115200);
} 

static void modbusTimInit(void)
{
	BSP_Tim_Init(BSP_TIM0);
}

void ModbusFunctionInit(void)
{
    modbusGPIOInit();
    modbusUartInit();  
	modbusTimInit();
	
	ModbusRingBufInit();
    ModbusSlaveInit();
}

void ModbusSend(uint8_t * Data,uint16_t Len)
{
	BSP_UART_WriteBytes_DMA(BSP_485COM ,Data, Len);
	
	if(*Data == 0x04)
	{
		DEBUG("something err\r\n");
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

