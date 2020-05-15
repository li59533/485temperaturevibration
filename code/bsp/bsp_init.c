/**
 **************************************************************************************************
 * @file        bsp_init.c
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
#include "bsp_init.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_flash.h"
#include "bsp_uart.h"
#include "bsp_tim.h"
#include "bsp_clock.h"
/**
 * @addtogroup    bsp_init_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_init_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_init_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_init_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_init_Functions 
 * @brief         
 * @{  
 */
void BSP_Init(void)
{
	BSP_ShowClock();
	BSP_Flash_Init();
	//BSP_UART_Init(BSP_UART1);
	//BSP_Tim_Init(BSP_TIM0);
	DEBUG("bsp init\r\n");
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

