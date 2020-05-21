/**
 **************************************************************************************************
 * @file        bsp_fft_integral_freertos.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_FFT_INTEGRAL_H_
#define _BSP_FFT_INTEGRAL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "FreeRTOS.h"
#include "MK24F25612.h"
#include "arm_math.h"
/**
 * @addtogroup    bsp_fft_integral_freertos_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Exported_Macros 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Exported_Functions 
 * @{  
 */
void BSP_FFT_Init(uint32_t sample_rate,uint32_t pointcount , float * fftcalc_space); // sizeof fftcalc_space is sample double.
void BSP_FFT_Func(uint32_t sample_rate,uint32_t pointcount , float * inbuf , float *outbuf);
uint32_t BSP_FFT_GetBaseFreq(uint32_t sample_rate,uint32_t pointcount , float *inbuf);
void BSP_FFT_Integral_IFFT(uint32_t sample_rate,uint32_t pointcount ,uint8_t integral_count,uint32_t lowpass ,uint32_t highpass,float * inbuf , float *outbuf);


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
