/**
 **************************************************************************************************
 * @file        modbus_map.h
 * @author
 * @version
 * @date        5/28/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _MODBUS_MAP_H_
#define _MODBUS_MAP_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */

/**
 * @addtogroup    modbus_map_Modules 
 * @{  
 */

/**
 * @defgroup      modbus_map_Exported_Macros 
 * @{  
 */

/*
#define MBREGISTERCOILS 			0
#define MBREGISTERDISCRETEINPUT    	1
#define MBREGISTERHOLDING  			2   // RW
#define MBREGISTERINPUT  			3   // R
*/

// ---MBREGISTERHOLDING ADDR---
typedef enum
{
	MB_REGHOLD_SLAVE_ID			= 0 ,
	MB_REGHOLD_SNCODE			= 1 ,
	MB_REGHOLD_Z_SENSITIVITY	= 9 ,
	MB_REGHOLD_X_SENSITIVITY	= 10 ,
	MB_REGHOLD_Y_SENSITIVITY	= 11 ,
	MB_REGHOLD_FFT_V_LOWPASS		= 12 ,
	MB_REGHOLD_FFT_V_HIGHPASS		= 13 ,
	MB_REGHOLD_FFT_X_LOWPASS		= 14 ,
	MB_REGHOLD_FFT_X_HIGHPASS		= 15 ,	
	MB_REGHOLD_TEMPTERATURE		= 16 ,
	MB_REGHOLD_WAVE_INTERVAL	= 17 ,
	MB_REGHOLD_BAUDRATE_BPS     = 18 , 
	MB_REGHOLD_PARITYMODE		= 19 ,
	MB_REGHOLD_STOPBITCOUNT     = 20 ,
	MB_REGHOLD_DEVICE_REST		= 21 , 
	MB_REGHOLD_X_ANGLE			= 22 ,
	MB_REGHOLD_Z_SELF_CAL		= 23 ,
	MB_REGHOLD_X_SELF_CAL		= 24 ,
	MB_REGHOLD_Y_SELF_CAL		= 25 ,
	
}MB_Reg_Hold_e;

// -----------------------------
// ---MBREGISTERINPUT    ADDR---

typedef enum
{

	MB_REGINPUT_Z_BASE_FREQ		= 0 ,
	MB_REGINPUT_Z_ACC_P			= 1 ,
	MB_REGINPUT_Z_ACC_RMS		= 2 ,
	MB_REGINPUT_Z_VELOCITY_RMS	= 3 ,
	MB_REGINPUT_Z_DISPLACE_PP	= 4 ,
	MB_REGINPUT_Z_KURTOSIS_COE	= 5 ,
	MB_REGINPUT_Z_ENVELOPE		= 6 ,
	MB_REGINPUT_Z_DISPLACE_RMS	= 7 ,

	MB_REGINPUT_X_BASE_FREQ		= 10 ,
	MB_REGINPUT_X_ACC_P			= 11 ,
	MB_REGINPUT_X_ACC_RMS		= 12 ,
	MB_REGINPUT_X_VELOCITY_RMS	= 13 ,
	MB_REGINPUT_X_DISPLACE_PP	= 14 ,
	MB_REGINPUT_X_KURTOSIS_COE	= 15 ,
	MB_REGINPUT_X_ENVELOPE		= 16 ,
	MB_REGINPUT_X_DISPLACE_RMS	= 17 ,
	
	MB_REGINPUT_Y_BASE_FREQ		= 20 ,
	MB_REGINPUT_Y_ACC_P			= 21 ,
	MB_REGINPUT_Y_ACC_RMS		= 22 ,
	MB_REGINPUT_Y_VELOCITY_RMS	= 23 ,
	MB_REGINPUT_Y_DISPLACE_PP	= 24 ,
	MB_REGINPUT_Y_KURTOSIS_COE	= 25 ,
	MB_REGINPUT_Y_ENVELOPE		= 26 ,
	MB_REGINPUT_Y_DISPLACE_RMS	= 27 ,

	MB_REGINPUT_TEMPERATURE     = 30 ,

	MB_REGINPUT_VERSION_MAJOR	= 97 ,
	MB_REGINPUT_VERSION_MINOR	= 98 ,
	MB_REGINPUT_VERSION_LITE	= 99 ,
	
	MB_REGINPUT_Z_WAVEFORM = 100 , 
	MB_REGINPUT_X_WAVEFORM = 2100 , 
	MB_REGINPUT_Y_WAVEFORM = 4100 , 
	
	
	
}MB_Reg_Input_e;


// -----------------------------
/**
 * @}
 */

/**
 * @defgroup      modbus_map_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_map_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_map_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      modbus_map_Exported_Functions 
 * @{  
 */

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
