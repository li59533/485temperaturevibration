/**
 **************************************************************************************************
 * @file        bsp_lmt01.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_LMT01_H_
#define _BSP_LMT01_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_lmt01_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lmt01_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Exported_Types 
 * @{  
 */
typedef enum
{
	LMT01_Pulse_ON = 1,
	LMT01_Pulse_OFF ,
	LMT01_Pulse_Wait , 
	LMT01_Updata_HasUp ,
	LMT01_Updata_NoUp ,
}bsp_lmt01_status_e;
/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Exported_Functions 
 * @{  
 */
void BSP_LMT01_Power_ON(void);
void BSP_LMT01_Power_OFF(void);
void BSP_LMT01_CoreLoop(void);  //call this func in 20ms
uint8_t BSP_LMT01_GetDataStatus(void);
float BSP_LMT01_GetValue(void);

// ----------TestFunc ----------
void BSP_LMT01_TestFunc(void);
// -----------------------------

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
