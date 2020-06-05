/**
 **************************************************************************************************
 * @file        modbus_port.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "modbus_port.h"
#include "modbus_rtu.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_conf.h" 
#include "bsp_tim.h"
#include "bsp_uart.h"

#include "clog.h"
/**
 * @addtogroup    modbus_port_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_port_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_port_Public_Variables 
 * @brief         
 * @{  
 */
uint8_t Uart2RBuf[20];
uint8_t Uart2RBuf_Ptr=0;
/**
 * @}
 */

/**
 * @defgroup      modbus_port_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void modbusGPIOInit(void);
static void modbusUartInit(void);
static void modbusTimInit(void);
/**
 * @}
 */

/**
 * @defgroup      modbus_port_Functions 
 * @brief         
 * @{  
 */
 
void ModbusFunctionInit(void)
{
    modbusGPIOInit();
    modbusUartInit();  
	modbusTimInit();
	
	ModbusRingBufInit();
    ModbusSlaveInit();
}

static void modbusGPIOInit(void)
{
	gpio_pin_config_t config =
	{
		kGPIO_DigitalOutput,
		0,
	};
	CLOCK_EnableClock(kCLOCK_PortE);
	PORT_SetPinMux( PORTE , 4, kPORT_MuxAsGpio  );
	GPIO_PinInit( GPIOE , 4, &config);
	Modbus_485en_R();

}

static void modbusUartInit(void)
{
	BSP_UART_Init(BSP_485COM);
//	BSP_UART_SetBaudRate(BSP_485COM, 115200);
} 

static void modbusTimInit(void)
{
	BSP_Tim_Init(BSP_TIM0);
}

void ModbusRevOneByte(uint8_t byte)
{
	if(Uart2RBuf_Ptr<sizeof(Uart2RBuf))
	{
		Uart2RBuf[Uart2RBuf_Ptr++]= byte;
		BSP_Tim_0_StartOnce();	
		
	//	DEBUG("FTM COUNT:%d\r\n" , FTM_GetCurrentTimerCount(FTM0));
		
	}	
}

void ModbusSend(uint8_t * Data,uint16_t Len)
{
	BSP_UART_WriteBytes_DMA(BSP_485COM ,Data, Len);
	
}


void ModbusUartIRQn(void)       
{
//    USART_ClearITPendingBit(USART1, USART_IT_ORE);
//	if((USART_GetITStatus(USART1, USART_IT_RXNE))==1)	//juge interrupt is RNXE :1;
//	{
//		TIM_Cmd(TIM3, DISABLE);
//		TIM_SetCounter( TIM3, 0);
//		uint8_t tmp = USART_ReceiveData(USART1);
//		if(Uart2RBuf_Ptr<sizeof(Uart2RBuf))
//		{
//			Uart2RBuf[Uart2RBuf_Ptr++]= tmp;
//		}
//		TIM_Cmd(TIM3, ENABLE);
//	}
}



void ModbusTimIRQn(void)
{
//	if(TIM_GetITStatus( TIM3, TIM_IT_Update)!= RESET)
//	{
//		TIM_ClearITPendingBit( TIM3, TIM_IT_Update);
//		TIM_Cmd(TIM3, DISABLE);
//		rBufToRing();
//	}
}

void Modbus_485en_R(void)
{
	GPIO_WritePinOutput( GPIOE, 4, 0);	
}

void Modbus_485en_T(void)
{
	GPIO_WritePinOutput( GPIOE, 4, 1);	
}

unsigned short ModbusCRC(unsigned char *ptr, unsigned char size)
{
	unsigned short a, b, tmp, CRC16;
	CRC16 = 0xffff;
	for (a = 0; a < size; a++)
	{
		CRC16 = *ptr^CRC16;
		for (b = 0; b < 8; b++)
		{
			tmp = CRC16 & 0x0001;
			CRC16 = CRC16 >> 1;
			if (tmp)
				CRC16 = CRC16 ^ 0xa001;
		}
		ptr++;
	}
	return (((CRC16 & 0x00FF) << 8) | ((CRC16 & 0xFF00) >> 8));
}


unsigned short checkCRC(unsigned char *ptr, unsigned char size)
{
	unsigned short tmp = 0;
	tmp = ModbusCRC(ptr, size);
    return tmp;
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

