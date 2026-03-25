/*
 * key.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#include "key.h"
#include <stdbool.h>
#include "config.h"
#include "main_system.h"

static volatile key_state_t s_key_state;
static volatile key_state_t s_pressed_key_state;

static volatile uint32_t s_key_counter;
static void (*s_KeyStateFunc)(void);

static volatile uint16_t s_chattering_counter = 0;

#ifndef KEY_ACTIVE_LOW
#define KEY_ACTIVE_LOW (0U)
#endif

static inline bool Key_read(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_PinState state = HAL_GPIO_ReadPin(port, pin);

#if KEY_ACTIVE_LOW
    return state ? true : false;
#else
    return state ? false : true;
#endif
}

void Key_Initialize()
{
    s_key_counter = 0;
    s_key_state = KEY_IDLE;
    s_KeyStateFunc = Key_State_Idle;
}

void Key_Update()
{
	s_key_counter++;
	s_KeyStateFunc();
}

void Key_State_Idle()
{
	//btn1
    if(Key_ReadBtn1State() == true)
    {
        s_chattering_counter++;
        if(s_chattering_counter > g_weray.timings.t_chattering)
        {
        	s_key_state = KEY_BTN1_PRESS;
            s_KeyStateFunc = Key_State_Btn1_Press;
        }
    }
}

void Key_State_Btn1_Press()
{
    if(Key_ReadBtn1State() == false)
    {
        s_chattering_counter++;
        if(s_chattering_counter > g_weray.timings.t_chattering)
        {
            s_KeyStateFunc = Key_State_Release;
        }
    }
    //    TODO: change Long parameter
    else if(s_key_counter > g_weray.timings.t_long_press_wait)
    {
    	s_key_state = KEY_BTN1_LONG;
        s_KeyStateFunc = Key_State_Btn1_Long;
    }
    else
    {
        s_chattering_counter = 0;
    }
}

void Key_State_Btn1_Long()
{
    if(Key_ReadBtn1State() == false)
    {
        s_chattering_counter++;
        if(s_chattering_counter > g_weray.timings.t_chattering)
        {
            s_KeyStateFunc = Key_State_Release;
        }
    }
    //    TODO: change Long parameter
    else if(s_key_counter > g_weray.timings.t_very_long_press_wait)
    {
        s_key_state = KEY_BTN1_VLONG;
        s_KeyStateFunc = Key_State_Btn1_VLong;
    }
    else
    {
        s_chattering_counter = 0;
    }
}

void Key_State_Btn1_VLong()
{
    if(Key_ReadBtn1State() == false)
    {
        s_chattering_counter++;
        if(s_chattering_counter > g_weray.timings.t_chattering)
        {
            s_KeyStateFunc = Key_State_Release;
        }
    }
    else
    {
        s_chattering_counter = 0;
    }
}


void Key_State_Release()
{
	__disable_irq();
	s_pressed_key_state = s_key_state;
	__enable_irq();

    s_KeyStateFunc = Key_State_Idle;
    s_chattering_counter = 0;
	s_key_state = KEY_IDLE;
}



bool Key_ReadBtn1State()
{
	//TODO: 구현해야함. true : active, false: non active
	return true;
}


key_state_t Key_GetState()
{
    key_state_t retVal;

    __disable_irq();
    retVal = s_pressed_key_state;
    s_pressed_key_state = KEY_IDLE;
    __enable_irq();

	return retVal;
}


