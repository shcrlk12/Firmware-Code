/*
 * unit_conversion.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_UNIT_CONVERSION_H_
#define INC_UNIT_CONVERSION_H_

#include <stdint.h>

uint16_t CONV_V_BUCK_LSB_to_mV(uint16_t value);
uint16_t CONV_V_BUCK_mV_to_LSB(uint16_t value);
uint32_t CONV_V_ANODE_LSB_to_10V(uint16_t value);
uint16_t CONV_V_ANODE_10V_to_LSB(uint32_t value);
uint16_t CONV_V_GATE_LSB_to_V(uint16_t value);
uint16_t CONV_V_GATE_V_to_LSB(uint16_t value);
uint16_t CONV_V_ACCU_LSB_to_V(uint16_t value);
uint16_t CONV_V_ACCU_V_to_LSB(uint16_t value);
uint16_t CONV_I_ANODE_LSB_to_mA(uint16_t value);
uint16_t CONV_I_ANODE_mA_to_LSB(uint16_t value);
uint16_t CONV_I_GATE_LSB_to_uA(uint16_t value);
uint16_t CONV_I_GATE_uA_to_LSB(uint16_t value);
uint16_t CONV_I_ACCU_LSB_to_uA(uint16_t value);
uint16_t CONV_I_ACCU_uA_to_LSB(uint16_t value);
uint16_t CONV_T_SENS_LSB_to_P1degC(uint16_t value);
uint16_t CONV_V_BATT_LSB_to_mV(uint16_t value);
uint16_t CONV_T_MCU_LSB_to_P1degC(uint16_t value);


#endif /* INC_UNIT_CONVERSION_H_ */
