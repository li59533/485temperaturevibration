/**
 **************************************************************************************************
 * @file        app_refresh.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_REFRESH_H_
#define _APP_REFRESH_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_refresh_Modules 
 * @{  
 */

/**
 * @defgroup      app_refresh_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Exported_Functions 
 * @{  
 */
void APP_RefreshMB_Charateristic(void);
void APP_RefreshMB_ConfParam(void);
void APP_RefreshMB_Waveform(void);
void APP_Refresh_MoveWavetoMB(uint8_t channel , float * buf  );
void APP_Refresh_MBtoSys(void);
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
