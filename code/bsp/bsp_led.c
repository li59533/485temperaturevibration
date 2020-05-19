/**
 **************************************************************************************************
 * @file        bsp_led.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_led.h"
#include "bsp_conf.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_led_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_led_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_led_Macros_Defines 
 * @brief         
 * @{  
 */
/* Modes */
#define BSP_LED_MODE_OFF     0x00
#define BSP_LED_MODE_ON      0x01
#define BSP_LED_MODE_BLINK   0x02
#define BSP_LED_MODE_FLASH   0x04
/**
 * @}
 */

/**
 * @defgroup      bsp_led_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_led_Private_Types
 * @brief         
 * @{  
 */
typedef struct {
  uint8_t mode;       /* Operation mode */
#if (defined BSP_LED_BLINK_ENABLE) && (BSP_LED_BLINK_ENABLE == TRUE)
  uint8_t todo;       /* Blink cycles left */
  uint8_t onPct;      /* On cycle percentage */
  uint16_t time;      /* On/off cycle time (msec) */
  uint32_t next;      /* Time for next change */
  uint8_t preBlinkState;
#endif
} BSPLedControl_t; 
 
 
typedef struct
{
	clock_ip_name_t clock_ip_name;
	PORT_Type *PORT_Type_base;
	GPIO_Type *GPIO_Type_base;
	uint32_t pin;
	port_mux_t mux;
	gpio_pin_config_t gpio_pin_config;
}GPIO_InstanceTypedef;
 
 
typedef struct
{
    GPIO_InstanceTypedef Pin;
    uint8_t OnLevel;
    uint8_t OffLevel;
}LED_IO_Typedef;


/*

PE4

*/


const LED_IO_Typedef LED_IO[BSP_LEDCOUNT] = 
{
	{
		{kCLOCK_PortE , PORTE, GPIOE , 4, kPORT_MuxAsGpio ,kGPIO_DigitalOutput ,0},
		.OnLevel = 1,
        .OffLevel = 0,
	},
};


/**
 * @}
 */

/**
 * @defgroup      bsp_led_Private_Variables 
 * @brief         
 * @{  
 */
static BSPLedControl_t s_BSPLedControlTable[BSP_LEDCOUNT] =
{
    {BSP_LED_MODE_OFF},
};
/**
 * @}
 */

/**
 * @defgroup      bsp_led_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_led_Functions 
 * @brief         
 * @{  
 */

void BSP_LED_Init(void)
{
	uint8_t i  = 0;

	for(i = 0; i < BSP_LEDCOUNT ; i++)
	{
		CLOCK_EnableClock(LED_IO[i].Pin.clock_ip_name);

		PORT_SetPinMux( LED_IO[i].Pin.PORT_Type_base, LED_IO[i].Pin.pin, LED_IO[i].Pin.mux  );
		GPIO_PinInit(LED_IO[i].Pin.GPIO_Type_base, LED_IO[i].Pin.pin, &LED_IO[i].Pin.gpio_pin_config);
		
		GPIO_WritePinOutput(LED_IO[i].Pin.GPIO_Type_base, LED_IO[i].Pin.pin, LED_IO[i].OffLevel);		
	}

}


void BSP_LED_Open(uint8_t BSP_LEDx)
{
	
	GPIO_WritePinOutput(LED_IO[BSP_LEDx].Pin.GPIO_Type_base, LED_IO[BSP_LEDx].Pin.pin, LED_IO[BSP_LEDx].OnLevel);
	s_BSPLedControlTable[BSP_LEDx].mode = BSP_LED_MODE_ON;
}

void BSP_LED_Close(uint8_t BSP_LEDx)
{
	GPIO_WritePinOutput(LED_IO[BSP_LEDx].Pin.GPIO_Type_base, LED_IO[BSP_LEDx].Pin.pin, LED_IO[BSP_LEDx].OffLevel);
	s_BSPLedControlTable[BSP_LEDx].mode = BSP_LED_MODE_OFF;
}


void BSP_LED_Toggle(uint8_t BSP_LEDx)
{
	
    if (s_BSPLedControlTable[BSP_LEDx].mode & BSP_LED_MODE_ON)
    {
        BSP_LED_Close(BSP_LEDx);
    }
    else 
    {
        BSP_LED_Open(BSP_LEDx);
    }	
	
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

