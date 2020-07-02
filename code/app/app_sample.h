/**
 **************************************************************************************************
 * @file        app_sample.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _APP_SAMPLE_H_
#define _APP_SAMPLE_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    app_sample_Modules 
 * @{  
 */

/**
 * @defgroup      app_sample_Exported_Macros 
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
 * @defgroup      app_sample_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Types 
 * @{  
 */
typedef struct
{
	uint16_t * originalData;
	uint16_t rate ; 
	uint16_t cur_dataPtr ; 
	uint8_t data_complete ;   // flag 0 is no complete , 1 is complete;
	
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
 * @defgroup      app_sample_Exported_Variables 
 * @{  
 */
extern APP_Sample_buf_t APP_Sample_buf;
/**
 * @}
 */

/**
 * @defgroup      app_sample_Exported_Functions 
 * @{  
 */
void APP_Sample_Init(void);
void APP_Sample_DeInit(void);
void APP_StartSample(void);
void APP_StopSample(void);

void APP_GetOriginalData( uint16_t data);
void APP_SetNextQriginalChannel_Process(void);
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
