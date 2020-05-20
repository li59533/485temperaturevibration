/**
 **************************************************************************************************
 * @file        app_sample.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_SAMPLE_H_
#define _APP_SAMPLE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_sample_Modules 
 * @{  
 */

/**
 * @defgroup      app_sample_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Functions 
 * @{  
 */
void APP_Sample_Init(void);
void APP_StartSample(void);
void APP_StopSample(void);

void APP_GetOriginalData( uint16_t data);
void APP_SetNextQriginalChannel_Process(void);
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
