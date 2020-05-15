/**
 **************************************************************************************************
 * @file        bsp_uart.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    bsp_uart_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_uart_Exported_Macros 
 * @{  
 */
#define BSP_UART0   0
#define BSP_UART1   1
#define BSP_UART2   2


// ------User def-----
#define BSP_485COM	BSP_UART1
// -------------------

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Exported_Functions 
 * @{  
 */
 
void BSP_UART_Init(uint8_t BSP_UARTX);
void BSP_UART_SetBaudRate(uint8_t BSP_UARTX , uint32_t buadrate);
void BSP_UART_WriteBytes_Blocking(uint8_t BSP_UARTX , uint8_t *buf, uint16_t len);
void BSP_UART_WriteBytes_DMA(uint8_t BSP_UARTX , uint8_t *buf, uint16_t len);


void BSP_Uart0_Close(void);
void BSP_Uart0_Open(void);
// -----------IRQ--------------
void UART2_IRQHandler(void);
// ----------------------------
 
// ------------Test-------------
void BSP_Uart_Test_Send(void);

// -----------------------------

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
