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
#include "ModbusRTU_Slave.h"
#include "modbus_task.h"
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
static void bsp_lptmr_init(void);
static void bsp_lptmr_deinit(void);
static void bsp_tmp0_deinit(void);
static void bsp_tmp0_init(void);
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
		default :break;
	}
}

void BSP_Tim_DeInit(uint8_t BSP_TIMx)
{
	switch (BSP_TIMx)
	{
		case BSP_TIM0 :bsp_lptmr_deinit();break;
		case BSP_TIM1 : bsp_tmp0_deinit();break;
		default :break;
	}
}

static void bsp_tmp0_deinit(void)
{

}

static void bsp_lptmr_deinit(void)
{
	
}

static void bsp_tmp0_init(void)
{
	
	//CLOCK_EnableClock(kCLOCK_Ftm0);
	ftm_config_t ftmInfo;
    FTM_GetDefaultConfig(&ftmInfo);

    /* Divide FTM clock by 4 */
    ftmInfo.prescale = kFTM_Prescale_Divide_4;

    /* Initialize FTM module */
    FTM_Init(FTM0, &ftmInfo);

    /*
     * Set timer period.
    */
    FTM_SetTimerPeriod(FTM0, USEC_TO_COUNT(5000, CLOCK_GetFreq(kCLOCK_BusClk) * 4));

    FTM_EnableInterrupts(FTM0, kFTM_TimeOverflowInterruptEnable);

	NVIC_SetPriority(FTM0_IRQn , 7);
    EnableIRQ(FTM0_IRQn);
	
    
}


void BSP_Tim_0_StartOnce(void)
{
	FTM_StopTimer(FTM0);
	FTM_SetTimerPeriod(FTM0, USEC_TO_COUNT(5000, CLOCK_GetFreq(kCLOCK_BusClk) * 4));
	FTM_StartTimer(FTM0, kFTM_SystemClock);
}

static void bsp_lptmr_init(void)
{

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
		Modbus_Task_Event_Start(MODBUS_TASK_DATAPROCESS_EVENT, EVENT_FROM_ISR);
		/* Clear interrupt flag.*/
		FTM_ClearStatusFlags(FTM0, kFTM_TimeOverflowFlag);
		FTM_StopTimer(FTM0);	
			
	}
	DEBUG("FTM0_IRQHandler\r\n");
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

