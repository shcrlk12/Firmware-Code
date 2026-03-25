/*
 * battmgmt_state.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */

#ifndef STATES_INC_BATTMGMT_STATE_H_
#define STATES_INC_BATTMGMT_STATE_H_

#include <stdbool.h>
#include "state_machine_type.h"

/* Battery management state handlers */
sub_state_battmgmt_t BattmgmtState_Init(void);
sub_state_battmgmt_t BattmgmtState_HoldBattLow(void);
sub_state_battmgmt_t BattmgmtState_StartCharge(void);
sub_state_battmgmt_t BattmgmtState_Charge(void);
sub_state_battmgmt_t BattmgmtState_StartChargeFromPassInput(void);
sub_state_battmgmt_t BattmgmtState_ChargeFromPassInput(void);

/* DC plug detect */
bool Batt_DC_PlugState(void);

#endif /* STATES_INC_BATTMGMT_STATE_H_ */
