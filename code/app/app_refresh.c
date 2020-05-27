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
#include "system_param.h"
#include "modbus_map.h"
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
static uint8_t app_refresh_waveFalg = 0;
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
static void app_refresh_version(void);
/**
 * @}
 */

/**
 * @defgroup      app_refresh_Functions 
 * @brief         
 * @{  
 */
void APP_RefreshMB_Charateristic(void)
{
	uint16_t data_temp = 0;
	
	// ----------- Z base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_Z_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_BASE_FREQ , data_temp) != 1)
	{
	}
	// ----------- Z ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_ACC_P , data_temp) != 1)
	{
	}
	// ----------- Z ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_ACC_RMS , data_temp) != 1)
	{
	}	
	// ----------- Z Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_VELOCITY_RMS , data_temp) != 1)
	{
	}	
	// ----------- Z Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_DISPLACE_PP , data_temp) != 1)
	{
	}	
	// ----------- Z Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_KURTOSIS_COE , data_temp) != 1)
	{
	}	
	// ----------- Z Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Z_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_ENVELOPE , data_temp) != 1)
	{
	}	

	// -----------------------------------------------------
	// ----------- X base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_X_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_BASE_FREQ , data_temp) != 1)
	{
	}
	// ----------- X ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_ACC_P , data_temp) != 1)
	{
	}
	// ----------- X ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_ACC_RMS , data_temp) != 1)
	{
	}	
	// ----------- X Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_VELOCITY_RMS , data_temp) != 1)
	{
	}	
	// ----------- X Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_DISPLACE_PP , data_temp) != 1)
	{
	}	
	// ----------- X Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_KURTOSIS_COE , data_temp) != 1)
	{
	}	
	// ----------- X Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_X_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_ENVELOPE , data_temp) != 1)
	{
	}	

	// ------------------------------------------------------
	// ----------- Y base Freq ----------
	data_temp = (uint16_t)APP_CalcValue[APP_SAMPLE_Y_INDEX].BaseFreq;
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_BASE_FREQ , data_temp) != 1)
	{
	}
	// ----------- Y ACC_P --------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].ACC_P * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_ACC_P , data_temp) != 1)
	{
	}
	// ----------- Y ACC_RMS ------------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].ACC_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_ACC_RMS , data_temp) != 1)
	{
	}	
	// ----------- Y Velocity_RMS -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Velocity_RMS * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_VELOCITY_RMS , data_temp) != 1)
	{
	}	
	// ----------- Y Displace_PP -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Displace_PP * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_DISPLACE_PP , data_temp) != 1)
	{
	}	
	// ----------- Y Kurtosis Coe -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Kurtosis_Coefficient * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_KURTOSIS_COE , data_temp) != 1)
	{
	}	
	// ----------- Y Envelope -------
	data_temp = (uint16_t)(APP_CalcValue[APP_SAMPLE_Y_INDEX].Envelope * 100);
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_ENVELOPE , data_temp) != 1)
	{
	}	
	
	
	// ----------- Temperature ----------
	
	// ----------- Version --------------

	app_refresh_version();
	
}



static void app_refresh_version(void)
{
	// ----------- Version --------------

	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_VERSION_MAJOR , VERSION_MAJOR) != 1)
	{
	}	
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_VERSION_MINOR , VERSION_MINOR) != 1)
	{
	}		
	if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_VERSION_LITE , VERSION_LITE) != 1)
	{
	}	
}

void APP_RefreshMB_ConfParam(void)
{
	uint16_t data_temp = 0;
	// ----------- Slave_ID ----------
	data_temp = (uint16_t)g_SystemParam_Config.MB_Slave_ID;
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_SLAVE_ID , data_temp) != 1)
	{
	}
	// ----------- SN_Code ----------
	
	for(uint8_t i = 0 ; i < 8 ; i ++)
	{
		data_temp = (uint16_t)g_SystemParam_Config.SNcode[i];
		if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_SNCODE + i , data_temp) != 1)
		{
		}
	}
	
	// ----------- Z_Sensitivity ----------
	data_temp = (uint16_t)(g_SystemParam_Config.Z_Axial_Sensitivity * 100);
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_Z_SENSITIVITY , data_temp) != 1)
	{
	}	
	// ----------- X_Sensitivity ----------
	data_temp = (uint16_t)(g_SystemParam_Config.X_Axial_Sensitivity * 100);
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_X_SENSITIVITY , data_temp) != 1)
	{
	}		
	// ----------- Y_Sensitivity ----------
	data_temp = (uint16_t)(g_SystemParam_Config.Y_Axial_Sensitivity * 100);
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_Y_SENSITIVITY , data_temp) != 1)
	{
	}		

	// ----------- FFT V_LowPass ----------
	data_temp = (uint16_t)(g_SystemParam_Config.FFT_V_LowPass );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_V_LOWPASS , data_temp) != 1)
	{
	}	
	// ----------- FFT V_HighPass ----------
	data_temp = (uint16_t)(g_SystemParam_Config.FFT_V_HighPass );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_V_HIGHPASS , data_temp) != 1)
	{
	}	
	// ----------- FFT X_LowPass ----------
	data_temp = (uint16_t)(g_SystemParam_Config.FFT_X_LowPass );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_X_LOWPASS , data_temp) != 1)
	{
	}	
	// ----------- FFT X_HighPass ----------
	data_temp = (uint16_t)(g_SystemParam_Config.FFT_X_HighPass );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_X_HIGHPASS , data_temp) != 1)
	{
	}		
	
	// ----------- Temperature_C ----------
	data_temp = (uint16_t)(g_SystemParam_Config.Temperature_C * 100);
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_TEMPTERATURE , data_temp) != 1)
	{
	}		
	
	// ----------- Waveform Interal ----------
	data_temp = (uint16_t)(g_SystemParam_Config.Waveform_Interval );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_WAVE_INTERVAL , data_temp) != 1)
	{
	}		
	
	// ----------- Baudrate Bps ----------
	data_temp = (uint16_t)(g_SystemParam_Config.BaudRate_Bps );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_BAUDRATE_BPS , data_temp) != 1)
	{
	}			
	// ----------- ParityMode ----------
	data_temp = (uint16_t)(g_SystemParam_Config.ParityMode );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_PARITYMODE , data_temp) != 1)
	{
	}				
	// ----------- StopbitCount ----------
	data_temp = (uint16_t)(g_SystemParam_Config.StopBitCount );
	if( MB_WirteRegister(MBREGISTERHOLDING, MB_REGHOLD_STOPBITCOUNT , data_temp) != 1)
	{
	}			
}

void APP_Refresh_MBtoSys(void)
{

	uint16_t data_temp = 0;
	// ----------- Slave_ID ----------
	
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_SLAVE_ID , &data_temp) == 1)
	{
		g_SystemParam_Config.MB_Slave_ID = (uint8_t)data_temp;
	}
	// ----------- SN_Code ----------
	
	for(uint8_t i = 0 ; i < 8 ; i ++)
	{
		if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_SNCODE + i , &data_temp) == 1)
		{
			g_SystemParam_Config.SNcode[i] = (uint8_t)data_temp;
		}
	}
	
	// ----------- Z_Sensitivity ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_Z_SENSITIVITY , &data_temp) == 1)
	{
		g_SystemParam_Config.Z_Axial_Sensitivity = (float)(data_temp / 100);
	}	
	// ----------- X_Sensitivity ----------

	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_X_SENSITIVITY , &data_temp) == 1)
	{
		g_SystemParam_Config.X_Axial_Sensitivity = (float)(data_temp / 100);
	}		
	// ----------- Y_Sensitivity ----------

	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_Y_SENSITIVITY , &data_temp) == 1)
	{
		g_SystemParam_Config.Y_Axial_Sensitivity = (float)(data_temp / 100);
	}		

	// ----------- FFT V_LowPass ----------
	
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_V_LOWPASS , &data_temp) == 1)
	{
		g_SystemParam_Config.FFT_V_LowPass = data_temp;
	}	
	// ----------- FFT V_HighPass ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_V_HIGHPASS , &data_temp) == 1)
	{
		g_SystemParam_Config.FFT_V_HighPass = data_temp;
	}	
	// ----------- FFT X_LowPass ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_X_LOWPASS , &data_temp) == 1)
	{
		g_SystemParam_Config.FFT_X_LowPass = data_temp;
	}	
	// ----------- FFT X_HighPass ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_FFT_X_HIGHPASS , &data_temp) == 1)
	{
		g_SystemParam_Config.FFT_X_HighPass = data_temp;
	}		
	
	// ----------- Temperature_C ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_TEMPTERATURE , &data_temp) == 1)
	{
		g_SystemParam_Config.Temperature_C = (float)(data_temp / 100);
	}		
	
	// ----------- Waveform Interal ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_WAVE_INTERVAL , &data_temp) == 1)
	{
		g_SystemParam_Config.Waveform_Interval = (uint8_t) data_temp;
	}		

	// ----------- Baudrate Bps ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_BAUDRATE_BPS , &data_temp) == 1)
	{
		g_SystemParam_Config.BaudRate_Bps  = (uint8_t)data_temp;
	}			
	// ----------- ParityMode ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_PARITYMODE , &data_temp) == 1)
	{
		g_SystemParam_Config.ParityMode = (uint8_t)data_temp;
	}				
	// ----------- StopbitCount ----------
	if( MB_ReadRegister(MBREGISTERHOLDING, MB_REGHOLD_STOPBITCOUNT , &data_temp) == 1)
	{
		g_SystemParam_Config.StopBitCount = (uint8_t)data_temp ; 
	}		
	
	//SystemParam_Save();	
}


void APP_RefreshMB_Waveform(void)
{
	app_refresh_waveFalg = 1;
}

void APP_Refresh_MoveWavetoMB(uint8_t channel , float * buf  )
{
	if(app_refresh_waveFalg == 1)
	{
		uint16_t data_temp = 0;
		if(channel == APP_SAMPLE_X_INDEX)
		{
			for(uint16_t i = 0 ; i < 2000; i ++)
			{
				data_temp = (uint16_t)(buf[i] * 100);
				if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_X_WAVEFORM + i, data_temp) != 1)
				{
				}				
			}			
		}
		if(channel == APP_SAMPLE_Y_INDEX)
		{
			for(uint16_t i = 0 ; i < 2000; i ++)
			{
				data_temp = (uint16_t)(buf[i] * 100);
				if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Y_WAVEFORM + i, data_temp) != 1)
				{
				}				
			}			
		}
		if(channel == APP_SAMPLE_Z_INDEX)
		{
			for(uint16_t i = 0 ; i < 2000; i ++)
			{
				data_temp = (uint16_t)(buf[i] * 100);
				if( MB_WirteRegister(MBREGISTERINPUT, MB_REGINPUT_Z_WAVEFORM + i, data_temp) != 1)
				{
				}				
			}	

			app_refresh_waveFalg = 0;
				
		}		
		
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

