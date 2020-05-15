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
 
/*
00> PFlash:Example Start 
00> 
00> PFlash:Information 
00> Total:Program_Flash_Size: 256KB, Hex:(0x40000)
00> Program:Flash_Sector_Size: 4KB, Hex:(0x400 * 4)
*/ 
 

 
void BSP_Flash_Init(void)
{	
	uint32_t pflashBlockBase = 0;
    uint32_t pflashTotalSize = 0;
    uint32_t pflashSectorSize = 0;
	
	FLASH_Init( &bsp_flashconfig);
	
    /* Get flash properties*/
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashBlockBaseAddr, &pflashBlockBase);
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashTotalSize, &pflashTotalSize);
    FLASH_GetProperty(&bsp_flashconfig, kFLASH_PropertyPflashSectorSize, &pflashSectorSize);	
	
    DEBUG("\r\n PFlash Information: ");
    DEBUG("\r\n Total Program Flash Size:\t%d KB, Hex: (0x%x)\r\n", (pflashTotalSize / 1024), pflashTotalSize);
    DEBUG("\r\n Program Flash Sector Size:\t%d KB, Hex: (0x%x) \r\n", (pflashSectorSize / 1024), pflashSectorSize);	
	
}	

int8_t BSP_Flash_WriteBytes(uint32_t AddrStart,uint8_t *buf,uint16_t len)
{
	uint8_t flash_temp[0x400 * 4] = { 0 };
	BSP_Flash_ReadBytes( AddrStart, flash_temp , 0x400 * 4);
	
	memcpy(flash_temp ,buf ,len );
	
	__disable_irq();
	FLASH_Erase(&bsp_flashconfig, AddrStart , 0x400 * 4, kFLASH_ApiEraseKey);
	FLASH_Program(&bsp_flashconfig, AddrStart ,(uint32_t *) flash_temp, 0x400 * 4);
	__enable_irq();
	return 0;
}

void BSP_Flash_ReadBytes(uint32_t AddrStart, uint8_t *buf , uint16_t len)
{
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

