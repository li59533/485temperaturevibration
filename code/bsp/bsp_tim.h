/**
 **************************************************************************************************
 * @file        bsp_tim.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_tim_Exported_Macros 
 * @{  
 */
#define		BSP_TIM0  0
#define		BSP_TIM1  1
#define 	BSP_TIM2  2


/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Exported_Functions 
 * @{  
 */
void BSP_Tim_DeInit(uint8_t BSP_TIMx);
void BSP_Tim_Init(uint8_t BSP_TIMx);
uint32_t BSP_GetTimrCurCount(uint8_t BSP_TIMx);
void BSP_Tim_StartOnceTimer(uint8_t BSP_TIMx , uint32_t msec);

void BSP_Tim_0_StartOnce(void);
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
