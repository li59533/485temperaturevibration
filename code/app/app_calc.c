/**
 **************************************************************************************************
 * @file        app_calc.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "app_calc.h"
#include "app_sample.h"
#include "FreeRTOS.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
 
#include "clog.h"
#include "system_param.h"
#include "bsp_math.h"
//#include "bsp_fft_integral.h"

#include "bsp_fft_integral_freertos.h"


/**
 * @addtogroup    app_calc_Modules 
 * @{  
 */

/**
 * @defgroup      app_calc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Macros_Defines 
 * @brief         
 * @{  
 */
#define APP_CALC_ADC_SCALEFACTOR     0.050354f // 3300mv / 65536 =  0.050354
 
/**
 * @}
 */

/**
 * @defgroup      app_calc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Private_Types
 * @brief         
 * @{  
 */
typedef struct 
{
	float ACC_P;
	float ACC_RMS;
	float Velocity_RMS;
	float Displace_PP;
	float Kurtosis_Coefficient;
	float Envelope;
	uint32_t BaseFreq;
}APP_CalcValue_t ;
/**
 * @}
 */

/**
 * @defgroup      app_calc_Private_Variables 
 * @brief         
 * @{  
 */
APP_CalcValue_t APP_CalcValue[3] ; 

/**
 * @}
 */

/**
 * @defgroup      app_calc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_calc_Functions 
 * @brief         
 * @{  
 */

void APP_Calc_Process(void)
{
	float *emu_inter_data = 0;
	float *testOutput = 0;
	float *testOutput_2 = 0;
	float * fftcalc_space = 0;
	
	fftcalc_space =  pvPortMalloc(sizeof(float) * APP_SAMPLE_CHANNEL_0_RATE * 2);
	emu_inter_data = pvPortMalloc(sizeof(float) * APP_SAMPLE_CHANNEL_0_RATE); //vPortFree()
	testOutput = pvPortMalloc(sizeof(float) * APP_SAMPLE_CHANNEL_0_RATE * 2 );	
	testOutput_2 = pvPortMalloc(sizeof(float) * APP_SAMPLE_CHANNEL_0_RATE  );	
	
	float Axial_Sensitivity[3];
	
	if(g_SystemParam_Config.X_Axial_Sensitivity > 0)
	{
		Axial_Sensitivity[0] = 1.0f / g_SystemParam_Config.X_Axial_Sensitivity;
	}
	else
	{
		Axial_Sensitivity[0] = 1.0f;
	}
	
	if(g_SystemParam_Config.Y_Axial_Sensitivity > 0)
	{
		Axial_Sensitivity[1] = 1.0f / g_SystemParam_Config.Y_Axial_Sensitivity;
	}
	else
	{
		Axial_Sensitivity[1] = 1.0f;
	}	
	
	if(g_SystemParam_Config.Z_Axial_Sensitivity > 0)
	{
		Axial_Sensitivity[2] = 1.0f / g_SystemParam_Config.Z_Axial_Sensitivity;
	}
	else
	{
		Axial_Sensitivity[2] = 1.0f;
	}	

	// --------Calc 3 Channels Charateristic Value------------
	
	for(uint8_t channel_index = 0 ; channel_index < 3 ; channel_index ++)
	{
		// ------------Get ACC with DC bias--------
		if(APP_Sample_buf.Sample_Channel_buf[channel_index].cur_dataPtr >=0 &&\
			APP_Sample_buf.Sample_Channel_buf[channel_index].cur_dataPtr < APP_SAMPLE_CHANNEL_0_RATE)
		{
			for(uint16_t i = 0 ; i < APP_SAMPLE_CHANNEL_0_RATE ; i ++)
			{
				emu_inter_data[i] = APP_Sample_buf.Sample_Channel_buf[channel_index].originalData[i + 4096] * APP_CALC_ADC_SCALEFACTOR * Axial_Sensitivity[channel_index];
			}
		}
		else
		{
			for(uint16_t i = 0 ; i < APP_SAMPLE_CHANNEL_0_RATE ; i ++)
			{
				emu_inter_data[i] = APP_Sample_buf.Sample_Channel_buf[channel_index].originalData[i] * APP_CALC_ADC_SCALEFACTOR * Axial_Sensitivity[channel_index];
			}		
		}
		
		// --------------Get ACC without bias -----------
		float * mean_value = 0;
		mean_value = pvPortMalloc(sizeof(float) * 1); //vPortFree()
		arm_mean_f32(emu_inter_data ,APP_SAMPLE_CHANNEL_0_RATE ,  mean_value);
		Clog_Float("MeanValue:", *mean_value);
		
		for(uint16_t i = 0; i < APP_SAMPLE_CHANNEL_0_RATE ; i ++ )
		{
			emu_inter_data[i] -= *mean_value;
		}
		vPortFree(mean_value);
		
		// ----------------------------------------------
		
		// ------------Calc ACC_P ACC_RMS----------------
		
		arm_abs_f32(emu_inter_data,testOutput,APP_SAMPLE_CHANNEL_0_RATE);
		uint32_t pIndex = 0;
		arm_max_f32	(testOutput,APP_SAMPLE_CHANNEL_0_RATE, &APP_CalcValue[channel_index].ACC_P , &pIndex );	 // ACC_P
		arm_rms_f32(emu_inter_data, APP_SAMPLE_CHANNEL_0_RATE , &APP_CalcValue[channel_index].ACC_RMS);    // ACC_RMS	
		
		Clog_Float("ACC_P:",APP_CalcValue[channel_index].ACC_P);
		Clog_Float("ACC_RMS:",APP_CalcValue[channel_index].ACC_RMS);
		// ----------------------------------------------
		
		
		// ------------Calc Kurtosis---------------------
		float *Kurtosis_Tempbuf = 0;
		
		Kurtosis_Tempbuf = pvPortMalloc(sizeof(float) * 4096); //vPortFree();
		for(uint16_t i = 0 ; i < APP_SAMPLE_CHANNEL_0_RATE ; i ++)
		{
			Kurtosis_Tempbuf[i] = emu_inter_data[i]*emu_inter_data[i]*emu_inter_data[i]*emu_inter_data[i];
		}
		float Kurtosis ;
		arm_mean_f32(Kurtosis_Tempbuf, APP_SAMPLE_CHANNEL_0_RATE, &Kurtosis);
		vPortFree(Kurtosis_Tempbuf);
		APP_CalcValue[channel_index].Kurtosis_Coefficient = Kurtosis / (APP_CalcValue[channel_index].ACC_RMS * APP_CalcValue[channel_index].ACC_RMS * APP_CalcValue[channel_index].ACC_RMS * APP_CalcValue[channel_index].ACC_RMS); // Kurtosis_Coefficient
		
		Clog_Float("Kurtosis_Cof:",APP_CalcValue[channel_index].Kurtosis_Coefficient);
		
		// ----------------------------------------------
		
		// --------------ADD Hanni Windows---------------
	//	for(uint16_t i = 0; i < APP_SAMPLE_CHANNEL_0_RATE ; i ++ )
	//	{
	//		emu_inter_data[i] *= (0.5f - 0.5f * arm_cos_f32(2.0f * 3.14159265f * i / APP_SAMPLE_CHANNEL_0_RATE));
	//	}
		// ----------------------------------------------	
		// ------------FFT BaseFreq, Velocity_RMS ,Displace_PP -----

		
		BSP_FFT_Init(APP_SAMPLE_CHANNEL_0_RATE,APP_SAMPLE_CHANNEL_0_RATE , fftcalc_space); // sizeof fftcalc_space is sample double.
		BSP_FFT_Func(APP_SAMPLE_CHANNEL_0_RATE,APP_SAMPLE_CHANNEL_0_RATE , emu_inter_data , testOutput);
		APP_CalcValue[channel_index].BaseFreq =  BSP_FFT_GetBaseFreq(APP_SAMPLE_CHANNEL_0_RATE,APP_SAMPLE_CHANNEL_0_RATE , testOutput);
		DEBUG("Base Freq:%d\r\n" , APP_CalcValue[channel_index].BaseFreq );
		
		BSP_FFT_Integral_IFFT(APP_SAMPLE_CHANNEL_0_RATE,APP_SAMPLE_CHANNEL_0_RATE ,1,1000 ,10,testOutput , testOutput_2); // Velocity domain
		arm_rms_f32(testOutput_2, APP_SAMPLE_CHANNEL_0_RATE , &APP_CalcValue[channel_index].Velocity_RMS);    // Velocity_RMS
		Clog_Float("Velocity_RMS:" , APP_CalcValue[channel_index].Velocity_RMS);
		
		BSP_FFT_Integral_IFFT(APP_SAMPLE_CHANNEL_0_RATE,APP_SAMPLE_CHANNEL_0_RATE ,2,1000 ,10,testOutput , testOutput_2); // Displace domain
		float displace_max  ;
		float displace_min ; 
		arm_max_f32	(testOutput_2,APP_SAMPLE_CHANNEL_0_RATE, &displace_max, &pIndex );	
		arm_min_f32	(testOutput_2,APP_SAMPLE_CHANNEL_0_RATE, &displace_min, &pIndex );	
		APP_CalcValue[channel_index].Displace_PP = displace_max - displace_min; 		// Displace_PP 
		Clog_Float("Displace_PP:" , APP_CalcValue[channel_index].Displace_PP);		

	}
	
	// ----------------------------------------------
	vPortFree(emu_inter_data);
	vPortFree(testOutput);
	vPortFree(testOutput_2);
	vPortFree(fftcalc_space);
}


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

