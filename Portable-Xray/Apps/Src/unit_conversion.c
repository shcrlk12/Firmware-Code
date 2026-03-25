/*
 * unit_conversion.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */
#include "unit_conversion.h"
#include <math.h>
#include "main_system.h"

#define LSB_MAX 4095.0f
#define VDD_V 3.3f


uint16_t CONV_float_to_adcvalue(float value)
{
    if (value > 4095.0f) value = 4095.0f;
    if (value < 0.0f) value = 0.0f;
    return (uint16_t)(value + 0.5f);
}

uint16_t CONV_float_to_uint16(float value)
{
    if (value > 65535.0f) value = 65535.0f;
    if (value < 0.0f) value = 0.0f;
    return (uint16_t)(value + 0.5f);
}

uint32_t CONV_float_to_uint32(float value)
{
    if (value > 1e9) value = 1e9;
    if (value < 0.0f) value = 0.0f;
    return (uint32_t)(value + 0.5f);
}

uint16_t CONV_V_BUCK_LSB_to_mV(uint16_t value)
{
    float v_buck_mV = (float)value * VDD_V * 1000.0f * (g_accu_system.board.R_VBUCK_Load + g_accu_system.board.R_VBUCK_Sense) / (g_accu_system.board.R_VBUCK_Sense * LSB_MAX);
    return CONV_float_to_uint16(v_buck_mV);
}

uint16_t CONV_V_BUCK_mV_to_LSB(uint16_t value)
{
    float lsb = (float)value * LSB_MAX * g_accu_system.board.R_VBUCK_Sense / (1000.0f * VDD_V * (g_accu_system.board.R_VBUCK_Load + g_accu_system.board.R_VBUCK_Sense));
    return CONV_float_to_adcvalue(lsb);
}

uint32_t CONV_V_ANODE_LSB_to_10V(uint16_t value)
{
    float v_anode_V = (float)value * VDD_V * (g_accu_system.board.R_VANODE_Load + g_accu_system.board.R_VANODE_Sense) / (g_accu_system.board.R_VANODE_Sense * LSB_MAX * 10.0f);
    return CONV_float_to_uint32(v_anode_V);
}

uint16_t CONV_V_ANODE_10V_to_LSB(uint32_t value)
{
    float lsb = (float)value * LSB_MAX * 10.0f * g_accu_system.board.R_VANODE_Sense / (VDD_V * (g_accu_system.board.R_VANODE_Load + g_accu_system.board.R_VANODE_Sense));
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_V_GATE_LSB_to_V(uint16_t value)
{
    float v_gate_V = (float)value * VDD_V * (g_accu_system.board.R_VGATE_Load + g_accu_system.board.R_VGATE_Sense) / (g_accu_system.board.R_VGATE_Sense * LSB_MAX);
    return CONV_float_to_uint16(v_gate_V);
}

uint16_t CONV_V_GATE_V_to_LSB(uint16_t value)
{
    float lsb = (float)value * LSB_MAX * g_accu_system.board.R_VGATE_Sense / (VDD_V * (g_accu_system.board.R_VGATE_Load + g_accu_system.board.R_VGATE_Sense));
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_V_ACCU_LSB_to_V(uint16_t value)
{
    float v_accu_V = (float)value * VDD_V * (g_accu_system.board.R_VACCU_Load + g_accu_system.board.R_VACCU_Sense) / (g_accu_system.board.R_VACCU_Sense * LSB_MAX);
    return CONV_float_to_uint16(v_accu_V);
}

uint16_t CONV_V_ACCU_V_to_LSB(uint16_t value)
{
    float lsb = (float)value * LSB_MAX * g_accu_system.board.R_VACCU_Sense / (VDD_V * (g_accu_system.board.R_VACCU_Load + g_accu_system.board.R_VACCU_Sense));
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_I_ANODE_LSB_to_mA(uint16_t value)
{
    float lsb_to_V = (float)value * VDD_V / LSB_MAX;
    float offset_V = VDD_V * g_accu_system.board.R_IBUCK_OFFSET_L / (g_accu_system.board.R_IBUCK_OFFSET_L + g_accu_system.board.R_IBUCK_OFFSET_H);
    float i_anode_mA = (lsb_to_V - offset_V) * 1000000.0f / (g_accu_system.board.GAIN_IBUCK_Sense * g_accu_system.board.R_IBUCK_Sense); // (uV/mOhm = mA)
    return CONV_float_to_uint16(i_anode_mA);
}

uint16_t CONV_I_ANODE_mA_to_LSB(uint16_t value)
{
    float v_sense_V = (float)value * g_accu_system.board.R_IBUCK_Sense * g_accu_system.board.GAIN_IBUCK_Sense / 1000000.0f;
    float v_offset_V = VDD_V * g_accu_system.board.R_IBUCK_OFFSET_L / (g_accu_system.board.R_IBUCK_OFFSET_L + g_accu_system.board.R_IBUCK_OFFSET_H);
    float lsb = LSB_MAX * (v_sense_V + v_offset_V) / VDD_V;
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_I_GATE_LSB_to_uA(uint16_t value)
{
    float i_gate_uA = (float)value * VDD_V * 1000000000.0f / (g_accu_system.board.GAIN_IGATE_Sense * g_accu_system.board.R_IGATE_Sense * LSB_MAX); // (nV/mOhm = uA)
    return CONV_float_to_uint16(i_gate_uA);
}

uint16_t CONV_I_GATE_uA_to_LSB(uint16_t value)
{
    float lsb = (float)value * LSB_MAX * g_accu_system.board.R_IGATE_Sense * g_accu_system.board.GAIN_IGATE_Sense / (VDD_V * 1000000000.0f);
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_I_ACCU_LSB_to_uA(uint16_t value)
{
    float i_accu_uA = (float)value * VDD_V * 1000000.0f / (g_accu_system.board.R_IACCU_Sense * LSB_MAX); // (uV/Ohm = uA)
    return CONV_float_to_uint16(i_accu_uA);
}

uint16_t CONV_I_ACCU_uA_to_LSB(uint16_t value)
{
    float lsb = (float)value * LSB_MAX * g_accu_system.board.R_IACCU_Sense / (VDD_V * 1000000.0f) ;
    return CONV_float_to_adcvalue(lsb);
}

uint16_t CONV_T_SENS_LSB_to_P1degC(uint16_t value)
{
    float log_conv = logf((LSB_MAX / (float)value - 1.0f) * g_weray.board.R_VTEMP_Load / g_weray.board.R_VTEMP_TC) * g_weray.board.INV_TC_FACTOR;
    float t_inv = 0.00335401643f + log_conv; // 1.0 / (273.15 + 25) + log_conv;
    float t_sens = 10.0f / t_inv - 2731.5f;
    return CONV_float_to_uint16(t_sens);
}

uint16_t CONV_V_BATT_LSB_to_mV(uint16_t value)
{
    float v_batt_mV = (float)value * VDD_V * 1000.0f * (g_weray.board.R_VBATT_Load + g_weray.board.R_VBATT_Sense) / (g_weray.board.R_VBATT_Sense * LSB_MAX);
    return CONV_float_to_uint16(v_batt_mV);
}

uint16_t CONV_T_MCU_LSB_to_P1degC(uint16_t value)
{
    // datasheet says coefficient is -1.5mV/degC, but there are no offset value
    // 1.5mV = 1.8613636LSB, so 1LSB = 0.5372405 degC
    // we need to add some offset for 'calibrated' value
    float t_mcu = (545.0f - (float)value * 0.5372405f) * 10.0f;
    return CONV_float_to_uint16(t_mcu);
}
