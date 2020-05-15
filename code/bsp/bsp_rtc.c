/**
 **************************************************************************************************
 * @file        bsp_rtc.c
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
#include "bsp_clock.h"
/**
 * @addtogroup    bsp_rtc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_rtc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_rtc_Macros_Defines 
 * @brief         
 * @{  
 */

#define SECONDS_IN_A_DAY (86400U)
#define SECONDS_IN_A_HOUR (3600U)
#define SECONDS_IN_A_MINUTE (60U)
#define DAYS_IN_A_YEAR (365U)
#define YEAR_RANGE_START (1970U)
#define YEAR_RANGE_END (2099U)
/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_rtc_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_rtc_Functions 
 * @brief         
 * @{  
 */
void BSP_RTC_Init(void)
{
	rtc_config_t config = { 0 };
	rtc_datetime_t datetime = { 0 };
	
	CLOCK_EnableClock(kCLOCK_PortC);
	PORT_SetPinMux(PORTC, 1,kPORT_MuxAsGpio);
	gpio_pin_config_t gpio_pin_config ;
	gpio_pin_config.pinDirection = kGPIO_DigitalInput;
	GPIO_PinInit(GPIOC, 1, &gpio_pin_config);
	
	CLOCK_EnableClock(kCLOCK_Rtc0);
	
	CLOCK_SetEr32kClock(2);
	
	RTC_GetDefaultConfig(&config);
		
	RTC_Init(RTC , &config);
	
	RTC_SetOscCapLoad(RTC, kRTC_Capacitor_16p);
	
	
	datetime.year = 2020;
	datetime.month = 1;
	datetime.day = 2;
	datetime.hour = 3;
	datetime.minute = 4;
	datetime.second = 5;
	
	RTC_SetDatetime(RTC , &datetime);
	
	RTC_EnableInterrupts( RTC , kRTC_AlarmInterruptEnable);
	EnableIRQ(RTC_IRQn);

	RTC_StartTimer(RTC);
}

void BSP_RTC_Stop(void)
{
	RTC_StopTimer( RTC );
}
void BSP_RTC_AlarmInterruptEnable(void)
{
	RTC_EnableInterrupts( RTC , kRTC_AlarmInterruptEnable);
	EnableIRQ(RTC_IRQn);
}


void BSP_RTC_ConvertSecondsToDatetime(uint32_t seconds ,  rtc_datetime_t *datetime)
{
    assert(datetime);

    uint32_t x;
    uint32_t secondsRemaining, days;
    uint16_t daysInYear;
    /* Table of days in a month for a non leap year. First entry in the table is not used,
     * valid months start from 1
     */
    uint8_t daysPerMonth[] = {0U, 31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    /* Start with the seconds value that is passed in to be converted to date time format */
    secondsRemaining = seconds;

    /* Calcuate the number of days, we add 1 for the current day which is represented in the
     * hours and seconds field
     */
    days = secondsRemaining / SECONDS_IN_A_DAY + 1;

    /* Update seconds left*/
    secondsRemaining = secondsRemaining % SECONDS_IN_A_DAY;

    /* Calculate the datetime hour, minute and second fields */
    datetime->hour = secondsRemaining / SECONDS_IN_A_HOUR;
    secondsRemaining = secondsRemaining % SECONDS_IN_A_HOUR;
    datetime->minute = secondsRemaining / 60U;
    datetime->second = secondsRemaining % SECONDS_IN_A_MINUTE;

    /* Calculate year */
    daysInYear = DAYS_IN_A_YEAR;
    datetime->year = YEAR_RANGE_START;
    while (days > daysInYear)
    {
        /* Decrease day count by a year and increment year by 1 */
        days -= daysInYear;
        datetime->year++;

        /* Adjust the number of days for a leap year */
        if (datetime->year & 3U)
        {
            daysInYear = DAYS_IN_A_YEAR;
        }
        else
        {
            daysInYear = DAYS_IN_A_YEAR + 1;
        }
    }

    /* Adjust the days in February for a leap year */
    if (!(datetime->year & 3U))
    {
        daysPerMonth[2] = 29U;
    }

    for (x = 1U; x <= 12U; x++)
    {
        if (days <= daysPerMonth[x])
        {
            datetime->month = x;
            break;
        }
        else
        {
            days -= daysPerMonth[x];
        }
    }

    datetime->day = days;	
}

uint32_t BSP_RTC_ConvertDatetimeToSeconds(rtc_datetime_t *datetime)
{
	assert(datetime);

    /* Number of days from begin of the non Leap-year*/
    /* Number of days from begin of the non Leap-year*/
    uint16_t monthDays[] = {0U, 0U, 31U, 59U, 90U, 120U, 151U, 181U, 212U, 243U, 273U, 304U, 334U};
    uint32_t seconds;

    /* Compute number of days from 1970 till given year*/
    seconds = (datetime->year - 1970U) * DAYS_IN_A_YEAR;
    /* Add leap year days */
    seconds += ((datetime->year / 4) - (1970U / 4));
    /* Add number of days till given month*/
    seconds += monthDays[datetime->month];
    /* Add days in given month. We subtract the current day as it is
     * represented in the hours, minutes and seconds field*/
    seconds += (datetime->day - 1);
    /* For leap year if month less than or equal to Febraury, decrement day counter*/
    if ((!(datetime->year & 3U)) && (datetime->month <= 2U))
    {
        seconds--;
    }

    seconds = (seconds * SECONDS_IN_A_DAY) + (datetime->hour * SECONDS_IN_A_HOUR) +
              (datetime->minute * SECONDS_IN_A_MINUTE) + datetime->second;

    return seconds;
}

void BSP_RTC_GetDate(rtc_datetime_t *datetime)
{
	RTC_GetDatetime(RTC , datetime);
}

uint32_t BSP_RTC_GetCurTimeStamp(void)
{
	return RTC->TSR;
}

void BSP_RTC_SetDate(rtc_datetime_t *datetime)
{
	RTC_StopTimer( RTC );
	RTC_SetDatetime( RTC , datetime);
	RTC_StartTimer( RTC );	
}

void BSP_RTC_SetTimeStamp(uint32_t timestamp)
{
	RTC_StopTimer( RTC );
	RTC->TSR = timestamp ;
	RTC_StartTimer( RTC );	
}

void BSP_RTC_SetAlarm_InTime(rtc_datetime_t *alarmTime)
{
	RTC_SetAlarm( RTC , alarmTime);
}

void BSP_RTC_SetAlarm_InTimeStamp(uint32_t timestamp)
{

    uint32_t currSeconds = 0;
    /* Get the current time */
    currSeconds = RTC->TSR;

    /* Return error if the alarm time has passed */
    if (timestamp < currSeconds)
    {
        return ;
    }

    /* Set alarm in seconds*/
    RTC->TAR = timestamp;
}





void BSP_RTC_SetAlarm_InSec(uint32_t sec)
{
	rtc_datetime_t datetime;
	uint32_t sec_temp = 0;
	BSP_RTC_GetDate( &datetime);

	sec_temp = BSP_RTC_ConvertDatetimeToSeconds( &datetime );
	sec_temp += sec;
	BSP_RTC_ConvertSecondsToDatetime( sec_temp , &datetime);
	BSP_RTC_SetAlarm_InTime( &datetime);
	
}




void RTC_IRQHandler(void)
{
	DEBUG("RTC_IRQHandler\r\n");
	if((RTC_GetStatusFlags( RTC ) & kRTC_AlarmFlag ) == kRTC_AlarmFlag)
	{
		RTC_ClearStatusFlags( RTC , kRTC_AlarmFlag);
		//NVIC_SystemReset();
		DEBUG("RTC_IRQHandler Alarm\r\n");
	}
}


// -------Test Func ------------
void BSP_RTC_Test(void)
{
	BSP_RTC_SetAlarm_InSec(10);
}

void BSP_ShowDate(void)
{
	rtc_datetime_t datetime = { 0 } ;
	RTC_GetDatetime(RTC , &datetime);
	DEBUG("%d . %d . %d  %d:%d:%d\r\n" ,datetime.year,datetime.month , datetime.day ,datetime.hour ,datetime.minute ,datetime.second );
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

