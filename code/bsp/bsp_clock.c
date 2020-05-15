/**
 **************************************************************************************************
 * @file        bsp_clock.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_clock.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_clock_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_clock_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_clock_Macros_Defines 
 * @brief         
 * @{  
 */

extern uint32_t SystemCoreClock;

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_clock_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Functions 
 * @brief         
 * @{  
 */




void BSP_ShowClock(void)
{
	DEBUG("kCLOCK_CoreSysClk:%d\r\n", CLOCK_GetFreq(kCLOCK_CoreSysClk));
	DEBUG("kCLOCK_PlatClk:%d\r\n", CLOCK_GetFreq(kCLOCK_PlatClk));
	DEBUG("kCLOCK_BusClk:%d\r\n", CLOCK_GetFreq(kCLOCK_BusClk));
	DEBUG("kCLOCK_FlashClk:%d\r\n", CLOCK_GetFreq(kCLOCK_FlashClk));
	DEBUG("kCLOCK_PllFllSelClk:%d\r\n", CLOCK_GetFreq(kCLOCK_PllFllSelClk));
	//DEBUG("kCLOCK_Er32kClk:%d\r\n", CLOCK_GetFreq(kCLOCK_Er32kClk));
	DEBUG("kCLOCK_McgFixedFreqClk:%d\r\n", CLOCK_GetFreq(kCLOCK_McgFixedFreqClk));
	DEBUG("kCLOCK_McgInternalRefClk:%d\r\n", CLOCK_GetFreq(kCLOCK_McgInternalRefClk));
	DEBUG("kCLOCK_McgFllClk:%d\r\n", CLOCK_GetFreq(kCLOCK_McgFllClk));
	DEBUG("kCLOCK_McgPll0Clk:%d\r\n", CLOCK_GetFreq(kCLOCK_McgPll0Clk));
	DEBUG("kCLOCK_LpoClk:%d\r\n", CLOCK_GetFreq(kCLOCK_LpoClk));
	DEBUG("kCLOCK_Osc0ErClk:%d\r\n", CLOCK_GetFreq(kCLOCK_Osc0ErClk));	
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

