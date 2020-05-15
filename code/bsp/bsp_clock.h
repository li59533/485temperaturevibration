/**
 **************************************************************************************************
 * @file        bsp_clock.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_CLOCK_H_
#define _BSP_CLOCK_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "bsp_conf.h"
/**
 * @addtogroup    bsp_clock_Modules 
 * @{  
 */
/*

00> kCLOCK_CoreSysClk:48000000
00> kCLOCK_PlatClk:48000000
00> kCLOCK_BusClk:24000000
00> kCLOCK_FlashClk:24000000
00> kCLOCK_PllFllSelClk:48000000
00> kCLOCK_Er32kClk:1000
00> kCLOCK_McgFixedFreqClk:250000
00> kCLOCK_McgInternalRefClk:32768
00> kCLOCK_McgFllClk:0
00> kCLOCK_McgPll0Clk:96000000
00> kCLOCK_LpoClk:1000
00> kCLOCK_Osc0ErClk:8000000

*/
/**
 * @defgroup      bsp_clock_Exported_Macros 
 * @{  
 */
 
/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Exported_Constants
 * @{  
 */
 
/*! @brief MCG set for BOARD_BootClockRUN configuration.
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_clock_Exported_Functions 
 * @{  
 */


/*
00> kCLOCK_CoreSysClk:120000000
00> kCLOCK_PlatClk:0
00> kCLOCK_BusClk:60000000
00> kCLOCK_FlashClk:24000000
00> kCLOCK_PllFllSelClk:120000000
00> kCLOCK_McgFixedFreqClk:250000
00> kCLOCK_McgInternalRefClk:32768
00> kCLOCK_McgFllClk:0
00> kCLOCK_McgPll0Clk:120000000
00> kCLOCK_LpoClk:1000
00> kCLOCK_Osc0ErClk:8000000
*/

void BSP_ShowClock(void);


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
