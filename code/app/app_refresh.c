/**
 **************************************************************************************************
 * @file        app_refresh.c
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "app_refresh.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_calc.h"
#include "app_sample.h"
#include "modbus_rtu.h"
#include "version.h"
/**
 * @addtogroup    app_refresh_Modules 
 * @{  
 */

/**
 * @defgroup      app_refresh_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_refresh_Functions 
 * @brief         
 * @{  
 */
void APP_Refresh_Charateristic(void)
{
	uint16_t data_temp = 0;
	
	// ----------- Z base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_Z_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, 0 , data_temp) != 1)
	{
	}
	// ----------- Z ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 1 , data_temp) != 1)
	{
	}
	// ----------- Z ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 2 , data_temp) != 1)
	{
	}	
	// ----------- Z Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 3 , data_temp) != 1)
	{
	}	
	// ----------- Z Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 4 , data_temp) != 1)
	{
	}	
	// ----------- Z Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 5 , data_temp) != 1)
	{
	}	
	// ----------- Z Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 6 , data_temp) != 1)
	{
	}	

	// -----------------------------------------------------
	// ----------- X base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_X_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, 10 , data_temp) != 1)
	{
	}
	// ----------- X ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 11 , data_temp) != 1)
	{
	}
	// ----------- X ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 12 , data_temp) != 1)
	{
	}	
	// ----------- X Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 13 , data_temp) != 1)
	{
	}	
	// ----------- X Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 14 , data_temp) != 1)
	{
	}	
	// ----------- X Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 15 , data_temp) != 1)
	{
	}	
	// ----------- X Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 16 , data_temp) != 1)
	{
	}	

	// ------------------------------------------------------
	// ----------- Y base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_Y_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, 20 , data_temp) != 1)
	{
	}
	// ----------- Y ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 21 , data_temp) != 1)
	{
	}
	// ----------- Y ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 22 , data_temp) != 1)
	{
	}	
	// ----------- Y Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 23 , data_temp) != 1)
	{
	}	
	// ----------- Y Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 24 , data_temp) != 1)
	{
	}	
	// ----------- Y Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 25 , data_temp) != 1)
	{
	}	
	// ----------- Y Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, 26 , data_temp) != 1)
	{
	}	
	
	
	// ----------- Temperature ----------
	
	// ----------- Version --------------

	if( MB_WirteRegister(MBREGISTERINPUT, 36 , VERSION_MAJOR) != 1)
	{
	}	
	if( MB_WirteRegister(MBREGISTERINPUT, 37 , VERSION_MINOR) != 1)
	{
	}		
	if( MB_WirteRegister(MBREGISTERINPUT, 38 , VERSION_LITE) != 1)
	{
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

