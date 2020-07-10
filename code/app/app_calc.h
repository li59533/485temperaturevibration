/**
 **************************************************************************************************
 * @file        app_calc.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_CALC_H_
#define _APP_CALC_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_calc_Modules 
 * @{  
 */

/**
 * @defgroup      app_calc_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Exported_Types 
 * @{  
 */
typedef struct 
{
	float ACC_P;
	float ACC_RMS;
	float Velocity_RMS;
	float Displace_PP;
	float Displace_RMS;
	float Kurtosis_Coefficient;
	float Envelope;
	uint32_t BaseFreq;
}APP_CalcValue_t ;
/**
 * @}
 */

/**
 * @defgroup      app_calc_Exported_Variables 
 * @{  
 */
extern APP_CalcValue_t APP_CalcValue[] ; 
/**
 * @}
 */

/**
 * @defgroup      app_calc_Exported_Functions 
 * @{  
 */
void APP_Calc_Process(void);
void APP_Calc_Z_SelfCal(void);
void APP_Calc_X_SelfCal(void);
void APP_Calc_Y_SelfCal(void);

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
