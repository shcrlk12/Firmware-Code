/*
 * duty_wait_state.c
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */


#include "duty_wait_state.h"
#include "main_system.h"
#include "key.h"

static volatile uint32_t s_time_duty_wait = 0;

main_state_t DutyWaitState_Loop()
{
    main_state_t nextMain = MAIN_STATE_DUTYWAIT;

    sub_state_duty_wait_t subState = GetSubState();
    sub_state_duty_wait_t nextSubState = subState;

	switch(subState)
	{
		case SUB_STATE_DUTY_WAIT_INIT:
			nextSubState = DutyWaitState_Init();
			break;

		case SUB_STATE_DUTY_WAIT_WAIT:
			nextSubState = DutyWaitState_Wait();
			break;

		case SUB_STATE_DUTY_WAIT_DISPLAY_TIME:
			nextSubState = DutyWaitState_DisplayTime();
			break;

		case SUB_STATE_DUTY_WAIT_DISPLAY_WARNING:
			nextSubState = DutyWaitState_DisplayWarning();
			break;

		case SUB_STATE_DUTY_WAIT_WAIT_DONE:
			(void)DutyWaitState_WaitDone();
			SetSubState(SUB_STATE_STANDBY_RETURN_FROM_EXPOSURE);
			return MAIN_STATE_STANDBY;

		default:
	        nextSubState = SUB_STATE_DUTY_WAIT_INIT;
	        break;
	}

	if(nextSubState != subState)
	{
		SetSubState(nextSubState);
	}

	return nextMain;
}

sub_state_duty_wait_t DutyWaitState_Init()
{
	//TODO: Wait LED ON
	s_time_duty_wait = 0;

    // if exposure stopped by user (and it is not error), display warning message for n secs
    if(g_accu_system.flags.weray_exposure_success == false)
    {
    	return SUB_STATE_DUTY_WAIT_DISPLAY_WARNING;
    }
    else
    {
    	return SUB_STATE_DUTY_WAIT_WAIT;
    }
}

sub_state_duty_wait_t DutyWaitState_Wait()
{
	key_state_t key_state = Key_GetState();

	//TODO: Key값 받아서 exp 가 눌렷으면 경고로 이동
	/*
	if()
		return SUB_STATE_DUTY_WAIT_DISPLAY_WARNING;
		*/
	if(s_time_duty_wait > g_accu_system.setting.t_pulse_off)
	{
	}
		return SUB_STATE_DUTY_WAIT_WAIT_DONE;

	return SUB_STATE_DUTY_WAIT_WAIT;
}

sub_state_duty_wait_t DutyWaitState_DisplayTime()
{
	return SUB_STATE_DUTY_WAIT_DISPLAY_TIME;
}

sub_state_duty_wait_t DutyWaitState_DisplayWarning()
{
	key_state_t key_state = Key_GetState();

	s_time_duty_wait++;

	//TODO: Wait중에 누르면 Wait LED 깜빡이도록 설정

    if((s_time_duty_wait > (uint32_t)g_weray.timings.t_disp_warning) && (key_state == KEY_IDLE))
    {
        return SUB_STATE_DUTY_WAIT_WAIT;
    }

    return SUB_STATE_DUTY_WAIT_DISPLAY_WARNING;
}

sub_state_duty_wait_t DutyWaitState_WaitDone()
{
	key_state_t key_state = Key_GetState();

    if(key_state == KEY_IDLE)
    {
        // reset flag for the next time
        g_accu_system.flags.weray_exposure_success = true;
    }
    return SUB_STATE_DUTY_WAIT_WAIT_DONE;
}

