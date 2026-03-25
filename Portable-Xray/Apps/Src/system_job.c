/*
 * system_job.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */
#include "main_system.h"

void System_Job()
{
	LED_Update();
	LCD_Update();
	BUZZER_Update();
}
