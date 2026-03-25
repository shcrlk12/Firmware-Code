/*
 * duty_wait_state.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */

#ifndef STATES_INC_DUTY_WAIT_STATE_H_
#define STATES_INC_DUTY_WAIT_STATE_H_

#include "state_machine_type.h"

sub_state_duty_wait_t DutyWaitState_Init(void);
sub_state_duty_wait_t DutyWaitState_Wait(void);
sub_state_duty_wait_t DutyWaitState_DisplayTime(void);
sub_state_duty_wait_t DutyWaitState_DisplayWarning(void);
sub_state_duty_wait_t DutyWaitState_WaitDone(void);


#endif /* STATES_INC_DUTY_WAIT_STATE_H_ */
