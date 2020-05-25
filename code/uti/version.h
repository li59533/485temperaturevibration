/**
 **************************************************************************************************
 * @file        version.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _VERSION_H_
#define _VERSION_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    version_Modules 
 * @{  
 */

/**
 * @defgroup      version_Exported_Macros 
 * @{  
 */
#define VERSION_MAJOR		0   // 0~255
#define VERSION_MINOR		0   // 0~255
#define VERSION_LITE		8	// 0~255

#define FRAME_VERSION_MAJOR		0   // 0~255
#define FRAME_VERSION_MINOR		0   // 0~255
#define FRAME_VERSION_LITE		3	// 0~255

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      version_Exported_Functions 
 * @{  
 */
uint32_t Version_Get_Bin(void);
char * Version_Get_Str(void);
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
