/**
 **************************************************************************************************
 * @file        bsp_flash.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_flash_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_flash_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_flash_Exported_Functions 
 * @{  
 */
 
 
void BSP_Flash_Init(void); 
int8_t BSP_Flash_WriteBytes(uint32_t AddrStart,uint8_t *buf,uint16_t len); 
void BSP_Flash_ReadBytes(uint32_t AddrStart, uint8_t *buf , uint16_t len);

void BSP_Flash_Test(void);
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
