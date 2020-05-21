/**
 **************************************************************************************************
 * @file        bsp_fft_integral.h
 * @author		L-KAYA	
 * @version   	v0.1.0
 * @date        
 * @brief		���ļ���Ҫ����ʵ�ּ��ٶ���Ƶ���һ�λ���λ��ֵõ��ٶȻ�λ�ƣ�
 * 				�д�ͨ�˲����ܣ����ֺ�Ư�ƽ�С�������Ƶ��1kHz���ϣ�Ч����Ϊ����
 **************************************************************************************************
 * @attention	����mallocʧ�ܽ���hardfaultʱ�����԰�starup_stm32f40_41xxx.s
 * 				�е�Stack_Size��Heap_Size����Ĭ�ϵĶ�ջ�Ƚ�С������̫��ʱ��
 * 				����ʧ��
 * 				���ļ���Ҫ�õ�STM32F4��DSP��
 *
 *	@other		���ļ��ǲο����á�matlab�����źŴ����е�Ӧ�á���.m��������
 * 				���񶯻�������λ��Ϊ0����λ�Ƽ��㣬�������ڵ���λ�ƵĲ���
 *
 *  @example	integ_init(1024);
 *				float data_buf[1000];		//��Ҫ���л��ֵ���������
 *				float integ_buf[1024];		//���ڴ�����ֽ��������
 *				frq_domain_integral(data_buf, integ_buf);
 **************************************************************************************************
 */
#ifndef _BSP_FFT_INTEGRAL_H_
#define _BSP_FFT_INTEGRAL_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
#include "bsp_math.h"

/**
 * @addtogroup    bsp_fft_integral_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_fft_integral_Exported_Macros 
 * @{  
 */
 
// ----User conf param-----
#define DATA_LEN				4096				//���ݳ��ȣ���ʼ��ʱ��Ϊ�������룬2���ݴ����

#define SMPLE_FRQ				4096				//����Ƶ��
#define GRAVITY					1   //9810.5				//��λ�仯ϵ���������ֽ�����ϸ�ϵ���������������ٶȵõ���
#define FRQ_MIN					5					//��ͨ�˲���ֹƵ��
#define FRQ_MAX					200					//��ͨ�˲���ֹƵ�ʣ�ӦС�ڲ���Ƶ�ʣ�
// -------------------------
/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_fft_integral_Exported_Types 
 * @{  
 */
typedef struct dou_integ
{
	uint8_t 	integ_time;							//���ִ�����1Ϊ�ٶȣ�2Ϊ����
	uint16_t 	fft_len;							//FFT���鳤�ȣ�Ϊ2�������ݴ�
	float	 	smple_frq;							//����Ƶ�ʣ���λHz
	float		high_pass;							//��ͨƵ����ʼ��
	float		low_pass;							//��ͨƵ�ʽ�ֹ��
	float 		frq_min;							//��С��ֹƵ��
	float 		frq_max;							//����ֹƵ��
	float	 	gravity;							//��λ�任ϵ��
	float		w_vec[DATA_LEN * 2];				//Ƶ������
	float 		fft_buf[DATA_LEN * 2];				//���ڴ洢fft��������е���ʱ����
	float 		mag_buf[DATA_LEN];
	arm_cfft_instance_f32 S;						//����fft����Ľṹ��
	
}dou_integ_t;


typedef struct 
{
	float * fft_pbuf;
	float * mag_pbuf;
	float tim_domain_peak;
	uint16_t base_freq;
}fft_instance_t;


/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Exported_Functions 
 * @{  
 */
 
int8_t BSP_FFT_Calc(float *inputbuf,fft_instance_t * fft_instance);

int BSP_FFT_IntegInit(uint16_t len,uint32_t sample_freq,float gravity,uint32_t freq_min,uint32_t freq_max);

int BSP_FrqDomain_Integral(uint8_t integral_time,float  * fft_buf, float* outputbuf);


float BSP_GetHarmonicPeak(uint16_t base_freq , float harmonic,float * fft_buf);

int8_t BSP_FFT_Mag_Calc(float * inputbuf, float * outputbuf, uint16_t bufsize);

float BSP_GetSpeedRMS(float * mag_buf,uint16_t len);

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
