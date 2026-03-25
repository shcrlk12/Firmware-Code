/*
 * main_system.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef MAIN_SYSTEM_H_
#define MAIN_SYSTEM_H_

#include "state_machine_type.h"
#include "data_struct.h"
#include "fw_info.h"
#include "state_machine.h"
#include "system_job.h"
#include "lcd.h"
#include "led.h"
#include "buzzer.h"
#include "bitflags.h"
#include "error.h"
#include "adc.h"

enum SYSTEM_ERROR_CODES
{
    SYSTEM_ERROR_NONE = 0,
    SYSTEM_ERROR_ANODE_OVERVOLTAGE = 1,
    SYSTEM_ERROR_ANODE_UNDERVOLTAGE = 2,
    SYSTEM_ERROR_GATE_OVERVOLTAGE = 3,
    SYSTEM_ERROR_TUBE_OVERCURRENT = 4,
    SYSTEM_ERROR_TUBE_OVERTEMPERATURE = 5,
    SYSTEM_ERROR_GATE_SETV_HIGH = 6,
    SYSTEM_ERROR_GATE_UNDERVOLTAGE = 7,
    SYSTEM_ERROR_TUBE_UNDERCURRENT = 8,
    SYSTEM_ERROR_ACCU_OVERVOLTAGE = 9,
    SYSTEM_ERROR_UNDERTEMPERATURE = 10,
    SYSTEM_ERROR_BATTERY_OVERDISCHARGE = 20,
    SYSTEM_ERROR_BATTERY_LOW = 21,
    SYSTEM_ERROR_BATTERY_HIGH = 22,
    SYSTEM_ERROR_CONDITIONING_FAIL = 30,
    SYSTEM_ERROR_EEPROM_ERROR = 40,
    SYSTEM_ERROR_INTERLOCK_OPEN = 50,
    SYSTEM_ERROR_BY_USER = 70,
};

void MainStateMachine_Loop();

extern STRUCT_ACCU_SYSTEM g_accu_system;
extern STRUCT_WERAY_PARAMS g_weray;

#endif /* MAIN_SYSTEM_H_ */
