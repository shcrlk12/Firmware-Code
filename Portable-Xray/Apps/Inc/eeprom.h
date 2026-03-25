/*
 * eeprom.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

// 7-bit rtc device address (b1010001)
#define RTC_DEVICE_ADDRESS 0x51

// 7-bit eeprom device address (b1010000)
#define EEPROM_DEVICE_ADDRESS 0x50
#define EEPROM_PAGE_HALF 32

// memory address (256kbit, 0x0000 ~ 0x7FFF)
#define ADDR_HEADER_INFO 0x0000
#define ADDR_SERIAL_INFO 0x0020
#define ADDR_EXPOSURE_SETTINGS 0x0040
#define ADDR_ERROR_THRESHOLDS 0x0060
#define ADDR_GATE_CONTROL_VARS 0x0080
#define ADDR_ANODE_CONTROL_VARS 0x00A0
#define ADDR_BUCK_CONTROL_VARS 0x00C0
#define ADDR_TIMING_VARS 0x00E0
#define ADDR_SYS_OPTIONS 0x0100
#define ADDR_CAL_PARAMS 0x0120
#define ADDR_CAL_RESULT 0x0140
#define ADDR_CAL_TABLE 0x0160
#define ADDR_DAISY_PARAMS 0x0180
#define ADDR_SEQ_OPTIONS 0x01A0
#define ADDR_BOARD_GATE_PARAMS 0x01C0
#define ADDR_BOARD_ANODE_PARAMS 0x01E0

#define ADDR_WERAY_SYS_SETTINGS 0x0200
#define ADDR_WERAY_UI_SETTINGS 0x0220
#define ADDR_WERAY_THRESHOLDS 0x0240
#define ADDR_WERAY_LED_PRESETS 0x0260
#define ADDR_WERAY_TIMINGS 0x0280
#define ADDR_WERAY_UI_BLINKS 0x02A0
#define ADDR_WERAY_OPTIONS 0x02C0
#define ADDR_WERAY_CIRCUIT 0x02E0

#define ADDR_ANODE_CONTROL_PID 0x0400
#define ADDR_GATE_CONTROL_PID 0x0420

#define N_ERROR_PAGES 16
#define ERROR_PAGE_MASK 15
#define ADDR_ERROR_INFO 0x1000
#define N_RESULT_PAGES 128
#define RESULT_PAGE_MASK 127
#define ADDR_EXPOSURE_RESULTS 0x2000

void EEPROM_UpdateTimeCount(void);
void EEPROM_Write(uint16_t address, uint8_t *data, int length);
void EEPROM_WriteByte(uint16_t address, uint8_t byte);
void EEPROM_WriteWord(uint16_t address, uint16_t word);
void EEPROM_WriteDWord(uint16_t address, uint32_t dword);
void EEPROM_WriteExposureResults();
void EEPROM_WriteErrorInfo();
void EEPROM_WriteCalibrationResults();
void EEPROM_Read(uint16_t address, uint8_t *data, int length);
uint8_t EEPROM_ReadByte(uint16_t address);
uint16_t EEPROM_ReadWord(uint16_t address);
uint32_t EEPROM_ReadDWord(uint16_t address);
void EEPROM_CheckAndLoad();
void EEPROM_LoadAll();
void EEPROM_Init();
void EEPROM_WerayInit();

void RTC_PrintTime();
void RTC_ResetTime();
uint16_t RTC_GetTimeSpanInDays();

#ifdef	__cplusplus
}
#endif

#endif /* INC_EEPROM_H_ */
