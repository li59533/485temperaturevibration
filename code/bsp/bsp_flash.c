/**
 **************************************************************************************************
 * @file        bsp_flash.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"

#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_flash.h"
/**
 * @addtogroup    bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_flash_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_flash_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_flash_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Private_Variables 
 * @brief         
 * @{  
 */
flash_config_t bsp_flashconfig ;  
/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Functions 
 * @brief         
 * @{  
 */
 
void error_trap(void)
{
    DEBUG("\r\n\r\n\r\n\t---- HALTED DUE TO FLASH ERROR! ----");
    while (1)
    {
    }
}
void app_finalize(void)
{
    /* Print finished message. */
    DEBUG("\r\n End of PFlash Example \r\n");
    while (1)
    {
    }
}
 
 
/*
00> PFlash:Example Start 
00> 
00> PFlash:Information 
00> Total:Program_Flash_Size: 256KB, Hex:(0x40000)
00> Program:Flash_Sector_Size: 4KB, Hex:(0x400 * 4)
*/ 
 
uint32_t pflashBlockBase = 0;
uint32_t pflashTotalSize = 0;
uint32_t pflashSectorSize = 0;
 
void BSP_Flash_Init(void)
{	
	status_t result;
	flash_security_state_t securityStatus = kFLASH_SecurityStateNotSecure; /* Return protection status */
	
	memset(&bsp_flashconfig, 0, sizeof(flash_config_t));
	result = FLASH_Init( &bsp_flashconfig);
	if (kStatus_FLASH_Success != result)
    {
        error_trap();
    }
    /* Get flash properties*/
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashBlockBaseAddr, &pflashBlockBase);
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashTotalSize, &pflashTotalSize);
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashSectorSize, &pflashSectorSize);	
	
    DEBUG("\r\n PFlash Information: ");
	DEBUG("\r\n pflashBlockBase:Hex: (0x%x)\r\n",  pflashBlockBase);
	
    DEBUG("\r\n Total Program Flash Size:\t%d KB, Hex: (0x%x)\r\n", (pflashTotalSize / 1024), pflashTotalSize);
    DEBUG("\r\n Program Flash Sector Size:\t%d KB, Hex: (0x%x) \r\n", (pflashSectorSize / 1024), pflashSectorSize);	
	
    /* Check security status. */
    result = FLASH_GetSecurityState(&bsp_flashconfig, &securityStatus);
    if (kStatus_FLASH_Success != result)
    {
        error_trap();
    }
    /* Print security status. */
    switch (securityStatus)
    {
        case kFLASH_SecurityStateNotSecure:
            DEBUG("\r\n Flash is UNSECURE!");
            break;
        case kFLASH_SecurityStateBackdoorEnabled:
            DEBUG("\r\n Flash is SECURE, BACKDOOR is ENABLED!");
            break;
        case kFLASH_SecurityStateBackdoorDisabled:
            DEBUG("\r\n Flash is SECURE, BACKDOOR is DISABLED!");
            break;
        default:
            break;
    }
    DEBUG("\r\n");	
	
	
}	
#include "cmsis_armcc.h"
static uint8_t flash_temp[0x400 * 4] = { 0 };
int8_t BSP_Flash_WriteBytes(uint32_t AddrStart,uint8_t *buf,uint16_t len)
{
	uint32_t  failAddr, failDat;
	int32_t status_temp = 0;
	//uint8_t flash_temp[0x400 * 4] = { 0 };
	BSP_Flash_ReadBytes( AddrStart, flash_temp , 0x400 * 4);
	
	memcpy(flash_temp ,buf ,len );
	
	__set_PRIMASK(1);
	//__disable_irq();
	status_temp = FLASH_Erase(&bsp_flashconfig, AddrStart , pflashSectorSize, kFLASH_ApiEraseKey);
	DEBUG("Flash:%d\r\n" , status_temp);
	status_temp = FLASH_VerifyErase(&bsp_flashconfig, AddrStart, pflashSectorSize, kFLASH_MarginValueUser);
	DEBUG("Flash:%d\r\n" , status_temp);
	status_temp = FLASH_Program(&bsp_flashconfig, AddrStart ,(uint32_t *) flash_temp, pflashSectorSize );
	DEBUG("Flash:%d\r\n" , status_temp);
	status_temp = FLASH_VerifyProgram(&bsp_flashconfig, AddrStart, pflashSectorSize , (uint32_t *) flash_temp, kFLASH_MarginValueUser,
                                     &failAddr, &failDat);	
	DEBUG("Flash:%d ,failAddr:%d ,failDat:%d\r\n" , status_temp ,failAddr ,failDat);
	//__enable_irq();
	__set_PRIMASK(0);
	return 0;
}

void BSP_Flash_ReadBytes(uint32_t AddrStart, uint8_t *buf , uint16_t len)
{
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
        /* Clean the D-Cache before reading the flash data*/
        SCB_CleanInvalidateDCache();
#endif	
	uint16_t i = 0 ;
	for(i = 0; i < len ; i ++)
	{
		buf[i] = *(uint8_t *)(AddrStart + i );
	}	
}

// ------------Test ----------------
void BSP_Flash_Test(void)
{
	DEBUG("BSP_Flash_Test\r\n");
}

// ---------------------------------



/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

