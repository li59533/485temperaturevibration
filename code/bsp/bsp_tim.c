/**
 **************************************************************************************************
 * @file        bsp_tim.c
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
#include "bsp_tim.h"

#include "bsp_clock.h"

#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "modbus_task.h" 
#include "modbus_rtu.h"

#include "sample_task.h"
#include "first_task.h"
#include "system_param.h"

/**
 * @addtogroup    bsp_tim_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_tim_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_tim_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_tim_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_tmp0_init(void);
static void bsp_tmp1_init(void);
static void bsp_tmp0_deinit(void);
static void bsp_tmp1_deinit(void);
/**
 * @}
 */

/**
 * @defgroup      bsp_tim_Functions 
 * @brief         
 * @{  
 */

 
void BSP_Tim_Init(uint8_t BSP_TIMx)
{
	switch (BSP_TIMx)
	{
		case BSP_TIM0 :bsp_tmp0_init();break;
		case BSP_TIM1 :bsp_tmp1_init();break;
		default :break;
	}
}

void BSP_Tim_DeInit(uint8_t BSP_TIMx)
{
	switch (BSP_TIMx)
	{
		case BSP_TIM0 :bsp_tmp0_deinit();break;
		case BSP_TIM1 :bsp_tmp1_deinit();break;
		default :break;
	}
}


static void bsp_tmp0_init(void)
{
	//CLOCK_EnableClock(kCLOCK_Ftm0);
	ftm_config_t ftmInfo;
    FTM_GetDefaultConfig(&ftmInfo);

    /* Divide FTM clock by 4 */
    ftmInfo.prescale = kFTM_Prescale_Divide_32;

    /* Initialize FTM module */
    FTM_Init(FTM0, &ftmInfo);
    /*
     * Set timer period.
    */
	switch(g_SystemParam_Config.BaudRate_Bps)
	{
		case 0 : FTM_SetTimerPeriod(FTM0, 27187);break;
		case 1 : FTM_SetTimerPeriod(FTM0, 13670);break;
		case 2 : FTM_SetTimerPeriod(FTM0, 6750);break;
		case 3 : FTM_SetTimerPeriod(FTM0, 4556);break;
		case 4 : FTM_SetTimerPeriod(FTM0, 3416);break;
		case 5 : FTM_SetTimerPeriod(FTM0, 1708);break;
		case 6 : FTM_SetTimerPeriod(FTM0, 1171);break;
		case 7 : FTM_SetTimerPeriod(FTM0, 562);break;
		default : FTM_SetTimerPeriod(FTM0, 6750);break;		
	}
	// -----IRQ-------
    FTM_EnableInterrupts(FTM0, kFTM_TimeOverflowInterruptEnable);
	NVIC_SetPriority(FTM0_IRQn , 6);
    EnableIRQ(FTM0_IRQn);
	// ---------------
}

static void bsp_tmp1_init(void)
{
	
	CLOCK_EnableClock(kCLOCK_Ftm1);
	ftm_config_t ftmInfo;
    FTM_GetDefaultConfig(&ftmInfo);
    /* Divide FTM clock by 4 */
    ftmInfo.prescale = kFTM_Prescale_Divide_1;
	//ftmInfo.prescale = kFTM_Prescale_Divide_128;
	
	ftmInfo.extTriggers = kFTM_InitTrigger;
    /* Initialize FTM module */
    FTM_Init(FTM1, &ftmInfo);
    /*
     * Set timer period.
    */
    //FTM_SetTimerPeriod(FTM1, 3662); // div_1 3622 -> 16384Hz
	FTM_SetTimerPeriod(FTM1, 4883); // div_1 4883 -> 12288Hz
	//FTM_SetTimerPeriod(FTM1, 65535); // test value
	// -----trg----------
	
	// ------------------

	// -----IRQ-------
//    FTM_EnableInterrupts(FTM1, kFTM_TimeOverflowInterruptEnable);
//	NVIC_SetPriority(FTM1_IRQn , 7);
//    EnableIRQ(FTM1_IRQn);
	// ---------------

}


static void bsp_tmp0_deinit(void)
{
	FTM_StopTimer(FTM0);
	FTM_Deinit(FTM0);
}
static void bsp_tmp1_deinit(void)
{
	FTM_StopTimer(FTM1);
	FTM_Deinit(FTM1);
}


void BSP_Tim_0_StartOnce(void)
{
	FTM_StopTimer(FTM0);
	
	FTM_ClearQuadDecoderCounterValue(FTM0);
//	switch(g_SystemParam_Config.BaudRate_Bps)
//	{
//		case 0 : FTM_SetTimerPeriod(FTM0, 27187);break;
//		case 1 : FTM_SetTimerPeriod(FTM0, 13670);break;
//		case 2 : FTM_SetTimerPeriod(FTM0, 6750);break;
//		case 3 : FTM_SetTimerPeriod(FTM0, 4556);break;
//		case 4 : FTM_SetTimerPeriod(FTM0, 3416);break;
//		case 5 : FTM_SetTimerPeriod(FTM0, 1708);break;
//		case 6 : FTM_SetTimerPeriod(FTM0, 1171);break;
//		case 7 : FTM_SetTimerPeriod(FTM0, 562);break;
//		default : FTM_SetTimerPeriod(FTM0, 6750);break;		
//	}
	FTM_StartTimer(FTM0, kFTM_SystemClock);
}

void BSP_Tim_1_Start(void)
{
	FTM_StartTimer(FTM1, kFTM_SystemClock);
}

void BSP_Tim_1_Stop(void)
{
	FTM_StopTimer(FTM1);
}

void BSP_Tim_StartOnceTimer(uint8_t BSP_TIMx , uint32_t msec)
{

}

uint32_t BSP_GetTimrCurCount(uint8_t BSP_TIMx)
{
	uint32_t count = 0;
	switch(BSP_TIMx)
	{
		case BSP_TIM0 : ;break;
		case BSP_TIM1 : ;break;
		default :break;
	}
	return count ;
}

 // ----------IRQHandler ------------------

void FTM0_IRQHandler(void)
{
	if(FTM_GetStatusFlags(FTM0) & kFTM_TimeOverflowFlag )
	{
		rBufToRing();
		/* Clear interrupt flag.*/
		FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
		FTM_StopTimer(FTM0);	
		
		
		Modbus_Task_Event_Start(MODBUS_TASK_DATAPROCESS_EVENT, EVENT_FROM_ISR);
		
		
		DEBUG("FTM0_IRQHandler\r\n");	
	}
	
}

void FTM1_IRQHandler(void)
{
	if(FTM_GetStatusFlags(FTM1) & kFTM_TimeOverflowFlag )
	{
		/* Clear interrupt flag.*/
		FTM_ClearStatusFlags(FTM1, kFTM_TimeOverflowFlag);
		DEBUG("FTM1_IRQHandler\r\n");
	}

}

 // ---------------------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

