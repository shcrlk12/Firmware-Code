/*
 * led.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_LED_H_
#define INC_LED_H_

void LED_Update(void);

void LED_AllOff(void);
void LED_AllOn(void);

void LED_ErrorOn(void);
void LED_ErrorOff(void);

void LED_PowerOn(void);
void LED_PowerOff(void);

void LED_RecordOn(void);
void LED_RecordOff(void);

void LED_WaitOn(void);
void LED_WaitOff(void);

void LED_ReadyOn(void);
void LED_ReadyOff(void);

void LED_ExposureOn(void);
void LED_ExposureOff(void);

#endif /* INC_LED_H_ */
