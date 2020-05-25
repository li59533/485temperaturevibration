/**
 **************************************************************************************************
 * @file        modbus_rtu.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUS_RTU_H_
#define _MODBUS_RTU_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "modbus_port.h"
/**
 * @addtogroup    modbus_rtu_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_rtu_Exported_Macros 
 * @{  
 */
#define MBREGISTERCOILS 			0
#define MBREGISTERDISCRETEINPUT    	1
#define MBREGISTERHOLDING  			2
#define MBREGISTERINPUT  			3 
 
#define MB_REG_COILS_COUNT          1
#define MB_REG_DISCRETEINPUT_COUNT	1
#define MB_REG_HOLDING_COUNT		100
#define MB_REG_INPUT_COUNT 			6500 

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Exported_Types 
 * @{  
 */
typedef struct
{
	uint8_t Buf[20];
	uint8_t Len;
}ringBuf_t;

typedef struct
{
	ringBuf_t RingData[5];
	uint8_t RingIn;
	uint8_t RingOut;
	uint8_t RingCount;
	uint8_t RingSize;
}RingArray;

typedef struct
{
    //uint8_t DataType;
    uint16_t * DataI;
    //float DataF;
}SlaveDataStruct_t;

typedef struct
{
    SlaveDataStruct_t Addr;
	uint16_t startAddr;
	uint16_t endAddr;
}SlaveAddrStruct_t;

typedef struct
{
    uint8_t Addr;
    uint8_t ID;
    uint8_t ReplyStatus;
	
	SlaveAddrStruct_t Reg_coil;
	SlaveAddrStruct_t Reg_discreteinput;
	SlaveAddrStruct_t Reg_holding ; 
	SlaveAddrStruct_t Reg_input;
            
}SlaveStruct_t;

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_rtu_Exported_Functions 
 * @{  
 */
void ModbusSlaveInit(void); //Slave ID startaddr endaddr init
void ModbusRingBufInit(void);    //RingBuf init
void rBufToRing(void);   
void ModbusDataProcess(void);
int8_t MB_WirteRegister(uint8_t Register, uint16_t Addr,uint16_t Data);       //Slave wirte register
uint16_t MB_ReadRegister(uint8_t Register, uint16_t Addr ,uint16_t *Data);    //Slave read register



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
