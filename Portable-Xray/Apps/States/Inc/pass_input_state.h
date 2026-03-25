/*
 * pass_input_state.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef STATES_INC_PASS_INPUT_STATE_H_
#define STATES_INC_PASS_INPUT_STATE_H_

#include <state_machine_type.h>

main_state_t PassInputState_Loop();

sub_state_pass_input_t PassInputState_Init();
sub_state_pass_input_t PassInputState_Wait();
sub_state_pass_input_t PassInputState_PassCheck();

#endif /* STATES_INC_PASS_INPUT_STATE_H_ */
