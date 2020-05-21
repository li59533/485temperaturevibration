/**
 **************************************************************************************************
 * @file        bsp_fft_integral.h
 * @author		L-KAYA	
 * @version   	v0.1.0
 * @date        
 * @brief		该文件主要用于实现加速度在频域的一次或二次积分得到速度或位移，
 * 				有带通滤波功能，积分后漂移较小建议采样频率1kHz以上，效果较为理想
 **************************************************************************************************
 * @attention	遇到malloc失败进入hardfault时，尝试把starup_stm32f40_41xxx.s
 * 				中的Stack_Size和Heap_Size调大，默认的堆栈比较小，数组太长时会
 * 				分配失败
 * 				该文件需要用到STM32F4的DSP库
 *
 *	@other		该文件是参考王济《matlab在振动信号处理中的应用》的.m程序，适用
 * 				于振动环境（总位移为0）的位移计算，不适用于单次位移的测量
 *
 *  @example	integ_init(1024);
 *				float data_buf[1000];		//需要进行积分的数据数组
 *				float integ_buf[1024];		//用于储存积分结果的数组
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
#define DATA_LEN				4096				//数据长度，初始化时作为参数传入，2的幂次最佳

#define SMPLE_FRQ				4096				//采样频率
#define GRAVITY					1   //9810.5				//单位变化系数（最后积分结果乘上该系数，根据重力加速度得到）
#define FRQ_MIN					5					//高通滤波截止频率
#define FRQ_MAX					200					//低通滤波截止频率（应小于采样频率）
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
	uint8_t 	integ_time;							//积分次数，1为速度，2为距离
	uint16_t 	fft_len;							//FFT数组长度，为2的整数幂次
	float	 	smple_frq;							//采样频率，单位Hz
	float		high_pass;							//高通频率起始点
	float		low_pass;							//低通频率截止点
	float 		frq_min;							//最小截止频率
	float 		frq_max;							//最大截止频率
	float	 	gravity;							//单位变换系数
	float		w_vec[DATA_LEN * 2];				//频率向量
	float 		fft_buf[DATA_LEN * 2];				//用于存储fft计算过程中的临时数组
	float 		mag_buf[DATA_LEN];
	arm_cfft_instance_f32 S;						//用于fft计算的结构体
	
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
