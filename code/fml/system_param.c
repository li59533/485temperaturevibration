/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *              
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_param.h"
#include "bsp_flash.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "crc.h"


/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */
const SystemParam_Config_t SystemParam_Config_Default = 
{
	.SNcode = {0x12 , 0x55},
};
/**
 * @}
 */

/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
// 12B -> 8B
static void sys_makeUIDtoSNcode(void);
/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
 
 
 
void SystemParam_Init(void)
{		
	BSP_Flash_ReadBytes(SYS_PARAM_SAVE_FLASH_FIRSTHEAD, (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config) );
	if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0) // Same Save
	{
		DEBUG("SYS First Read OK\r\n");
	}
	else
	{
		BSP_Flash_ReadBytes(SYS_PARAM_SAVE_FLASH_SECONDHEAD, (uint8_t *)&g_SystemParam_Config , sizeof(g_SystemParam_Config) );
		if(CRC16_Modbus((uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config)) == 0)
		{
			
			DEBUG("SYS Second Read OK\r\n");
		}
		else
		{
			SystemParam_Reset();
		}
	}

}
// 12B -> 8B
static void sys_makeUIDtoSNcode(void)
{
//	sim_uid_t sim_uid ; 
//	uint8_t uid[12] = { 0 };
//	uint8_t crc_temp[2] = { 0 };
//	uint8_t sn_temp[8] = { 0 }; 
//	uint16_t temp = 0;
//	SIM_GetUniqueId(&sim_uid);
//	memcpy(uid,(uint8_t *)&sim_uid , 12);
//	
//	crc_temp[0] = uid[0];
//	crc_temp[1] = uid[11];
//	temp = CRC16_Modbus(crc_temp,2);
//	memcpy(&sn_temp[0] , (uint8_t *)&temp , 2);
//	
//	crc_temp[0] = uid[1];
//	crc_temp[1] = uid[10];
//	temp = CRC16_Modbus(crc_temp,2);
//	memcpy(&sn_temp[2] , (uint8_t *)&temp , 2);	
//	
//	crc_temp[0] = uid[2];
//	crc_temp[1] = uid[9];
//	temp = CRC16_Modbus(crc_temp,2);
//	memcpy(&sn_temp[4] , (uint8_t *)&temp , 2);	
//		
//	temp = CRC16_Modbus(&uid[3],6);
//	memcpy(&sn_temp[6] , (uint8_t *)&temp , 2);	
//			
//	memcpy(g_SystemParam_Config.SNcode ,sn_temp , 8);
	
}


int16_t SystemParam_Read(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
            if (1)
            {
                
            }
            break;
        }
    }
    return 0;
}

void SystemParam_Save(void)
{
	g_SystemParam_Config.crc = CRC16_Modbus((uint8_t*)&g_SystemParam_Config, sizeof(g_SystemParam_Config) - sizeof(g_SystemParam_Config.crc));
	BSP_Flash_WriteBytes(SYS_PARAM_SAVE_FLASH_FIRSTHEAD,(uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
	BSP_Flash_WriteBytes(SYS_PARAM_SAVE_FLASH_SECONDHEAD,(uint8_t *)&g_SystemParam_Config,sizeof(g_SystemParam_Config));
	DEBUG("Sys save\r\n");
}

void SystemParam_Reset(void)
{
	g_SystemParam_Config = SystemParam_Config_Default;
	sys_makeUIDtoSNcode();

	SystemParam_Save();
	DEBUG("SystemParam_Reset Load DefaultConf\r\n");

}

void SystemParam_Apply(uint8_t handle)
{
    switch (handle)
    {
        case SYSTEMPARAM_CONFIG:
        {
 
            break;
        }
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

