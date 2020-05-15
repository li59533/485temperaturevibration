/**
 **************************************************************************************************
 * @file        bsp_lmt01.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_lmt01.h"
#include "bsp_conf.h"
/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"
#include "system_param.h"
#include "osal.h"
/**
 * @addtogroup    bsp_lmt01_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_lmt01_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Macros_Defines 
 * @brief         
 * @{  
 */

#define LMT01_POWER_ON	GPIO_WritePinOutput(GPIOE, 1, 1)
#define LMT01_POWER_OFF	GPIO_WritePinOutput(GPIOE, 1, 0)



/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	uint32_t lmt01_pulse_count ;
	uint32_t lmt01_pulse_count_record ;
	uint8_t lmt01_pulse_status;
	uint8_t lmt01_updata_status;
	float lmt01_value;
}bsp_lmt01_data_t ;



/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Private_Variables 
 * @brief         
 * @{  
 */

static bsp_lmt01_data_t bsp_lmt01_data =
{
	.lmt01_pulse_count = 0,
	.lmt01_pulse_count_record = 0,
	.lmt01_pulse_status = LMT01_Pulse_OFF,
	.lmt01_updata_status = LMT01_Updata_NoUp,
};
/**
 * @}
 */
 
/**
 * @defgroup      bsp_lmt01_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_lmt01_Functions 
 * @brief         
 * @{  
 */
 
/*
Power -> PE1
pulse -> PD7
*/ 
 
 
//void BSP_LMT01_Init(void)
//{
//	// ------GPIO --------
//	gpio_pin_config_t gpio_pin_config ;
//	CLOCK_EnableClock(kCLOCK_PortD);
//	CLOCK_EnableClock(kCLOCK_PortE);
//	
//	PORT_SetPinMux(PORTD, 7,kPORT_MuxAsGpio);
//	gpio_pin_config.outputLogic = 0;
//	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
//	GPIO_PinInit(GPIOD, 7, &gpio_pin_config);

//	PORT_SetPinMux(PORTE, 1,kPORT_MuxAsGpio);
//	gpio_pin_config.outputLogic = 0;
//	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
//	GPIO_PinInit(GPIOE, 1, &gpio_pin_config);	
//	
//	PORT_SetPinInterruptConfig(PORTD, 7, kPORT_InterruptRisingEdge)	;
//	
//	EnableIRQ(PORTC_PORTD_IRQn);	
//}

void BSP_LMT01_Power_ON(void)
{
	// ------GPIO --------
	gpio_pin_config_t gpio_pin_config ;
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortE);
	
	PORT_SetPinMux(PORTD, 7,kPORT_MuxAsGpio);
	gpio_pin_config.outputLogic = 0;
	gpio_pin_config.pinDirection = kGPIO_DigitalInput;
	GPIO_PinInit(GPIOD, 7, &gpio_pin_config);

	PORT_SetPinMux(PORTE, 1,kPORT_MuxAsGpio);
	gpio_pin_config.outputLogic = 0;
	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
	GPIO_PinInit(GPIOE, 1, &gpio_pin_config);	
	
	PORT_SetPinInterruptConfig(PORTD, 7, kPORT_InterruptRisingEdge)	;
	
	EnableIRQ(PORTC_PORTD_IRQn);		
	
	LMT01_POWER_ON;
}

void BSP_LMT01_Power_OFF(void)
{
	gpio_pin_config_t gpio_pin_config ;
	LMT01_POWER_OFF;

	DisableIRQ(PORTC_PORTD_IRQn);
	PORT_SetPinInterruptConfig(PORTD, 7, kPORT_InterruptOrDMADisabled)	;

	PORT_SetPinMux(PORTD, 7,kPORT_MuxAsGpio);
	gpio_pin_config.outputLogic = 0;
	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
	GPIO_PinInit(GPIOD, 7, &gpio_pin_config);

	PORT_SetPinMux(PORTE, 1,kPORT_MuxAsGpio);
	gpio_pin_config.outputLogic = 0;
	gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
	GPIO_PinInit(GPIOE, 1, &gpio_pin_config);	

	CLOCK_DisableClock(kCLOCK_PortD);
	CLOCK_DisableClock(kCLOCK_PortE);	
}


void BSP_LMT01_CoreLoop(void)  //call this func in 20ms
{

	switch(bsp_lmt01_data.lmt01_pulse_status)
	{
		case LMT01_Pulse_ON:
		{

			bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_OFF;
		}
		break;
		case LMT01_Pulse_OFF:
		{
			bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_Wait;
			bsp_lmt01_data.lmt01_pulse_count_record = bsp_lmt01_data.lmt01_pulse_count;
			bsp_lmt01_data.lmt01_pulse_count  = 0;
			bsp_lmt01_data.lmt01_value = ((float)bsp_lmt01_data.lmt01_pulse_count_record * 0.0625f - 50) + g_SystemParam_Config.tempCompensation*0.1f; //²¹³¥Öµ
			bsp_lmt01_data.lmt01_updata_status = LMT01_Updata_HasUp;			
		}
		break;
		case LMT01_Pulse_Wait:
		{
			
		}
		break;
		default:break;
	}
	
}

uint8_t BSP_LMT01_GetDataStatus(void)
{
	return bsp_lmt01_data.lmt01_updata_status;
}

float BSP_LMT01_GetValue(void)
{
	bsp_lmt01_data.lmt01_updata_status = LMT01_Updata_NoUp;
	return bsp_lmt01_data.lmt01_value;
}

// -------------------IRQ-------------

void PORTC_PORTD_IRQHandler(void)
{
	if((PORT_GetPinsInterruptFlags(PORTD) & (0x01 << 7) )== (0x01 << 7))
	{
		//DEBUG("PORTC_PORTD_IRQHandler");
		bsp_lmt01_data.lmt01_pulse_count ++;
		bsp_lmt01_data.lmt01_pulse_status = LMT01_Pulse_ON;
		PORT_ClearPinsInterruptFlags( PORTD, (0x01 << 7));
	}
}

// ------------------Test ------------

void BSP_LMT01_TestFunc(void)
{
	if(BSP_LMT01_GetDataStatus() == LMT01_Updata_HasUp)
	{
		char test_c[50] = { 0 };
		
		sprintf(test_c , "LMT01:%f,PulseCount:%d\r\n" ,bsp_lmt01_data.lmt01_value ,bsp_lmt01_data.lmt01_pulse_count_record);
		DEBUG("%s" , test_c);
	}
	else
	{
		DEBUG("LMT01 Value is NoUp\r\n");
	}
}

// -----------------------------------


/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

