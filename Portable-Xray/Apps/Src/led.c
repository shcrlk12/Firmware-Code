/*
 * led.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */
#include <stdbool.h>
#include "led.h"
#include "bitflags.h"
#include "stm32f1xx_hal.h"

#ifndef LED_ACTIVE_LOW
#define LED_ACTIVE_LOW (0U)
#endif

typedef uint16_t led_status_t;

enum {
    LED_ST_ERROR    = (1u << 0),
    LED_ST_POWER    = (1u << 1),
    LED_ST_RECORD   = (1u << 2),
    LED_ST_WAIT     = (1u << 3),
    LED_ST_READY    = (1u << 4),
    LED_ST_EXPOSURE = (1u << 5),
};

static volatile led_status_t s_led_status;
static volatile led_status_t s_old_led_status;

static inline GPIO_PinState led_pin_state(bool on)
{
#if LED_ACTIVE_LOW
    return on ? GPIO_PIN_RESET : GPIO_PIN_SET;
#else
    return on ? GPIO_PIN_SET : GPIO_PIN_RESET;
#endif
}

static inline void led_write(GPIO_TypeDef *port, uint16_t pin, bool on)
{
    HAL_GPIO_WritePin(port, pin, led_pin_state(on));
}


void LED_Update(void)
{
    uint16_t cur;

    // Disabling Interrupt to Prevent Collision
    __disable_irq();
    cur = s_led_status;
    __enable_irq();

    if (cur == s_old_led_status) {
        return;
    }

    s_old_led_status = cur;

//    // 각 LED 핀 갱신
//    led_write(LED_ERROR_GPIO_Port,    LED_ERROR_Pin,    BITS_TEST_U16(cur, LED_ST_ERROR));
//    led_write(LED_POWER_GPIO_Port,    LED_POWER_Pin,    BITS_TEST_U16(cur, LED_ST_POWER));
//    led_write(LED_RECORD_GPIO_Port,   LED_RECORD_Pin,   BITS_TEST_U16(cur, LED_ST_RECORD));
//    led_write(LED_WAIT_GPIO_Port,     LED_WAIT_Pin,     BITS_TEST_U16(cur, LED_ST_WAIT));
//    led_write(LED_READY_GPIO_Port,    LED_READY_Pin,    BITS_TEST_U16(cur, LED_ST_READY));
//    led_write(LED_EXPOSURE_GPIO_Port, LED_EXPOSURE_Pin, BITS_TEST_U16(cur, LED_ST_EXPOSURE));
}


void LED_AllOff(void)
{
    BITS_CLEAR_U16(s_led_status, 0xFFu);
}

void LED_AllOn(void)
{
    BITS_SET_U16(s_led_status, 0xFFu);
}

void LED_ErrorOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_ERROR);
}

void LED_ErrorOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_ERROR);
}

void LED_PowerOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_POWER);
}

void LED_PowerOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_POWER);
}

void LED_RecordOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_RECORD);
}

void LED_RecordOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_RECORD);
}

void LED_WaitOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_WAIT);
}

void LED_WaitOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_WAIT);
}

void LED_ReadyOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_READY);
}

void LED_ReadyOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_READY);
}

void LED_ExposureOn(void)
{
    BITS_SET_U16(s_led_status, LED_ST_EXPOSURE);
}

void LED_ExposureOff(void)
{
    BITS_CLEAR_U16(s_led_status, LED_ST_EXPOSURE);
}
