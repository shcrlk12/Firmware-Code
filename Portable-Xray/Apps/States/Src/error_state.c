/*
 * error_state.c
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */


#include "error_state.h"
#include "main_system.h"
#include "key.h"

main_state_t ErrorState_Loop()
{
    main_state_t nextMain = MAIN_STATE_ERROR;

    sub_state_error_t subState = GetSubState();
    sub_state_error_t nextSubState = subState;

	switch(subState)
	{
		case SUB_STATE_ERROR_INIT:
			nextSubState = ErrorState_Init();
			break;

		case SUB_STATE_ERROR_SET_UI:
			nextSubState = ErrorState_Set_UI();
			break;

		case SUB_STATE_ERROR_WAIT:
			nextSubState = ErrorState_Wait();
			break;

		case SUB_STATE_ERROR_EXIT:
			SetSubState(SUB_STATE_STANDBY_INIT);
			return MAIN_STATE_STANDBY;

		default:
	        nextSubState = SUB_STATE_ERROR_INIT;
	        break;
	}

	if(nextSubState != subState)
	{
		SetSubState(nextSubState);
	}

	return nextMain;
}

sub_state_error_t ErrorState_Init()
{
	return SUB_STATE_ERROR_SET_UI;
}

sub_state_error_t ErrorState_Set_UI()
{
	//TODO: Error에 따라 UI 설정 해야함.


    return SUB_STATE_ERROR_WAIT;

}

sub_state_error_t ErrorState_Wait()
{
	key_state_t key_state = Key_GetState();

    // this can be done only by remote system
    if((g_accu_system.flags.weray_clear_error == true) && (key_state == KEY_IDLE))
    {
        // actual error clear is done in control loop; just reset UI from error
        g_accu_system.flags.weray_clear_error = false;

        return SUB_STATE_ERROR_EXIT;
    }

    return SUB_STATE_ERROR_WAIT;
}

