/**
 **************************************************************************************************
 * @file        bsp_fft_integral.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_fft_integral.h"
#include "arm_const_structs.h"
#include "math.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"

/**
 * @addtogroup    bsp_fft_integral_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_fft_integral_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_fft_integral_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_fft_integral_Private_Variables 
 * @brief         
 * @{  
 */
struct dou_integ integ;
/**
 * @}
 */
 
/**
 * @defgroup      bsp_fft_integral_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_fft_integral_Functions 
 * @brief         
 * @{  
 */
int BSP_FFT_IntegInit(uint16_t len,uint32_t sample_freq,float gravity,uint32_t freq_min,uint32_t freq_max)
{

	// 设置频域二次积分的参数(可更改)
	integ.smple_frq  = sample_freq;								//采样频率
	integ.gravity    = gravity;									//单位变化系数（最后积分结果乘上该系数，根据重力加速度得到）
	integ.frq_min    = freq_min;								//高通滤波截止频率
	integ.frq_max    = freq_max;								//低通滤波截止频率（应小于采样频率）
	integ.fft_len    = len;
	if(integ.frq_max >= integ.smple_frq)
	{
		return -2;		
	}
	switch(integ.fft_len)
	{
		case 16:{
			integ.S = arm_cfft_sR_f32_len16;
			break;
		}
		case 32:{
			integ.S = arm_cfft_sR_f32_len32;
			break;
		}
		case 64:{
			integ.S = arm_cfft_sR_f32_len64;
			break;
		}
		case 128:{
			integ.S = arm_cfft_sR_f32_len128;
			break;
		}
		case 256:{
			integ.S = arm_cfft_sR_f32_len256;
			break;
		}
		case 512:{
			integ.S = arm_cfft_sR_f32_len512;
			break;
		}
		case 1024:{
			integ.S = arm_cfft_sR_f32_len1024;
			break;
		}
		case 2048:{
			integ.S = arm_cfft_sR_f32_len2048;
			break;
		}
		case 4096:{
			integ.S = arm_cfft_sR_f32_len4096;
			break;
		}
		default:{
			integ.S = arm_cfft_sR_f32_len1024;
		}
	}

	return 0;
}




int8_t BSP_FFT_Mag_Calc(float * inputbuf, float * outputbuf, uint16_t bufsize)
{
	arm_cmplx_mag_f32(inputbuf,integ.mag_buf,bufsize);
	outputbuf = integ.mag_buf;
	return 0 ;
}


int8_t BSP_FFT_Calc(float *inputbuf,fft_instance_t * fft_instance)
{
	uint16_t i =0 ;
	float peak_max = 0.0f;
	//float peak_calc_temp = 0.0f;
	//-------------- make fft array and get acc_peak------------
	
	fft_instance->tim_domain_peak = 0;
	for(i=0; i<integ.fft_len; i++)	//  make fft array
	{			
		/*
		// -------DEBUG-----------------
		char debug_buf[30] ;
		snprintf(debug_buf,30,"%f",inputbuf[i]);
		DEBUG("%d %s\r\n",i,debug_buf);
		BSP_Systick_Delayms(3);
		// -----------------------------
		*/
		
		integ.fft_buf[2*i]   = inputbuf[i];		//real part
		//integ.fft_buf[2*i] = arm_sin_f32(2*3.1415926f*160*i/4096) *    (0.5f - 0.5f * arm_cos_f32(2.0f * 3.14159265f * i / 4096.0f));;
		integ.fft_buf[2*i+1] = 0;				//imaginary part
		
		if(fft_instance->tim_domain_peak <  inputbuf[i])   // get the acc peak
		{
			fft_instance->tim_domain_peak = inputbuf[i];
		}
	}
	// ----------------------------------------------------------
	// -------------- fft calc-----------------------------------
	arm_cfft_f32(&integ.S, integ.fft_buf, 0, 1);
	fft_instance->fft_pbuf = integ.fft_buf;
	// ----------------------------------------------------------
	// -------------- mag calc-----------------------------------
	arm_cmplx_mag_f32(integ.fft_buf ,integ.mag_buf , integ.fft_len);
	fft_instance->mag_pbuf = integ.mag_buf;
	// ----------------------------------------------------------
	// ------------- recover ---------
	for(i = 1 ;i < (uint16_t)(integ.fft_len) ; i ++)
	{
		integ.mag_buf[i] = integ.mag_buf[i] /(DATA_LEN/2);
	}	
	// -------------------------------
	// -------------- Get Base Freq -------------------------
	
	for(i = 1 ;i < (uint16_t)(integ.fft_len/2) ; i ++)
	{
		if(peak_max < integ.mag_buf[i])
		{
			peak_max = integ.mag_buf[i];
			fft_instance->base_freq= i;
		}
	}	
	
	// ----------------------------------------------------------
	
	return 0;
}



int BSP_FrqDomain_Integral(uint8_t integral_time,float  * fft_buf, float* outputbuf)
{		
	float fft_buf_temp[DATA_LEN * 2] = {0.0f}; 
	memcpy(fft_buf_temp,fft_buf,sizeof(fft_buf_temp));
	float df = (float)integ.smple_frq / (float)integ.fft_len;			//计算频率间隔（Hz/s）
	integ.high_pass = round(integ.frq_min/df);						//高通频率截止点
	integ.low_pass  = round(integ.frq_max/df);  						//低通频率截止点
	integ.integ_time = integral_time;
	float dw = 2*PI*df;													//圆频率间隔（rad/s）
	
	for(int i=0; i<(integ.fft_len/2); i++){
		integ.w_vec[i] = dw*i;											//正离散圆频率向量
		integ.w_vec[i] = pow(integ.w_vec[i],integ.integ_time);		//以积分次数为指数，建立圆频率变量向量
	}
//	
//	for(int i=integ.fft_len/2; i<(integ.fft_len-1); i++){
//		integ.w_vec[i] = -dw*(integ.fft_len/2-1) + dw*(i - integ.fft_len/2);	//负离散圆频率向量
//		integ.w_vec[i] = pow(integ.w_vec[i],integ.integ_time);		//以积分次数为指数，建立圆频率变量向量
//	}

	for(int i=integ.fft_len/2 + 1 ; i<(integ.fft_len); i++)
	{
		integ.w_vec[i] = dw*(i - integ.fft_len);
		//integ.w_vec[i] = -dw*(integ.fft_len/2-1) + dw*(i - integ.fft_len/2);	//负离散圆频率向量
		integ.w_vec[i] = pow(integ.w_vec[i],integ.integ_time);		//以积分次数为指数，建立圆频率变量向量
	}	
	
	
	for(int i=1; i<integ.fft_len-1; i++){
		fft_buf_temp[2*i  ] /= integ.w_vec[i];
		fft_buf_temp[2*i+1] /= integ.w_vec[i];
	}
	
	if(integral_time== 2){
		
		integ.high_pass = round(integ.frq_min/df) *2;						//高通频率截止点
		integ.low_pass  = round(integ.frq_max/df);  						//低通频率截止点
		for(int i=0; i<integ.fft_len; i++){								//进行积分频域变换和相位变换，放在一起做了
			fft_buf_temp[2*i  ] = -fft_buf_temp[2*i  ];					//频域变换即fft数组中的实部和虚部都除以w_vec的圆频率变换向量
			fft_buf_temp[2*i+1] = -fft_buf_temp[2*i+1];					//2次积分相位变换为旋转180度，即实部虚部都加一个负号
		}
		integ.gravity = 1000000;
	}
	else{
		float temp;
		integ.high_pass = round(integ.frq_min/df);						//高通频率截止点
		integ.low_pass  = round(integ.frq_max/df);  						//低通频率截止点
		
		for(int i=0; i<integ.fft_len; i++){		
			temp = -fft_buf_temp[2*i];									//1次积分相位变换为逆时针旋转90度
			fft_buf_temp[2*i  ] = fft_buf_temp[2*i+1];					//实部等于虚部，虚部等于负实部
			fft_buf_temp[2*i+1] = temp;
		}
		integ.gravity = 1000;
	}
	
	for(int i=0; i<integ.fft_len-integ.low_pass; i++){					//清除频域中的低频部分
		fft_buf_temp[2*i  ] = 0;
		fft_buf_temp[2*i+1] = 0;
	}
	for(int i=integ.fft_len-integ.high_pass; i<integ.fft_len; i++){		//清除频域中的高频部分
		fft_buf_temp[2*i  ] = 0;
		fft_buf_temp[2*i+1] = 0;
	}
	/*
	char debug_buf[30] = {0};
	for(int i = integ.fft_len-integ.low_pass; i<integ.fft_len * 2;i ++ )
	{
		snprintf(debug_buf,30,"%f",fft_buf_temp[i]);
		DEBUG("%d :%s \r\n",i,debug_buf);
		BSP_Systick_Delayms(1);
	}
	*/
	
	arm_cfft_f32(&integ.S, fft_buf_temp, 1, 1);							//计算IFFT,结果保存在fft_buf中
	
	for(int i=0; i<integ.fft_len; i++){
		outputbuf[i] =fft_buf_temp[2*i]*integ.gravity*2;					//乘以一个2，才是正常数据，取逆变换的实部并乘以单位变换系数为积分结果
	}
	
	return 0;
}


float BSP_GetHarmonicPeak(uint16_t base_freq , float harmonic,float * mag_buf)
{
	uint16_t index = 0;
	index = (uint16_t ) (base_freq * harmonic);
	
	return mag_buf[index] * 2.0f;
}

float BSP_GetSpeedRMS(float * mag_buf,uint16_t len)
{
	float sum_temp = 0.0f; 
	for(uint16_t i = 1 ; i <=  2048 ; i ++)
	{
		sum_temp +=(mag_buf[i]  * 1.633f / ( 2.0f * 3.14159265f * i) )* (mag_buf[i] * 1.633f / ( 2.0f * 3.14159265f * i));
	}
	sum_temp /= 2.0f;
	arm_sqrt_f32(sum_temp,&sum_temp);
	return sum_temp;
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

