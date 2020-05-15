/**
 **************************************************************************************************
 * @file        bsp_adc.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_adc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_adc_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Exported_Functions 
 * @{  
 */
void BSP_ADC_Init(void);
void BSP_ADC_DeInit(void);
uint32_t BSP_ADC_GetValue(uint8_t channel);

uint16_t BSP_ADC_GetAverageValue(uint8_t channel);
void BSP_ADC_ShowValue(void);
void BSP_ADC_DisableIRQ(void);
void BSP_ADC_EnableIRQ(void);
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
