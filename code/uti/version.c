/**
 **************************************************************************************************
 * @file        version.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "version.h"
/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       version_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       version_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Private_Variables 
 * @brief         
 * @{  
 */
static char version_buf[30] = {0};
/**
 * @}
 */

/**
 * @defgroup      version_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Functions 
 * @brief         
 * @{  
 */
uint32_t Version_Get_Bin(void)
{
	uint32_t version = 0;
	version = VERSION_MAJOR * 256 * 256 | VERSION_MINOR * 256 | VERSION_LITE;
	return version;
}

char * Version_Get_Str(void)
{
	snprintf(version_buf,30,"%d.%d.%d",VERSION_MAJOR,VERSION_MINOR,VERSION_LITE);
	return version_buf;
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

