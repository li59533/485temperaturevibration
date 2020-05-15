/**
 **************************************************************************************************
 * @file        system_param.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_PARAM_H_
#define _SYSTEM_PARAM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_Exported_Macros 
 * @{  
 */
												
#define SYS_PARAM_SAVE_FLASH_FIRSTHEAD   		0x0003E000
#define SYS_PARAM_SAVE_FLASH_SECONDHEAD			0x0003F000

#define SYSTEMPARAM_CONFIG     0



/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Types 
 * @{  
 */
 
typedef enum
{
	Normal_WorkingMode = 0,
	LowPower_WorkingMode ,
}WorkMode_e;	
 
 
 
#pragma pack(1)



typedef struct
{
	uint8_t SNcode[8];

    uint16_t crc;           /*!< ���еĲ����ṹ����밴�ֽڶ��䡣�����һ�������
                                 ��һ��uint16_t���͵����ݣ������������ڲ��洢ʱ��
                                 crcУ��ʹ洢���û��ڱ������ʱ���ù��ĸ�ֵ��ֵ��*/
}SystemParam_Config_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Variables 
 * @{  
 */
extern SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Functions 
 * @{  
 */
void SystemParam_Init(void);

int16_t SystemParam_Read(uint8_t handle);

void SystemParam_Save(void);

void SystemParam_Reset(void);

void SystemParam_Apply(uint8_t handle);
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
