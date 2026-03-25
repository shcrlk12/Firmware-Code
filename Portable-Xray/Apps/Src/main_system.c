/*
 * main_system.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#include "main_system.h"

STRUCT_ACCU_SYSTEM g_accu_system;
STRUCT_WERAY_PARAMS g_weray;

STRUCT_TIMING_VARS g_exp_timing;
STRUCT_EXPOSURE_SETTINGS g_exp_settings;


void MainStateMachine_Loop()
{
	main_state_t state = GetMainState();
	main_state_t nextState;

	switch(state)
	{
		case MAIN_STATE_SYSTEM_INIT:
			nextState = InitState_Loop();
			break;

		case MAIN_STATE_PASS_INPUT:
			nextState = PassInputState_Loop();
			break;
		case MAIN_STATE_IDLE:
			break;

		default:
			break;
	}

	// Check error
	nextState = Check_Error();

	// Change State
	if(nextState != state)
	{
		SetMainState(nextState);
		SetSubState(0);
	}
}

void SetExposureParameters()
{
    // copy default exposure settings, convert timing (msec) to count
	g_exp_settings.v_gate_set = g_accu_system.setting.v_gate_set;
	g_exp_settings.v_anode_set = g_accu_system.setting.v_anode_set;
	g_exp_settings.n_repeat = g_accu_system.setting.n_repeat;
	g_exp_settings.t_pulse_on = g_accu_system.setting.t_pulse_on * 10;
	g_exp_settings.t_pulse_off = g_accu_system.setting.t_pulse_off * 10;
	g_exp_settings.i_accu_set = g_accu_system.setting.i_accu_set;

    // convert timing (msec) to count
	g_exp_timing.t_busy_hold = 0; // no hold time before gate ramp
	g_exp_timing.t_anode_ramp = g_accu_system.timing.t_anode_ramp * 10;
	g_exp_timing.t_anode_hold = g_accu_system.timing.t_anode_hold * 10;
	g_exp_timing.t_gate_ramp = g_accu_system.timing.t_gate_ramp * 10;
	g_exp_timing.t_gate_hold = g_accu_system.timing.t_gate_hold * 10;
	g_exp_timing.t_accu_ramp = g_accu_system.timing.t_accu_ramp * 10;
    g_exp_timing.t_off_hold = g_accu_system.timing.t_off_hold * 10;

    // take account of rise-fall-stabilize time
    uint16_t pulse_on_offset = g_exp_timing.t_accu_ramp + 1;
    uint16_t pulse_off_offset = g_exp_timing.t_accu_ramp + g_exp_timing.t_gate_ramp + g_exp_timing.t_gate_hold + 3;
    if(g_accu_system.options.short_pulse_mode == 1)
    {
        pulse_off_offset = 0;
    }

    if(g_exp_settings.t_pulse_on > pulse_on_offset)
    {
    	g_exp_settings.t_pulse_on = g_exp_settings.t_pulse_on - pulse_on_offset;
    }
    else
    {
    	g_exp_settings.t_pulse_on = 0;
    }

    if(g_exp_settings.t_pulse_off > pulse_off_offset)
    {
    	g_exp_settings.t_pulse_off = g_exp_settings.t_pulse_off - pulse_off_offset;
    }
    else
    {
    	g_exp_settings.t_pulse_off = 0;
    }

    // for long pulse mode, when pulse off time is not enough, do not repeat
    if((g_accu_system.setting.t_pulse_off < 500) && (g_accu_system.options.short_pulse_mode == 0)) g_exp_settings.n_repeat = 1;
}

void UpdateExposureResults()
{
    if(g_accu_system.accumulator.n_sample != 0)
    {
        // update result, total number of exposure and cumulative exposure time is calculated during exposure process
    	g_accu_system.result.v_gate = (uint16_t)(g_accu_system.accumulator.v_gate / g_accu_system.accumulator.n_sample);
    	g_accu_system.result.v_accu = (uint16_t)(g_accu_system.accumulator.v_accu / g_accu_system.accumulator.n_sample);
    	g_accu_system.result.v_anode = (uint16_t)(g_accu_system.accumulator.v_anode / g_accu_system.accumulator.n_sample);
    	g_accu_system.result.v_buck = (uint16_t)(g_accu_system.accumulator.v_buck / g_accu_system.accumulator.n_sample);
    	g_accu_system.result.i_accu = (uint16_t)(g_accu_system.accumulator.i_accu / g_accu_system.accumulator.n_sample);
        g_accu_system.result.i_anode = (uint16_t)(g_accu_system.accumulator.i_anode / g_accu_system.accumulator.n_sample);
    }
    else
    {
    	g_accu_system.result.v_gate = 0;
    	g_accu_system.result.v_accu = 0;
    	g_accu_system.result.v_anode = 0;
    	g_accu_system.result.v_buck = 0;
    	g_accu_system.result.i_accu = 0;
    	g_accu_system.result.i_anode = 0;
    }
    DATALOG_ExposureLog(g_accu_system.result.v_gate, g_accu_system.result.v_accu,
    		g_accu_system.result.v_anode, g_accu_system.result.v_buck,
			g_accu_system.result.i_accu, g_accu_system.result.i_anode);
    g_accu_system.result.n_exposure++;
}
