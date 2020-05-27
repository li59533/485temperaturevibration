/**
 **************************************************************************************************
 * @file        modbus_port.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUS_PORT_H_
#define _MODBUS_PORT_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    modbus_port_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_port_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Exported_Variables 
 * @{  
 */
extern uint8_t Uart2RBuf[20];
extern uint8_t Uart2RBuf_Ptr;
/**
 * @}
 */

/**
 * @defgroup      modbus_port_Exported_Functions 
 * @{  
 */
 
void ModbusFunctionInit(void); 
void ModbusRevOneByte(uint8_t byte);
void ModbusSend(uint8_t * Data,uint16_t Len);
void ModbusUartIRQn(void) ;
void ModbusTimIRQn(void);
void Modbus_485en_R(void);
void Modbus_485en_T(void);


unsigned short ModbusCRC(unsigned char *ptr, unsigned char size);

unsigned short checkCRC(unsigned char *ptr, unsigned char size);
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
