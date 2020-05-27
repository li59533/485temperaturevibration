/**
 **************************************************************************************************
 * @file        app_lnprotocol.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "self_def.h"
#include "app_lnprotocol.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "lnprotocol.h"
#include "system_param.h"
#include "bsp_uart.h"
#include "app_hal.h"
/**
 * @addtogroup    app_lnprotocol_Modules 
 * @{  
 */

/**
 * @defgroup      app_lnprotocol_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_lnprotocol_process_1(uint8_t * buf , uint16_t len);
static void app_lnprotocol_getslaveID(uint8_t * buf , uint16_t len );
static void app_lnprotocol_paramRest(uint8_t * buf , uint16_t len);
/**
 * @}
 */

/**
 * @defgroup      app_lnprotocol_Functions 
 * @brief         
 * @{  
 */
void APP_Lnprotocol_Process(uint8_t * buf , uint16_t len)
{
	if(buf[0] == LNPROTOCOL_HEAD)   // check head 
	{

		if((buf[2] + buf[3] * 256) == (len - 6) ) // check inf len 
		{
			if(LNprotocol_Checksum( &buf[0] , len) == 1) // check sum
			{
				app_lnprotocol_process_1( buf  , len);   // deal with the cmd
			}					
		}
		else
		{
			
		}
	}
}

static void app_lnprotocol_process_1(uint8_t * buf , uint16_t len)
{
	ln_protocolintance_t * ln_protocolintance = 0;
	
	ln_protocolintance = (ln_protocolintance_t *) buf;
	
	switch(ln_protocolintance->cmd)
	{
		case CMD_GetSlaveID_Req:app_lnprotocol_getslaveID( (uint8_t *)&ln_protocolintance->payload, ln_protocolintance->len); break;
		case CMD_Param_Rest:app_lnprotocol_paramRest( (uint8_t *)&ln_protocolintance->payload, ln_protocolintance->len);break; 
		default:break;
	}		
}

static void app_lnprotocol_paramRest(uint8_t * buf , uint16_t len)
{
	SystemParam_Reset();
	APP_Hal_Rest();
}

static void app_lnprotocol_getslaveID(uint8_t * buf , uint16_t len )
{
	ln_protocolintance_t * ln_protocolintance = 0;
	uint8_t sendbuf[100] = { 0 };
	uint8_t buf_temp[10] = { 0 };
	uint16_t send_len = 0; 

	ln_protocolintance = (ln_protocolintance_t *) sendbuf;
	ln_protocolintance->head = LNPROTOCOL_HEAD;
	ln_protocolintance->cmd = CMD_GetSlaveID_Resp;
	
	uint8_t * buf_ptr = (uint8_t *)&ln_protocolintance->payload;

	// -------- DestAddr ---
	buf_temp[0] = g_SystemParam_Config.MB_Slave_ID;
	buf_ptr = LNprotocol_AddPayload(buf_ptr, (uint8_t *)buf_temp , 1);
	send_len += 1;

	// ---------------------
	// ---------------------------------------
	ln_protocolintance->len = send_len;
	*buf_ptr = LNprotocol_GetChecksum(&ln_protocolintance->head , send_len + 6);
	buf_ptr ++;
	*(buf_ptr ) = LNPROTOCOL_FOOT;
	buf_ptr ++;

	// --------Send---------

	BSP_UART_WriteBytes_DMA(BSP_485COM ,&ln_protocolintance->head , buf_ptr - &ln_protocolintance->head);
	// ----------------------	
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

