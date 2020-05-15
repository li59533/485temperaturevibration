/**
 **************************************************************************************************
 * @file        bsp_power.c
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
#include "bsp_power.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_e32.h"
#include "bsp_clock.h"
#include "bsp_uart.h"
#include "bsp_systick.h"
#include "bsp_adc.h"
#include "app_getdata.h"
#include "bsp_lmt01.h"
/**
 * @addtogroup    bsp_power_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_power_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_power_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_power_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_power_Functions 
 * @brief         
 * @{  
 */

typedef enum
{
	Power_Mode_Normal = 0,
	Power_Mode_STOP	  ,
}BSP_Power_Mode_e;


void BSP_Power_SetMode(BSP_Power_Mode_e mode)
{
	DEBUG("Current Mode:%X\r\n" , SMC_GetPowerModeState( SMC ));
	
	//SMC_SetPowerModeProtection( SMC , kSMC_AllowPowerModeVlls | kSMC_AllowPowerModeLls); 
}


void BSP_Power_EnterVLPS(void)
{
	DEBUG("ENTER VLPS\r\n");
	BSP_LMT01_Power_OFF();
	BSP_E32_Close();
	BSP_SysTick_DisableIRQ();
	
	BOARD_RUNClockToVLPS();
	
	BSP_SysTick_Init();
	BSP_LMT01_Power_ON();
	BSP_E32_Open();
	BSP_SysTick_Init();
	
}




// -------Test Func--------
void BSP_Power_ModeTest(void)
{
	BSP_E32_Power_OFF();
	BSP_Uart0_Close();
//	DEBUG("Current Mode:%X\r\n" , SMC_GetPowerModeState( SMC ));
	SMC_SetPowerModeProtection(SMC , kSMC_AllowPowerModeAll);
	SMC_SetPowerModeVlps(SMC);

}

// ------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

