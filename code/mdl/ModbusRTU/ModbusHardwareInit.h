/**
 **************************************************************************************************
 * @file        ModbusHardwareInit.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUSHARDWAREINIT_H_
#define _MODBUSHARDWAREINIT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    ModbusHardwareInit_Modules 
 * @{  
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      ModbusHardwareInit_Exported_Functions 
 * @{  
 */
void ModbusFunctionInit(void);
void ModbusSend(uint8_t * Data,uint16_t Len);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif
