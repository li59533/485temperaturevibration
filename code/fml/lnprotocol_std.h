/**
 **************************************************************************************************
 * @file        lnprotocol_std.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _LNPROTOCOL_STD_H_
#define _LNPROTOCOL_STD_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    lnprotocol_std_Modules 
 * @{  
 */

/**
 * @defgroup      lnprotocol_std_Exported_Macros 
 * @{  
 */
#define LNPROTOCOL_STD_HEAD			0X7E
#define LNPROTOCOL_STD_FOOT			0X7E


/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      lnprotocol_std_Exported_Types 
 * @{  
 */
 

 

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      lnprotocol_std_Exported_Functions 
 * @{  
 */
int8_t LNprotocol_STD_Checksum(uint8_t * buf,uint16_t len);  // enter a complete buf
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
