/**
 **************************************************************************************************
 * @file        app_sample.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"

#include "clog.h"
#include "app_sample.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_tim.h"
#include "bsp_adc.h"
/**
 * @addtogroup    app_sample_Modules 
 * @{  
 */

/**
 * @defgroup      app_sample_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sample_Macros_Defines 
 * @brief         
 * @{  
 */
#define APP_SAMPLE_CHANNEL_0_RATE 4096
#define APP_SAMPLE_CHANNEL_1_RATE 4096
#define APP_SAMPLE_CHANNEL_2_RATE 4096


#define APP_SAMPLE_X_RATE	APP_SAMPLE_CHANNEL_0_RATE
#define APP_SAMPLE_Y_RATE	APP_SAMPLE_CHANNEL_1_RATE
#define APP_SAMPLE_Z_RATE   APP_SAMPLE_CHANNEL_2_RATE

#define APP_SAMPLE_X_INDEX   	0
#define APP_SAMPLE_Y_INDEX		1
#define APP_SAMPLE_Z_INDEX		2
/**
 * @}
 */

/**
 * @defgroup      app_sample_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_sample_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	uint16_t * originalData;
	uint16_t rate ; 
	uint16_t cur_dataPtr ; 
}APP_Sample_Channel_buf_t;

typedef struct
{
	APP_Sample_Channel_buf_t Sample_Channel_buf[3] ;
	uint8_t cur_channel ; 
}APP_Sample_buf_t ; 
/**
 * @}
 */

/**
 * @defgroup      app_sample_Private_Variables 
 * @brief         
 * @{  
 */
static uint16_t app_sample_channel_0_buf[APP_SAMPLE_CHANNEL_0_RATE * 2] = {0};
static uint16_t app_sample_channel_1_buf[APP_SAMPLE_CHANNEL_1_RATE * 2] = {0};
static uint16_t app_sample_channel_2_buf[APP_SAMPLE_CHANNEL_2_RATE * 2] = {0};

APP_Sample_buf_t APP_Sample_buf;


const uint8_t app_sample_rank[] = {APP_SAMPLE_X_INDEX,APP_SAMPLE_Y_INDEX,APP_SAMPLE_Z_INDEX};

/**
 * @}
 */

/**
 * @defgroup      app_sample_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_samlpechannel_init(void);
/**
 * @}
 */

/**
 * @defgroup      app_sample_Functions 
 * @brief         
 * @{  
 */
void APP_Sample_Init(void)
{
	DEBUG("APP_Sample_Init\r\n");
	app_samlpechannel_init();
	
	BSP_Tim_Init(BSP_TIM1);
	BSP_ADC_Init();
	APP_StartSample();
}

void APP_StartSample(void)
{
	BSP_Tim_1_Start();
}

void APP_StopSample(void)
{
	BSP_Tim_1_Stop();
}



static void app_samlpechannel_init(void)
{
	
	APP_Sample_buf.cur_channel = 0;
	//BSP_ADC0_SetChannelConfig(5);
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_X_INDEX].originalData = app_sample_channel_0_buf;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_X_INDEX].rate = APP_SAMPLE_CHANNEL_0_RATE;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_X_INDEX].cur_dataPtr = 0;

	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Y_INDEX].originalData = app_sample_channel_1_buf;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Y_INDEX].rate = APP_SAMPLE_CHANNEL_1_RATE;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Y_INDEX].cur_dataPtr = 0;

	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Z_INDEX].originalData = app_sample_channel_2_buf;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Z_INDEX].rate = APP_SAMPLE_CHANNEL_2_RATE;
	APP_Sample_buf.Sample_Channel_buf[APP_SAMPLE_Z_INDEX].cur_dataPtr = 0;	
}


// ----Test Code--------
uint16_t waveform[3] = {0};
// ---------------------
void APP_GetOriginalData( uint16_t data)
{
	APP_Sample_buf.Sample_Channel_buf[app_sample_rank[APP_Sample_buf.cur_channel]].originalData[APP_Sample_buf.Sample_Channel_buf[app_sample_rank[APP_Sample_buf.cur_channel]].cur_dataPtr] = data ; 
	APP_Sample_buf.Sample_Channel_buf[app_sample_rank[APP_Sample_buf.cur_channel]].cur_dataPtr ++;
	
	APP_Sample_buf.Sample_Channel_buf[app_sample_rank[APP_Sample_buf.cur_channel]].cur_dataPtr %= (APP_Sample_buf.Sample_Channel_buf[app_sample_rank[APP_Sample_buf.cur_channel]].rate << 1);

	 // ---test code---
	waveform[app_sample_rank[APP_Sample_buf.cur_channel]] = data;
	 // ---------------
	
	APP_SetNextQriginalChannel_Process();
}

void APP_SetNextQriginalChannel_Process(void) // this ��ͨ�������� Ҫ��ADCͨ����Ӧ�� , Channel(axial) must corresponding ADC channel
{
	APP_Sample_buf.cur_channel ++ ; 
	APP_Sample_buf.cur_channel %= (sizeof(app_sample_rank) / sizeof(app_sample_rank[0]));

	switch(app_sample_rank[APP_Sample_buf.cur_channel])
	{
		case APP_SAMPLE_X_INDEX: BSP_ADC0_SetChannelConfig(5);break;
		case APP_SAMPLE_Y_INDEX: BSP_ADC0_SetChannelConfig(7);break;
		case APP_SAMPLE_Z_INDEX: BSP_ADC0_SetChannelConfig(6);break;
		default:break;
	}
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

