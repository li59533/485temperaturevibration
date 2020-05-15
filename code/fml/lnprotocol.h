/**
 **************************************************************************************************
 * @file        lnprotocol.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _LNPROTOCOL_H_
#define _LNPROTOCOL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    lnprotocol_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_Exported_Macros 
 * @{  
 */
#define LNPROTOCOL_HEAD			0X7E

#define LNPROTOCOL_FOOT			0X7E


/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_Exported_Types 
 * @{  
 */
typedef enum 
{
	TAG_CONF_SN      	= 1,
	TAG_CONF_X_K		= 2,
	TAG_CONF_Y_K		= 3,
	TAG_CONF_Z_K		= 4,
	TAG_CONF_X_ADC_K	= 5,
	TAG_CONF_Y_ADC_K	= 6,
	TAG_CONF_Z_ADC_K	= 7,
	TAG_CONF_CUR_BATTERY = 8,
	TAG_CONF_RTC		= 9,
	TAG_CONF_SLEEPTIME 	= 10

}LN_Protocol_Conf_Tag_e;

typedef enum
{
	TAG_X_ACC_VALUE 	 = 1,
	TAG_X_SPEED_VALUE 	 = 2,
	TAG_X_DISPLACE_VALUE = 3,
	TAG_X_KURTOSIS_VALUE = 4,
	TAG_X_ENVELOPE_VALUE = 5,
	
	TAG_Y_ACC_VALUE 	 = 6,
	TAG_Y_SPEED_VALUE 	 = 7,
	TAG_Y_DISPLACE_VALUE = 8,
	TAG_Y_KURTOSIS_VALUE = 9,
	TAG_Y_ENVELOPE_VALUE = 10,
	
	TAG_Z_ACC_VALUE 	 = 11,
	TAG_Z_SPEED_VALUE 	 = 12,
	TAG_Z_DISPLACE_VALUE = 13,
	TAG_Z_KURTOSIS_VALUE = 14,
	TAG_Z_ENVELOPE_VALUE = 15,	
	TAG_TEMPERATURE    	 = 16,
	TAG_BATTERY			 = 17,	
	
	
}LN_Protocol_ReportData_Tag_e;



typedef enum
{
	CONF_SUCCESS = 1,
	CONF_ERROR	 = 2,
}LN_Conf_Status_e;


typedef enum
{
	
	CMD_Conf_Stop	 	= 0x00 ,
	CMD_Conf_Start	 	= 0x01,
	CMD_Conf_ID		 	= 0x02,
	CMD_Conf_ChannelKind = 0x03,
	CMD_Conf_Reply_Conf	= 0x04,
	CMD_Conf_Set_Conf	= 0x05,
	CMD_Conf_Reply_Sample_Rate	= 0x06,
	CMD_Conf_Set_Sample_Rate = 0x07,
	CMD_Conf_Reply_SelfStart = 0x08,
	CMD_Conf_Set_SelfStart	= 0x09,
	CMD_Conf_Set_EQ		= 0x0a,
	
	CMD_ReportData	 = 0x45,
	CMD_Conf_GotoLowpower = 0x46,
	CMD_Conf_Reply_AlarmTime = 0x47,
	CMD_Conf_Set_AlarmTime = 0x49,
	CMD_ReportDataACK = 0x50,
	
	CMD_Conf_Calibration = 0x69,
	
	CMD_Conf_ADCToRealValue = 0x6A,
	
	CMD_Conf_Set_SNcode = 0x88,
	// ------
	
	CMD_Conf_GetVersion = 0xA0
	
	// ------
}LN_Protocol_Cmd_e;



#pragma pack(1)
typedef struct
{
	uint8_t Tag;
	uint8_t Len;
	union 
	{
		uint8_t BIT_8;
		uint16_t BIT_16;
		uint32_t BIT_32;
		uint8_t Array[20];
	}Value;
}LN_Tlv_t;


typedef struct
{
	uint8_t head;
	uint8_t cmd;
	uint16_t len;
	uint8_t * payload;
	uint8_t sum;
	uint8_t foot;

}ln_protocolintance_t;




#pragma pack()

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_Exported_Functions 
 * @{  
 */
uint8_t * LNprotocol_AddHead(uint8_t * targetspace_ptr); // return the value ptr

uint8_t * LNprotocol_AddValue(uint8_t * targetspace_ptr , uint8_t *buf,uint8_t len);

uint8_t * LNprotocol_AddFoot(uint8_t * targetspace_ptr);

void LNprotocol_Addlen(uint8_t *buf, uint16_t len);

uint8_t LNprotocol_AddChecksum(uint8_t * buf,uint16_t len);
uint16_t LNprotocol_GetChecksum116bits(uint8_t *buf , uint16_t len);
uint8_t LN_AddTlv(uint8_t * disaddr,LN_Tlv_t * tlv_value);


uint8_t * LNprotocol_AddPayload(uint8_t * buf_ptr , uint8_t * payload , uint16_t len);
uint8_t LNprotocol_GetChecksum(uint8_t *buf , uint16_t len);
int8_t LNprotocol_Checksum(uint8_t * buf,uint16_t len);  // enter a complete buf

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
