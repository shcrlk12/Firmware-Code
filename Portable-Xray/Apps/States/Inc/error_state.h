/*
 * error_state.h
 *
 *  Created on: Jan 7, 2026
 *      Author: Owner
 */

#ifndef STATES_INC_ERROR_STATE_H_
#define STATES_INC_ERROR_STATE_H_

#include "state_machine_type.h"

main_state_t ErrorState_Loop();
sub_state_error_t ErrorState_Init();
sub_state_error_t ErrorState_Set_UI();
sub_state_error_t ErrorState_Wait();

#endif /* STATES_INC_ERROR_STATE_H_ */
