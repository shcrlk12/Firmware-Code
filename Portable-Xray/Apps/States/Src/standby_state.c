#include "standby_state.h"
#include "main_system.h"

volatile uint32_t time_after_exposure = 0;

sub_state_standby_t StandbyState_Init()
{
	return SUB_STATE_STANDBY_SETUP;
}

sub_state_standby_t StandbyState_Setup()
{
	// start battery state monitoring immediately (this Setup is called just once after power-up)
	time_after_exposure = (uint32_t)g_weray.timings.t_batt_mon_resume * 1000UL + 1;

}

main_state_t StandbyState_Loop()
{
    main_state_t nextMain = MAIN_STATE_STANDBY;

    sub_state_standby_t subState = GetSubState();
    sub_state_standby_t nextSubState;

	switch(subState)
	{
		case SUB_STATE_STANDBY_INIT:
			nextSubState = StandbyState_Init();
			break;

		case SUB_STATE_STANDBY_SETUP:
			nextSubState = StandbyState_Setup();
			break;

		default:
	        nextSubState = SUB_STATE_STANDBY_INIT;
	        break;
	}

	if(nextSubState != subState)
	{
		SetSubState(nextSubState);
	}

	return nextMain;
}
