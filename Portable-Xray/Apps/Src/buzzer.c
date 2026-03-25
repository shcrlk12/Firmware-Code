/*
 * buzzer.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */
#include "buzzer.h"

uint16_t buzzer_time_counter = 0;
uint16_t buzzer_duration = 0;
bool buzzer_on = false;

void BUZZER_TIMER_Interrupt_Handler(void)
{
	// buzzer BMX-3203, resonant frequency 3.2kHz, 3V, 90dBSPL@10cm
	// 50% duty signal required
	// with the settings of IOC file, timer will generate 6.4kHz triggers
	// if sound is too loud, just reduce frequency
//    IO_BUZZER_Toggle();
}

// these functions are to be called from main state machine
void BUZZER_Set(uint8_t state)
{
	if (state == 1)
	{
        // start timer
//        timer_buzzer->Start();
	}
	else
	{
//        timer_buzzer->Stop();
//        IO_BUZZER_SetLow();
	}
}

void BUZZER_Beep(uint16_t duration)
{
	buzzer_time_counter = 0;
	buzzer_duration = duration;
	BUZZER_Set(1);
	buzzer_on = true;
}

void BUZZER_Update(void)
{
	if(buzzer_time_counter < buzzer_duration)
	{
		buzzer_time_counter++;
	}
	else if(buzzer_on == true)
	{
		BUZZER_Set(0);
		buzzer_on = false;
	}
}

void BUZZER_Initialize()
{
//    timer_buzzer->PeriodSet(28499); // ~3.5kHz
//    timer_buzzer->Stop();
//    timer_buzzer->TimeoutCallbackRegister(BUZZER_TIMER_Interrupt_Handler);
}
