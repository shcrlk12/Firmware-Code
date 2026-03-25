/*
 * error.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */
#include "error.h"
#include "main_system.h"
#include "config.h"

main_state_t Check_Stop() {
	__disable_irq();
	main_state_t nextMainState = GetMainState();
	__enable_irq();

	if ((g_accu_system.flags.trigger_user_stop == true)
			|| (g_accu_system.flags.system_error_occurred == true)) {

	}
	return nextMainState;
}

main_state_t Check_Error() {

	__disable_irq();
	main_state_t nextMainState = GetMainState();
    __enable_irq();

	enum SYSTEM_ERROR_CODES error_code = SYSTEM_ERROR_NONE;
	if (g_accu_system.options.bypass_errors == 0) {
		if (ADC_Get_VFB_ANODE() > g_accu_system.evaluated_threshold.v_anode_max)
			error_code = SYSTEM_ERROR_ANODE_OVERVOLTAGE;
		if (ADC_Get_VFB_GATE() > g_accu_system.evaluated_threshold.v_gate_max)
			error_code = SYSTEM_ERROR_GATE_OVERVOLTAGE;
		if (ADC_Get_VFB_ACCU() > g_accu_system.evaluated_threshold.v_accu_max)
			error_code = SYSTEM_ERROR_ACCU_OVERVOLTAGE;
		if (ADC_Get_IFB_BUCK() > g_accu_system.evaluated_threshold.i_anode_max)
			error_code = SYSTEM_ERROR_TUBE_OVERCURRENT;
		if (ADC_Get_IFB_ACCU() > g_accu_system.threshold.i_accu_max)
			error_code = SYSTEM_ERROR_TUBE_OVERCURRENT; // absolute maximum during ramp-up
		if (g_accu_system.flags.system_xon_stabilized == true) {
			if (ADC_Get_IFB_ACCU()
					> g_accu_system.evaluated_threshold.i_accu_max)
				error_code = SYSTEM_ERROR_TUBE_OVERCURRENT; // within control range after ramp-up
			if (g_accu_system.options.test_mode == 0) {
				if (ADC_Get_VFB_ANODE()
						< g_accu_system.evaluated_threshold.v_anode_min)
					error_code = SYSTEM_ERROR_ANODE_UNDERVOLTAGE;
				if (ADC_Get_VFB_GATE()
						< g_accu_system.evaluated_threshold.v_gate_min)
					error_code = SYSTEM_ERROR_GATE_UNDERVOLTAGE;
				if (ADC_Get_IFB_ACCU()
						< g_accu_system.evaluated_threshold.i_accu_min)
					error_code = SYSTEM_ERROR_TUBE_UNDERCURRENT;
			}
		}
		if (g_accu_system.options.bypass_interlock == 0) {
			volatile uint8_t intlock_value;
			if (g_weray.options.exp_sw_interlock == 1) {
//	                intlock_value = IO_EXP_SW_IN_GetValue();
			} else {
//	                intlock_value = IO_DC_PLUG_STATE_GetValue();
			}
			if (intlock_value == g_weray.options.interlock_active_low) {
				error_code = SYSTEM_ERROR_INTERLOCK_OPEN;
			}
		}
	}

	if (error_code != SYSTEM_ERROR_NONE) {
		g_accu_system.error_count++;
		if (g_accu_system.error_count
				> g_accu_system.evaluated_threshold.n_error_cycle) {
			g_accu_system.error_count = 0;
			g_accu_system.flags.system_error_occurred = true;
//	            PROC_CaptureErrorInfo((uint16_t)error_code);
//	            PROC_AnodeControlEnable(false);
//	            PROC_GateControlEnable(false);
//	            PROC_SetACCU(false, 0);
//	            PROC_UpdateExposureResults();
//	            PROC_ChangeToControlState(state_on_error);
		}
	} else {
		g_accu_system.error_count = 0;
	}

	return nextMainState;
}
