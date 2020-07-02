/**
 **************************************************************************************************
 * @file        bsp_adc.c
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

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "bsp_led.h"
#include "app_sample.h"
/**
 * @addtogroup    bsp_adc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_adc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_adc_Macros_Defines 
 * @brief         
 * @{  
 */
#define ADC16_RESULT_REG_ADDR (uint32_t)(&ADC0->R[0]) /* Get ADC16 result register address */
/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_adc_Private_Types
 * @brief         
 * @{  
 */
typedef struct
{
	uint16_t adcbuf[8];
	uint8_t in ;
	uint16_t average;
}bsp_adc_data_t;


/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Private_Variables 
 * @brief         
 * @{  
 */
bsp_adc_data_t bsp_adc_data = 
{
	.in = 0 ,
	.average = 0,
};


/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

static void bsp_adc_trigger_init(void);
 
//static void bsp_adcDMA_init(void);
/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Functions 
 * @brief         
 * @{  
 */
 
/*
PD1 -> ADC0_SE5b  X 101 5
PD5 -> ADC0_SE6b  Z 110 6 
PD6 -> ADC0_SE7b  Y 111 7
*/ 
 
void BSP_ADC_Init(void)
{
	adc16_config_t adc16ConfigStruct;
    //adc16_channel_config_t adc16ChannelConfigStruct;
	// -------GPIO -------
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* PORTD 1 5 6  is configured as ADC0_SE 5 6 7*/
    PORT_SetPinMux(PORTD, 1U, kPORT_PinDisabledOrAnalog);	
	PORT_SetPinMux(PORTD, 5U, kPORT_PinDisabledOrAnalog);	
	PORT_SetPinMux(PORTD, 6U, kPORT_PinDisabledOrAnalog);	

	// -------------------
	// -------ADC -------------
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
    adc16ConfigStruct.clockSource = kADC16_ClockSourceAlt2;
    adc16ConfigStruct.enableAsynchronousClock = false;
    adc16ConfigStruct.clockDivider = kADC16_ClockDivider1;
    adc16ConfigStruct.resolution = kADC16_Resolution16Bit;
    adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
    adc16ConfigStruct.enableHighSpeed = true ;
    adc16ConfigStruct.enableLowPower = false;
    adc16ConfigStruct.enableContinuousConversion = false;  
    ADC16_Init(ADC0, &adc16ConfigStruct);	
	
	//ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */
	ADC16_DoAutoCalibration(ADC0);
	ADC16_SetChannelMuxMode(ADC0, kADC16_ChannelMuxB);	
	// --------------------------------	
	// ---------select trigger --------
	SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(9)| SIM_SOPT7_ADC0ALTTRGEN(0) |SIM_SOPT7_ADC0PRETRGSEL(1);    // need to look reference maunl  ,this is FTM 1
	ADC16_EnableHardwareTrigger( ADC0 , true );

	// --------------------------------
	// -------IRQ---------
	EnableIRQ(ADC0_IRQn);
	NVIC_SetPriority(ADC0_IRQn , 6);
	// -------------------
			// ----------channel------------
//	
//	
//	adc16ChannelConfigStruct.channelNumber = 5;
//	adc16ChannelConfigStruct.enableDifferentialConversion = false;
//	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted =  true;
//	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);
//	
			// -----------------------------
	bsp_adc_trigger_init();		
			
	// ------------------------
}

static void bsp_adc_trigger_init(void)
{
	pdb_config_t pdbConfigStruct;
    pdb_adc_pretrigger_config_t pdbAdcPreTriggerConfigStruct;
    /* Configure the PDB counter. */
    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = false;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);
	pdbConfigStruct.triggerInputSource = kPDB_TriggerInput9;
    PDB_Init(PDB0, &pdbConfigStruct);

    /* Configure the delay interrupt. */
//    PDB_SetModulusValue(PDB0, 1000U);

//    /* The available delay value is less than or equal to the modulus value. */
//    PDB_SetCounterDelayValue(PDB0, 1000U);
//    PDB_EnableInterrupts(PDB0, kPDB_DelayInterruptEnable);
//	EnableIRQ(PDB0_IRQn);
    /* Configure the ADC Pre-Trigger. */
    pdbAdcPreTriggerConfigStruct.enablePreTriggerMask = 1U << 0;
    pdbAdcPreTriggerConfigStruct.enableOutputMask = 1U << 0;
    pdbAdcPreTriggerConfigStruct.enableBackToBackOperationMask = 0U;
    PDB_SetADCPreTriggerConfig(PDB0, 0, &pdbAdcPreTriggerConfigStruct);
    PDB_SetADCPreTriggerDelayValue(PDB0, 0, 0, 0U);
    /* The available Pre-Trigger delay value is less than or equal to the modulus value. */

    PDB_DoLoadValues(PDB0);

}

void BSP_ADC_DeInit(void)
{
	PDB_Deinit(PDB0);
	ADC16_Deinit(ADC0);	
}
void BSP_ADC0_SetChannelConfig(uint8_t channel)
{
	adc16_channel_config_t adc16ChannelConfigStruct;
	adc16ChannelConfigStruct.channelNumber = channel;
	adc16ChannelConfigStruct.enableDifferentialConversion = false;
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted =  true;
	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);
}

void BSP_ADC_DisableIRQ(void)
{
	DisableIRQ(ADC0_IRQn);
}

void BSP_ADC_EnableIRQ(void)
{
	EnableIRQ(ADC0_IRQn);
}




uint32_t BSP_ADC_GetValue(uint8_t channel)
{
	return ADC16_GetChannelConversionValue( ADC0 , 0);
}



uint16_t BSP_ADC_GetAverageValue(uint8_t channel)
{
	return bsp_adc_data.average;
}


// --------------Test -----

uint8_t channel_buf[3] = { 5,6,7 };

void BSP_ADC_ShowValue(void)
{
	
	static uint8_t channel_ptr = 0;
	adc16_channel_config_t adc16ChannelConfigStruct;
	adc16ChannelConfigStruct.channelNumber = channel_buf[channel_ptr ++];
	channel_ptr %= 3;
	adc16ChannelConfigStruct.enableDifferentialConversion = false;
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted =  true;

	ADC16_SetChannelConfig(ADC0, 0, &adc16ChannelConfigStruct);

}

void BSP_ADC_TestTrig(void)
{
	PDB_DoSoftwareTrigger(PDB0);
}

// ------------------------


// -------IRQ ----------------
void ADC0_IRQHandler(void)
{
	uint32_t value = 0 ;
	value = ADC16_GetChannelConversionValue(ADC0, 0);
	APP_GetOriginalData(value);
	//DEBUG("ADC0_IRQHandler : %d\r\n" , value);
}


void PDB0_IRQHandler(void)
{
	DEBUG("PDB0_IRQHandler\r\n");
    PDB_ClearStatusFlags(PDB0, kPDB_DelayEventFlag);
	
}





// ---------------------------




/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

