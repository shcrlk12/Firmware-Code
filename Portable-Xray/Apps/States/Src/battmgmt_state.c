/*
 * battmgmt_state.c
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */

#include "battmgmt_state.h"
#include "state_machine_type.h"
#include "key.h"

main_state_t BattmgmtState_Loop()
{
    main_state_t nextMain = MAIN_STATE_BATTMGMT;

    sub_state_battmgmt_t subState = GetSubState();
    sub_state_battmgmt_t nextSubState = subState;

	switch(subState)
	{
		case SUB_STATE_BATTMGMT_INIT:
			nextSubState = BattmgmtState_Init();
			break;

		case SUB_STATE_BATTMGMT_HOLD_BATT_LOW:
			nextSubState = BattmgmtState_HoldBattLow();
			break;

		case SUB_STATE_BATTMGMT_START_CHARGE:
			nextSubState = BattmgmtState_StartCharge();
			break;

		case SUB_STATE_BATTMGMT_CHARGE:
			nextSubState = BattmgmtState_Charge();
			break;

		case SUB_STATE_BATTMGMT_EXIT_CHARGE_TO_STANDBY:
			SetSubState(SUB_STATE_STANDBY_INIT);
			return MAIN_STATE_STANDBY;

		case SUB_STATE_BATTMGMT_START_CHARGE_FROM_PASS_INPUT:
			nextSubState = BattmgmtState_StartChargeFromPassInput();
			break;

		case SUB_STATE_BATTMGMT_CHARGE_FROM_PASS_INPUT:
			nextSubState = BattmgmtState_ChargeFromPassInput();
			break;

		case SUB_STATE_BATTMGMT_EXIT_CHARGE_TO_PASS_INPUT:
			SetSubState(SUB_STATE_PASS_INPUT_INIT);
			return MAIN_STATE_PASS_INPUT;

		default:
	        nextSubState = SUB_STATE_BATTMGMT_INIT;
	        break;
	}

	if(nextSubState != subState)
	{
		SetSubState(nextSubState);
	}

	return nextMain;
}

sub_state_battmgmt_t BattmgmtState_Init()
{
	//TODO: batt low
}

sub_state_battmgmt_t BattmgmtState_HoldBattLow()
{
	Key_GetState();
	if(Batt_DC_PlugState() == 1)
	{
		return SUB_STATE_BATTMGMT_START_CHARGE;
	}
}

sub_state_battmgmt_t BattmgmtState_StartCharge()
{
	//TODO: 외부에서 바로 이점으로 진입하도록 해야함. dc 꼽으면
	// TODO: 배터리 UI 셋업 해야함

	return SUB_STATE_BATTMGMT_CHARGE;
}

sub_state_battmgmt_t BattmgmtState_Charge()
{
	// TODO: 배터리 상태에 대한UI 업데이트 해야함.

	key_state_t key_state = Key_GetState();
	if((Batt_DC_PlugState == 0) && (key_state == KEY_IDLE))
	{
		return SUB_STATE_BATTMGMT_EXIT_CHARGE_TO_STANDBY;
	}
	return SUB_STATE_BATTMGMT_CHARGE;
}

sub_state_battmgmt_t BattmgmtState_StartChargeFromPassInput()
{
	// TODO: 배터리 상태에 대한UI 업데이트 해야함.

	key_state_t key_state = Key_GetState();
	if((Batt_DC_PlugState == 0) && (key_state == KEY_IDLE))
	{
		return SUB_STATE_BATTMGMT_EXIT_CHARGE_TO_STANDBY;
	}
	return SUB_STATE_BATTMGMT_CHARGE;
}


sub_state_battmgmt_t BattmgmtState_ChargeFromPassInput()
{
	// TODO: 배터리 상태에 대한UI 업데이트 해야함.

	key_state_t key_state = Key_GetState();
	if((Batt_DC_PlugState == 0) && (key_state == KEY_IDLE))
	{
		return SUB_STATE_BATTMGMT_EXIT_CHARGE_TO_STANDBY;
	}
	return SUB_STATE_BATTMGMT_CHARGE;
}

bool Batt_DC_PlugState()
{
	//TODO: dc 플러그 상태 받아와야함.
	return true;
}
