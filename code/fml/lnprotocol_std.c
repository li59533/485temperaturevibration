/**
 **************************************************************************************************
 * @file        lnprotocol_std.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "lnprotocol_std.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    lnprotocol_std_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_std_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_std_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_std_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_std_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Functions 
 * @brief         
 * @{  
 */

int8_t LNprotocol_STD_Checksum(uint8_t * buf,uint16_t len)  // enter a complete buf
{
	uint8_t checksum = 0;
	uint8_t * check_ptr = 0;
	uint16_t check_len = 0;
	
	check_ptr = buf + 1 ;
	check_len = len - 3 ;
	
	while(check_len --)
	{
		checksum += *(check_ptr ++);
	}
	
	if(checksum == *check_ptr)
	{
		return 1;
	}else
	{
		return -1;
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

