/*
 * key.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
	KEY_IDLE,
	KEY_BTN1_PRESS,
	KEY_BTN2_PRESS,
	KEY_BTN3_PRESS,
	KEY_BTN4_PRESS,
	KEY_BTN5_PRESS,
	KEY_BTN6_PRESS,
	KEY_BTN7_PRESS,
	KEY_BTN8_PRESS,
	KEY_BTN9_PRESS,
	KEY_BTN10_PRESS,
	KEY_BTN1_LONG,
	KEY_BTN2_LONG,
	KEY_BTN3_LONG,
	KEY_BTN4_LONG,
	KEY_BTN5_LONG,
	KEY_BTN6_LONG,
	KEY_BTN7_LONG,
	KEY_BTN8_LONG,
	KEY_BTN9_LONG,
	KEY_BTN10_LONG,
	KEY_BTN1_VLONG,
	KEY_BTN2_VLONG,
	KEY_BTN3_VLONG,
	KEY_BTN4_VLONG,
	KEY_BTN5_VLONG,
	KEY_BTN6_VLONG,
	KEY_BTN7_VLONG,
	KEY_BTN8_VLONG,
	KEY_BTN9_VLONG,
	KEY_BTN10_VLONG,
	KEY_BTN1_RELEASE,
	KEY_BTN2_RELEASE,
	KEY_BTN3_RELEASE,
	KEY_BTN4_RELEASE,
	KEY_BTN5_RELEASE,
	KEY_BTN6_RELEASE,
	KEY_BTN7_RELEASE,
	KEY_BTN8_RELEASE,
	KEY_BTN9_RELEASE,
	KEY_BTN10_RELEASE,
} key_state_t;

void        Key_Initialize(void);
void        Key_Update(void);

// state machine
void        Key_State_Idle(void);
void        Key_State_Btn1_Press(void);
void        Key_State_Btn1_Long(void);
void        Key_State_Btn1_VLong(void);
void        Key_State_Release(void);

bool        Key_ReadBtn1State(void);

key_state_t Key_GetState(void);

#endif /* INC_KEY_H_ */
