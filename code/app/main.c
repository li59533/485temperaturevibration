/*
 * This is template for main module created by KSDK Project Generator. Enjoy!
 */

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"


/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "clog.h"
#include "rtos_tools.h"
#include "task_list.h"


/*!
 * @brief Application entry point.
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	
	DEBUG("Start\r\n");
	RTOS_Init();
}


void HardFault_Handler(void)
{
	while(1)
	{
		DEBUG("HardFault_Handler\r\n");
	}
}

