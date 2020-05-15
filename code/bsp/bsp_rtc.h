/**
 **************************************************************************************************
 * @file        bsp_rtc.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_RTC_H_
#define _BSP_RTC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_rtc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_rtc_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Exported_Functions 
 * @{  
 */

void BSP_RTC_Init(void);
void BSP_RTC_Stop(void);
void BSP_RTC_SetDate(rtc_datetime_t *datetime);
void BSP_RTC_GetDate(rtc_datetime_t *datetime);
uint32_t BSP_RTC_GetCurTimeStamp(void);
void BSP_RTC_SetTimeStamp(uint32_t timestamp);
uint32_t BSP_RTC_ConvertDatetimeToSeconds(rtc_datetime_t *datetime);
void BSP_RTC_ConvertSecondsToDatetime(uint32_t seconds ,  rtc_datetime_t *datetime);
void BSP_RTC_SetAlarm_InTime(rtc_datetime_t *alarmTime);
void BSP_RTC_SetAlarm_InTimeStamp(uint32_t timestamp);
void BSP_RTC_SetAlarm_InSec(uint32_t sec);
void BSP_RTC_AlarmInterruptEnable(void);


// -----Test Func-----------
void BSP_ShowDate(void);
void BSP_RTC_Test(void);
// -------------------------


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
