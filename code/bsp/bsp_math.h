/**
 **************************************************************************************************
 * @file        bsp_math.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_MATH_H_
#define _BSP_MATH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "FreeRTOS.h"
#include "MK24F25612.h"
#include "arm_math.h"
/**
 * @addtogroup    bsp_math_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_math_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_math_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_math_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_math_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_math_Exported_Functions 
 * @{  
 */
void bsp_math_mean(float * psrc , uint32_t count , float * result); //  mean
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
