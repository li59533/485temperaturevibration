/**
 **************************************************************************************************
 * @file        bsp_uart.c
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
#include "bsp_uart.h"
#include "clog.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "ModbusRTU_Slave.h"
/**
 * @addtogroup    bsp_uart_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_uart_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_uart_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_uart_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_uart0_init(void);
static void bsp_uart1_init(void);
static void bsp_uart2_init(void);

static void bsp_uart0_dma_init(void);
static void bsp_uart2_dma_init(void);

/**
 * @}
 */

/**
 * @defgroup      bsp_uart_Functions 
 * @brief         
 * @{  
 */
/*
PE3 -> TX1  ALT3
PE4 -> RX1  ALT3


*/


void BSP_UART_Init(uint8_t BSP_UARTX)
{
	switch(BSP_UARTX)
	{
		case BSP_UART0: bsp_uart0_init();break;
		case BSP_UART1: bsp_uart1_init();break;
		case BSP_UART2: bsp_uart2_init();break;
		default:break;
	}
}

void BSP_UART_SetBaudRate(uint8_t BSP_UARTX , uint32_t buadrate)
{
	switch(BSP_UARTX)
	{
		case BSP_UART0: 
		{

		}
		break;
		case BSP_UART1:  UART_SetBaudRate(UART1, buadrate,  CLOCK_GetFreq(kCLOCK_CoreSysClk));;break;
		case BSP_UART2: bsp_uart2_init();break;
		default:break;
	}
}
	 

void BSP_Uart0_Close(void)
{

}

void BSP_Uart0_Open(void)
{
	BSP_UART_Init( BSP_UART0 );
	BSP_UART_SetBaudRate(BSP_UART0 , 115200);
}


static void bsp_uart0_init(void)
{
	// -------gpio init ------

	// -----------------------		
	
	// -------uart 0 init ----

	// -----------------------
	
	// --------open irq-------

	
	// -----------------------
	
// -----------DMA ------------------------

// ---------------------------------------	
	
}


/* UART user callback */
void UART_UserCallback(UART_Type *base, uart_edma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_UART_TxIdle == status)
    {
		DEBUG("kStatus_UART_TxIdle\r\n");
//        txBufferFull = false;
//        txOnGoing = false;
    }

    if (kStatus_UART_RxIdle == status)
    {
		DEBUG("kStatus_UART_RxIdle\r\n");
//        rxBufferEmpty = false;
//        rxOnGoing = false;
    }
}


#define SOPT5_UART1TXSRC_UART_TX 0x00u /*!<@brief UART 1 transmit data source select: UART1_TX pin */
edma_handle_t g_uartTxEdmaHandle;
edma_handle_t g_uartRxEdmaHandle;
uart_edma_handle_t g_uartEdmaHandle;
uart_handle_t g_uart1_handle;
static void bsp_uart1_init(void)
{
	uart_config_t uartConfig;
	edma_config_t config;
	// -------gpio init ------
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTE0 (pin E4) is configured as UART1_TX */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

    /* PORTE1 (pin E3) is configured as UART1_RX */
    PORT_SetPinMux(PORTE, 1U, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
	// -----------------------		
	
	// -------uart 0 init ----
    /* Initialize the UART. */
    /*
     * uartConfig.baudRate_Bps = 115200U;
     * uartConfig.parityMode = kUART_ParityDisabled;
     * uartConfig.stopBitCount = kUART_OneStopBit;
     * uartConfig.txFifoWatermark = 0;
     * uartConfig.rxFifoWatermark = 1;
     * uartConfig.enableTx = false;
     * uartConfig.enableRx = false;
     */
    UART_GetDefaultConfig(&uartConfig);
    uartConfig.baudRate_Bps = 115200;
    uartConfig.enableTx = true;
    uartConfig.enableRx = true;

    UART_Init(UART1, &uartConfig, CLOCK_GetFreq(kCLOCK_CoreSysClk));	
	
	
	// -----------------------
	
	// --------open irq-------
	UART_EnableInterrupts( UART1 ,kUART_TransmissionCompleteInterruptEnable);
	UART_EnableInterrupts( UART1 ,kUART_RxDataRegFullInterruptEnable);
	NVIC_SetPriority(UART1_RX_TX_IRQn , 6);
	EnableIRQ(UART1_RX_TX_IRQn);
	// -----------------------
	
// -----------DMA ------------------------
  /* Init DMAMUX */
    DMAMUX_Init(DMAMUX0);
    /* Set channel for UART */
    DMAMUX_SetSource(DMAMUX0, 0, kDmaRequestMux0UART1Tx);
    
    DMAMUX_EnableChannel(DMAMUX0, 0);


    /* Init the EDMA module */
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(DMA0, &config);
    EDMA_CreateHandle(&g_uartTxEdmaHandle, DMA0, 0);

    /* Create UART DMA handle. */
    UART_TransferCreateHandleEDMA(UART1, &g_uartEdmaHandle, UART_UserCallback, NULL, &g_uartTxEdmaHandle,
                                  &g_uartRxEdmaHandle);
// ---------------------------------------	
	
}

static void bsp_uart2_init(void)
{

}


static void bsp_uart0_dma_init(void)
{
						
}


static void bsp_uart2_dma_init(void)
{

						
}


// --------Function -------------

		// ----Send ----
			/*
				Uart0 blocking mode has some bug...
			*/
void BSP_UART_WriteBytes_Blocking(uint8_t BSP_UARTX , uint8_t *buf, uint16_t len)
{
	switch(BSP_UARTX)
	{
		case BSP_UART0 :;break;
		case BSP_UART1 :UART_WriteBlocking(UART1, buf, len);break;
		case BSP_UART2 :UART_WriteBlocking(UART2, buf, len);break;
		default:break;
	}
}

void BSP_UART_WriteBytes_DMA(uint8_t BSP_UARTX , uint8_t *buf, uint16_t len)
{
	uart_transfer_t  xfer;
	xfer.data = buf;
	xfer.dataSize = len;	
	switch(BSP_UARTX)
	{
		case BSP_UART0:; break;
		case BSP_UART1: 
						UART_EnableInterrupts( UART1 ,kUART_TransmissionCompleteInterruptEnable);
						UART_SendEDMA(UART1, &g_uartEdmaHandle, &xfer);
						break;
		case BSP_UART2:; break;
		default:break;
	}
}

		// -------------
		// ---Rev-------

		// -------------


// ------------------------------

// -----------IRQ--------------

void UART2_IRQHandler(void)
{
	DEBUG("UART2_IRQHandler\r\n");
	
	if((UART_GetStatusFlags(UART2) & kUART_RxDataRegFullFlag )== kUART_RxDataRegFullFlag)
	{
		UART_ClearStatusFlags(UART2, kUART_RxDataRegFullFlag);
		
		uint8_t c = 0;
		c = UART_ReadByte(UART2);
		DEBUG("Uart R:%X\r\n" , c);
	}
	
	if((UART_GetStatusFlags(UART2) & kUART_RxActiveEdgeInterruptEnable )== kUART_RxActiveEdgeInterruptEnable)
	{
		UART2->S2 |= UART_S2_RXEDGIF(1);  
	}	
	
}

void UART0_IRQHandler(void)
{

}

void UART1_ERR_IRQHandler(void)
{
	DEBUG("UART1_ERR_IRQHandler\r\n");
}

void UART1_RX_TX_IRQHandler(void)
{
	if(UART_GetStatusFlags(UART1) &kUART_TransmissionCompleteFlag )
	{

		//DEBUG("kUART_TransmissionCompleteFlag\r\n");
		UART_EnableTx(UART1, false);
		UART1->C2 |= 0x01;
		UART1->C2  &= (~0x01);
		UART_EnableTx(UART1, true);
		UART_DisableInterrupts( UART1 ,kUART_TransmissionCompleteInterruptEnable);
	}
	if(UART_GetStatusFlags(UART1) &kUART_RxDataRegFullFlag )
	{
//		DEBUG("kUART_RxDataRegFullFlag\r\n");
//		DEBUG("Uart R:%X\r\n" , c);	
//		uint8_t c = 0;
//		c = UART_ReadByte(UART1);
		ModbusRevOneByte(UART_ReadByte(UART1));
	}
}

void DMA0_IRQHandler(void)
{

	EDMA_HandleIRQ(&g_uartTxEdmaHandle);
}

// ----------------------------

// ------------Test-------------
uint8_t test_bud[] = {0x00,0x12,0x32,0xff,0x00,0x11,0xcd,0x45};
void BSP_Uart_Test_Send(void)
{
	DEBUG("BSP_Uart_Test_Send\r\n");
	BSP_UART_WriteBytes_DMA(BSP_485COM , test_bud, sizeof(test_bud));
}

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

