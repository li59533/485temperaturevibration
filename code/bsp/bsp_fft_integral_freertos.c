/**
 **************************************************************************************************
 * @file        bsp_fft_integral_freertos.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_fft_integral_freertos.h"
#include "arm_const_structs.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "math.h" 
#include "clog.h"
/**
 * @addtogroup    bsp_fft_integral_freertos_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_fft_integral_freertos_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_freertos_Functions 
 * @brief         
 * @{  
 */

// ------fft tools ---------

typedef struct
{
	arm_cfft_instance_f32 S;
	float * fft_space_1;
}bsp_fft_param_t;
bsp_fft_param_t bsp_fft_param;

void BSP_FFT_Init(uint32_t sample_rate ,uint32_t pointcount ,  float * fftcalc_space) // sizeof fftcalc_space is sample double.
{
	bsp_fft_param.fft_space_1 = fftcalc_space;
	//bsp_fft_param.fft_space_1 = test_buf;
	switch(sample_rate)
	{
		case 1024:{
			bsp_fft_param.S = arm_cfft_sR_f32_len1024;
			break;
		}
		case 2048:{
			bsp_fft_param.S = arm_cfft_sR_f32_len2048;
			break;
		}
		case 4096:{
			bsp_fft_param.S = arm_cfft_sR_f32_len4096;
			break;
		}
		default:{
			bsp_fft_param.S = arm_cfft_sR_f32_len1024;
		}
	}
}

void BSP_FFT_Func(uint32_t sample_rate ,uint32_t pointcount, float * inbuf , float *outbuf)
{
	// -----------make fft array----------
	for(uint32_t i = 0 ; i < sample_rate ; i ++)   
	{
		bsp_fft_param.fft_space_1[2 * i] = inbuf[i];
		//bsp_fft_param.fft_space_1[2 * i]= 100 * arm_sin_f32(2*3.1415926f*160*i/sample_rate)  ;//*  (0.5f - 0.5f * arm_cos_f32(2.0f * 3.14159265f * i / 4096.0f));
		bsp_fft_param.fft_space_1[2 * i + 1] = 0;
	}

	// -------------- fft calc-------------
	arm_cfft_f32(&bsp_fft_param.S, bsp_fft_param.fft_space_1, 0, 1);
	
	memcpy(outbuf ,bsp_fft_param.fft_space_1 , sample_rate * 2 * 4 );	

}

void BSP_FFT_Integral_IFFT(uint32_t sample_rate,uint32_t pointcount ,uint8_t integral_count,uint32_t lowpass ,uint32_t highpass,float * inbuf , float *outbuf)
{

	
	float df = (float)(sample_rate / pointcount);
	float dw = 2*PI*df;	
	float integral_lowpass ; 
	float integral_highpass ; 
	float *w_vec = 0;
	uint32_t unit_conv = 1;
	
	w_vec = pvPortMalloc(sizeof(float) * sample_rate * 2);
	
	integral_lowpass =  round((float)lowpass/df);
	integral_highpass = round((float)highpass/df);
	
	for(uint32_t i=0; i<(pointcount/2); i++)
	{
		w_vec[i] = dw * i;											//����ɢԲƵ������
		w_vec[i] = pow(w_vec[i] , integral_count);		//�Ի��ִ���Ϊָ��������ԲƵ�ʱ�������
	}
	
	for(uint32_t i=pointcount/2 + 1 ; i<(pointcount); i++)
	{
		w_vec[i] = dw * (i - pointcount);//����ɢԲƵ������
		w_vec[i] = pow(w_vec[i] , integral_count);		//�Ի��ִ���Ϊָ��������ԲƵ�ʱ�������
	}	

	memcpy(bsp_fft_param.fft_space_1 ,inbuf , pointcount * 2 * 4);
	
	for(uint32_t i = 1; i < pointcount - 1; i++)
	{
		bsp_fft_param.fft_space_1[2*i  ] /= w_vec[i];
		bsp_fft_param.fft_space_1[2*i+1] /= w_vec[i];
	}
	
	
	vPortFree(w_vec);
//	
	
	
	if(integral_count == 2)
	{
		integral_lowpass =  round((float)lowpass/df) ;
		integral_highpass = round((float)highpass/df) * 2;
		
		
		for(int i=0; i < pointcount; i++)
		{								//���л���Ƶ��任����λ�任������һ������
			bsp_fft_param.fft_space_1[2*i  ] = - bsp_fft_param.fft_space_1[2*i  ];					//Ƶ��任��fft�����е�ʵ�����鲿������w_vec��ԲƵ�ʱ任����
			bsp_fft_param.fft_space_1[2*i+1] = - bsp_fft_param.fft_space_1[2*i+1];					//2�λ�����λ�任Ϊ��ת180�ȣ���ʵ���鲿����һ������
		}
		unit_conv = 1000000;
	}
	else{
		float temp;
		
		integral_lowpass =  round((float)lowpass/df) ;
		integral_highpass = round((float)highpass/df) ;		
				
		for(int i=0; i < pointcount; i++)
		{		
			temp = - bsp_fft_param.fft_space_1[ 2 * i];									//1�λ�����λ�任Ϊ��ʱ����ת90��
			bsp_fft_param.fft_space_1[ 2 * i ] = bsp_fft_param.fft_space_1[ 2 * i + 1 ];					//ʵ�������鲿���鲿���ڸ�ʵ��
			bsp_fft_param.fft_space_1[ 2 * i + 1] = temp;
		}
		unit_conv = 1000;
	}	
	

	for(int i = 0; i < integral_highpass; i++){					//���Ƶ���еĵ�Ƶ����
		bsp_fft_param.fft_space_1[ 2 * i  ] = 0;
		bsp_fft_param.fft_space_1[ 2 * i + 1] = 0;
	}
	for(int i = integral_lowpass; i < pointcount; i ++){		//���Ƶ���еĸ�Ƶ����
		bsp_fft_param.fft_space_1[ 2 * i  ] = 0;
		bsp_fft_param.fft_space_1[ 2 * i + 1] = 0;
	}		
		
	arm_cfft_f32(&bsp_fft_param.S , bsp_fft_param.fft_space_1, 1, 1);							//����IFFT,���������fft_buf��
	
	for(uint32_t  i=0; i < pointcount; i++)
	{
		outbuf[i] =bsp_fft_param.fft_space_1[2*i]*(float)unit_conv*2;					//����һ��2�������������ݣ�ȡ��任��ʵ�������Ե�λ�任ϵ��Ϊ���ֽ��
	}
	
}

uint32_t BSP_FFT_GetBaseFreq(uint32_t sample_rate ,uint32_t pointcount, float *inbuf)
{
	// -------------- mag calc-----------------------------------
	arm_cmplx_mag_f32(inbuf ,bsp_fft_param.fft_space_1 ,sample_rate);

	for(uint32_t i = 1 ;i < (sample_rate / 2); i ++)
	{
		bsp_fft_param.fft_space_1[i] = bsp_fft_param.fft_space_1[i] /(sample_rate/2);
	}	
	// -------------------------------
	// -------------- Get Base Freq -------------------------
	
	float baseFreq_mag;
	uint32_t pIndex ; 
	arm_max_f32(bsp_fft_param.fft_space_1, sample_rate / 2 , &baseFreq_mag , &pIndex);
	Clog_Float("baseFreq_mag:",baseFreq_mag);
	return pIndex;
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

