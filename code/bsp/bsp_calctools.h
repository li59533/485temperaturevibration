
/**
 **************************************************************************************************
 * @file        bsp_calctools.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_CALCTOOLS_H_
#define _BSP_CALCTOOLS_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "FreeRTOS.h"
#include "MK24F25612.h"
#include "arm_math.h"



/**
 * @addtogroup    bsp_calctools_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_calctools_Exported_Macros 
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_calctools_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Exported_Functions 
 * @{  
 */
 
/*
param: 
	iir_order  ->   order count ,if the is 3 , this iir_order is 4 . it is a multiple of 2;
	iir_coeffs ->   this is a array of 5*( iir_order / 2),
	calc_array ->   original wave 
	result_array -> wave , after filter
	count -> the wave count 

*/ 
int8_t BSP_Calctools_IIR_Filter(uint8_t iir_order , \
								float * iir_coeffs , \
								float * calc_array , \
								float * result_array , \
								uint32_t count);

void BSP_Calctools_TimeDomainIntergral(float * calc_array , float * result_array , uint32_t count );


								
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
