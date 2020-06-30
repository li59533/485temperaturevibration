
/**
 **************************************************************************************************
 * @file        bsp_calctools.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_calctools.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_calctools_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_calctools_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_calctools_Constants_Defines 
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_calctools_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_calctools_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_calctools_Functions 
 * @brief         
 * @{  
 */

// ------------------ Time domain filtering --------------------------

int8_t BSP_Calctools_IIR_Filter(uint8_t iir_order , float * iir_coeffs , float * calc_array , float * result_array , uint32_t count)
{
	arm_biquad_casd_df1_inst_f32 S;
	if( (iir_order % 2) != 0)
	{
		return -1;
	}
	
	if(sizeof(iir_coeffs) != (5 * iir_order / 2))
	{
		return -2;
	}
	
	
	float * iir_state  = 0;

	iir_state = pvPortMalloc(sizeof(float) * 2 * iir_order );

	arm_biquad_cascade_df1_init_f32( &S, iir_order / 2 , iir_coeffs , iir_state );	
	arm_biquad_cascade_df1_f32(&S, calc_array, result_array, count);		
	vPortFree(iir_state);

	return 1;
}

// --------------------------------------------------------------------


// -------------------Time domain integral ----------------------------

void BSP_Calctools_TimeDomainIntergral(float * calc_array , float * result_array , uint32_t count )
{
	result_array[0] = calc_array[0];
	
	for( uint32_t i = 1 ; i < count ; i ++ )
	{
		result_array[i] = result_array[i - 1] + calc_array[i];
	}
}

// --------------------------------------------------------------------





/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

